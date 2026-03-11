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
using voidFunc = function<void()> ;


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

    template <typename F, typename... Args>
    auto submit(F&& func, Args&&... args) {
        auto pt = make_shared<packaged_task<decltype(func(args...))()>>(bind(func,args...));

        auto fut = pt->get_future();
        {
            unique_lock<mutex> ul(mtxPending);
            tasks.push([pt]{
                 (*pt)();
            });
            cvPending.notify_all();
        }
        return fut;
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
            while(true) {
                voidFunc task;
                {
                    unique_lock<mutex> ul1(mtxPending);
                    cvPending.wait(ul1,[this]{ return stopped || tasks.size() > 0; });
                    if(stopped && tasks.empty()) return;
                    // something is tasks..so we. pick it
                    task = move(tasks.front());
                    tasks.pop();
                }

                try
                {
                    task();
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }

    bool stopped;
    mutex  mtxPending;
    int numth, taskRunning;
    vector<thread> workers;
    condition_variable cvPending;
    queue<voidFunc> tasks;
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
        futrs.push_back(move(th.submit(heavyCompute,rand()%5)));
    }

    for(auto &it : futrs){
        it.get();
    }
    th.shutdown();
}

int main(){
    testMethod();
    return 0;
}