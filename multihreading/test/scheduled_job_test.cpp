#include <iostream>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <vector>

using namespace std;
using Clock = chrono::steady_clock;
using Duration = chrono::milliseconds;
using Task = function<void()>;
using TimePoint = Clock::time_point;


enum TaskType {
   Oneshot = 0, FixedDelay = 1, Delayed = 2
};

struct TaskObj {
    TimePoint nextRuntime = Clock::now();
    Task task = [](){};
    Duration period = Duration(0);
    int id = -1;
    TaskType tasktype = TaskType::Oneshot;

    TaskObj() = default;

    TaskObj(Task _task, Duration _gapTime,TimePoint _nextRuntime, int _id, TaskType _type){
        task = _task;
        period = _gapTime;
        tasktype = _type;
        id = _id;
        nextRuntime = _nextRuntime;
    }
    
    bool operator>(const TaskObj& obj) const {
        return this->nextRuntime > obj.nextRuntime;
    }
};


class SchedulerService {
    public:
    explicit SchedulerService(int _numTh){
        numTh = _numTh;
        for(auto i=0;i<numTh;i++)workers.emplace_back(&SchedulerService::workerLoop,this);
        schedulerWorker = thread(&SchedulerService::schedularLoop,this);
    }

    int submitOneShotTask(Task command, Duration delay){
        int curId = id.fetch_add(1);
        TimePoint tp = TimePoint::clock::now() + delay;
        TaskObj obj(command,Duration(0),tp,curId,TaskType::Oneshot);
        unique_lock<mutex> ul(mtxPq);
        pq.push(obj);
        cvSchedule.notify_one();
        return id;
    }
    int submitScheduledTask(Task command,Duration delay, Duration initdelay ){
        int curId = id.fetch_add(1);
        TimePoint tp = TimePoint::clock::now() + initdelay;
        TaskObj obj(command,delay,tp,curId,TaskType::FixedDelay);
        unique_lock<mutex> ul(mtxPq);
        pq.push(obj);
        cvSchedule.notify_one();
        return id;
    }

    int submitDelayedTask(Task command,Duration delay, Duration initdelay ){
        int curId = id.fetch_add(1);
        TimePoint tp = TimePoint::clock::now() + initdelay;
        TaskObj obj(command,delay,tp,curId,TaskType::Delayed);
        unique_lock<mutex> ul(mtxPq);
        pq.push(obj);
        cvSchedule.notify_one();
        return id;
    }
    void shutdown(){
        stopped.store(true);
        cvSchedule.notify_all();
        cvWorker.notify_all();
        for(auto &th : workers) {
            if(th.joinable()) th.join();
        }
         if(schedulerWorker.joinable())schedulerWorker.join();
    }

    private:
    int numTh;
    atomic<int> id{0};
    atomic<bool> stopped{0};
    priority_queue<TaskObj,vector<TaskObj>,greater<TaskObj>> pq;
    queue<TaskObj> taskQueue;
    mutex mtxPq,mtxTaskQueue;
    condition_variable cvSchedule,cvWorker;
    vector<thread> workers;
    thread schedulerWorker;

    void schedularLoop(){
        TaskObj task;
        while (true)
        {
            {
                unique_lock<mutex> ul(mtxPq);
                if(pq.empty()){
                    cvSchedule.wait(ul,[this]{
                        return stopped || !pq.empty();
                    });
                    if(stopped) return;
                    continue;
                }
                task = pq.top();
                cvSchedule.wait_until(ul,task.nextRuntime,[this] {
                    if(stopped.load()) return true;
                    if(!pq.empty() && pq.top().nextRuntime <= Clock::now()) return true;
                    return false;
                });
                if(stopped.load()) return;
                task = pq.top();
                pq.pop();
            }

            {
                unique_lock<mutex> ul1(mtxTaskQueue);
                taskQueue.push(task);
                cvWorker.notify_one();
            }
        }

    }


    void workerLoop(){
        TaskObj obj;
        while (true)
        {
            {
                unique_lock<mutex> ul1(mtxTaskQueue);
                cvWorker.wait(ul1,[this]{return stopped || !taskQueue.empty();});
                if(stopped.load()) return;
                obj = taskQueue.front();
                taskQueue.pop();
            }
            auto command = obj.task;
            command();
            auto now = Clock::now();
            
            if(obj.tasktype == TaskType::Oneshot || stopped.load()) continue;
            {
                unique_lock<mutex> ul2(mtxPq);
                if(obj.tasktype == TaskType::FixedDelay){
                    obj.nextRuntime = obj.nextRuntime + obj.period;
                } else {
                    obj.nextRuntime = now + obj.period;
                }
                if(obj.nextRuntime <= Clock::now()) obj.nextRuntime = Clock::now();
                pq.push(obj);
                cvSchedule.notify_one();
            }
        }
    }
};

void testMethod1() {
    SchedulerService serv(4);
    auto start = Clock::now();
    serv.submitOneShotTask([start]{
        this_thread::sleep_for(Duration(100));
        cout<<"done one shot task: "<< chrono::duration_cast<Duration>(Clock::now() - start).count() << endl;
    },Duration(500));
    
    serv.submitScheduledTask([start]{
        this_thread::sleep_for(Duration(200));
        cout<<"done scheduled task "<<chrono::duration_cast<Duration>(Clock::now() - start).count() << endl;
    },Duration(200),Duration(100));

    serv.submitDelayedTask([start]{
        this_thread::sleep_for(Duration(300));
        cout<<"done delayed  task "<< chrono::duration_cast<Duration>(Clock::now() - start).count() << endl;
    },Duration(100),Duration(200));
    this_thread::sleep_for(Duration(10000));
    cout<<"shutting down executor"<<endl;
    serv.shutdown();
}
int main(){
    testMethod1();
    return 0;
}


//DEI65Q