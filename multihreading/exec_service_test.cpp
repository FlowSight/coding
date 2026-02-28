#include<iostream>
#include<thread>
#include<algorithm>
#include<functional>
#include<queue>
#include<mutex>

using namespace std;
using voidFunc = function<void()>;

class ExecService {
    public:
    ExecService& operator=(ExecService& ex) = delete;
    ExecService(const ExecService &ex)=delete;

    explicit ExecService(int num_th){
        _tasksRunning = 0;
        _shutdown = 0;
        for(auto i=0;i<num_th;i++) threadPool.push_back(thread(&ExecService::workerloop, this));
    }

    void submitWork(voidFunc func){
        unique_lock<mutex> ul(mtxTasks);
        tasks.push(func);
        _cvQueue.notify_one();
    }
    void shutdown(){
        {
            unique_lock<mutex> ul(mtxShutdown);
            _shutdown = 1;
        }
        _cvQueue.notify_all();

        unique_lock<mutex> ul2(mtxthreadPool);
        for(auto &it : threadPool) {
            if(it.joinable()) it.join();
        }
        threadPool.clear();
    }

    void waitTaskDone(){
        while(true){
            {
                {
                    unique_lock<mutex> ul(mtxTasks);
                    if(!tasks.empty()){
                        ul.unlock();
                        this_thread::sleep_for(chrono::milliseconds(10));
                        continue;
                    }
                }
                unique_lock<mutex> ul1(_mtxTasksRunning);
                _cvRunning.wait(ul1,[this]{
                    return _tasksRunning == 0;
                });
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(10));
        }

    }

    private:

    void workerloop(){
        voidFunc task;
        while(true){
            {
                unique_lock<mutex> ul(mtxTasks);
                _cvQueue.wait(ul,[this]{
                    return _shutdown || !tasks.empty();
                });
            
                if(_shutdown) return;
                task = move(tasks.front());
                tasks.pop();
                {
                    unique_lock<mutex> ul(_mtxTasksRunning);
                    _tasksRunning++;
                }
            }
            try {
                task();
            } catch(...){

            }

            {
                unique_lock<mutex> ul2(_mtxTasksRunning);
                _tasksRunning--;
                _cvRunning.notify_one(); // critical
            }
        }
    }

    vector<std::thread> threadPool;
    queue<voidFunc> tasks;
    int _tasksRunning, _shutdown;
    mutex mtxthreadPool, mtxTasks, mtxShutdown;
    mutex _mtxTasksRunning;
    condition_variable _cvQueue, _cvRunning;
};

void voidMethod(){
    cout<<"inside voidfunc "<<this_thread::get_id()<<endl;
    this_thread::sleep_for(chrono::milliseconds(10));
}

void testThread(){
    ExecService ex(2);
    for(auto i=0;i<10;i++) ex.submitWork(voidMethod);
    ex.waitTaskDone();
    ex.shutdown();
}

int main(){
    testThread();
    return 0;
}