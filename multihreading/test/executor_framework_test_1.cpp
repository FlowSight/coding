#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <future>
#include <chrono>
#include <semaphore>

using namespace std;
using voidFunc = function<void(int)> ;


class ThreadPoolExecutor {
    public:
    explicit ThreadPoolExecutor(int _numth) {
        stopped = false;
        numth = _numth;
        taskRunning = 0;
        for(auto i=0;i<numth;i++)workers.emplace_back(&ThreadPoolExecutor::workerLoop, this);
    }

    ~ThreadPoolExecutor() {
        shutdown();
    }

    //template <typename T>
    void submit(packaged_task<void(int)> task) {
        {
            unique_lock<mutex> ul(mtxPending);
            if(stopped) return;
            tasks.push(move(task));
            cvPending.notify_all();
        }
    }
    void shutdown() {
        {
            unique_lock<mutex> ul(mtxPending);
            if(stopped) return;
            stopped = true;
            
        }

        cvPending.notify_all();
        cout<<"shutting down..."<<endl;

        for(auto &th : workers){
            if(th.joinable()) th.join();
        }
    }


    private:
        void workerLoop(){
            packaged_task<void(int)> task;
            while(true) {
                {
                    unique_lock<mutex> ul1(mtxPending);
                    cvPending.wait(ul1,[this]{ return stopped || tasks.size() > 0; });
                    if(stopped && tasks.empty()) return;
                    // something is tasks..so we. pick it
                    task = move(tasks.front());
                    tasks.pop();
                    taskRunning++;
                }

                try
                {
                    task(rand()%5);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                 {
                    unique_lock<mutex> ul1(mtxPending);
                    taskRunning--;
                 }
            }
        }

    bool stopped;
    mutex  mtxPending;
    int numth, taskRunning;
    vector<thread> workers;
    condition_variable cvPending;
    queue<packaged_task<void(int)>> tasks;
    binary_semaphore binSem{1};

};


void heavyCompute(int workSec){
    this_thread::sleep_for(chrono::seconds(workSec));
    cout<<"Slept for "<<workSec<<endl;
}

void testMethod(){
    ThreadPoolExecutor th(4);
    vector<future<void>> futrs;
    for(auto i=0;i<10;i++){
        packaged_task<void(int)> task(heavyCompute);
        auto fut = task.get_future();
        th.submit(move(task));
        //futrs.push_back(move(fut));
    }
    this_thread::sleep_for(chrono::seconds(10));
    th.shutdown();
}

int main(){
    testMethod();
    return 0;
}