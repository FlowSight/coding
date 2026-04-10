#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <numeric>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>
#include <chrono>
#include <unordered_set>
#include <functional>
#include <future>

using namespace std;
using Task = function<void()>;
using Time = chrono::milliseconds;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct Job {
    public:
    Task task;
    int id;
    vector<int> dep;
    Job()=default;
    Job(Task _task, int _id, vector<int> _dep){
        task = _task;
        id = _id;
        dep = _dep;
    }
};

class JobManager {
    public:
    explicit JobManager(vector<Job> _jobs, int _numth) {
         jobs = _jobs;
         numTh = _numth;
         processJobs();
         for(auto i=0;i<numTh;i++){
            workers.emplace_back(&JobManager::workerloop,this);
         }
    }

    void start(){
        cvtodo.notify_all();
    }

    void shutdown(){
        stopped.store(true);
        cvtodo.notify_all();
    }

    void waitforfinish(){
        for(auto &th : workers){
            if(th.joinable())th.join();
        }
    }


    private:
    vector<Job> jobs;
    int numTh;
    atomic<bool> stopped{false};
    unordered_map<int,int> ind;
    unordered_map<int,vi> g;
    unordered_map<int,Job> idmap;
    vector<thread> workers;
    condition_variable cvtodo;
    queue<int> todo;
    mutex mtxtodo, mtxInd;

    void workerloop() {
        Job job;
        int picked = -1;
        while(true){
            {
                unique_lock<mutex> ul1(mtxtodo);
                cvtodo.wait(ul1,[this]{
                    return stopped || !todo.empty();
                });
                if(stopped) return;
                picked = todo.front();
                todo.pop();
            }
            try {
                job = idmap[picked];
                cout<<"processing job: "<<job.id<<endl;
                job.task();
            } catch (const exception ex) {
                cout<<"failed while running job :" << job.id<<endl;
                shutdown();
                return;
            }
            
            {
                unique_lock<mutex> ul2(mtxInd);
                for(auto it : g[job.id]){
                    if(--ind[it] == 0) {
                        unique_lock<mutex> ul3(mtxtodo);
                        todo.push(it);
                        cvtodo.notify_one();
                    }
                }
            }

        }
    }
    void processJobs(){
       for(auto it : jobs) {
        idmap[it.id] = it;
        if(ind.find(it.id) == ind.end()) ind[it.id] = 0;
        for(auto it1 : it.dep){
            g[it1].push_back(it.id);
            ind[it.id]++;
        }
       }
        for(auto it = ind.begin();it!=ind.end();it++){
            if(it->second == 0) todo.push(it->first);
        }
    }
};


void testmethod1(){
    vector<Job> jobs;
    
    for(auto i=0;i<10;i++){
        Task task = []{
            int idx = rand()%500;
            //if(idx<200) throw runtime_error("bad exception");
            this_thread::sleep_for(chrono::milliseconds(rand()%500));
        };
        vector<int> dep;
        if(i) dep.push_back(rand()%i);
        auto job = Job(task,i,dep);
        jobs.push_back(job);

    }
    JobManager jm(jobs,3);
    jm.start();
    this_thread::sleep_for(Time(10000));
    jm.shutdown();
    jm.waitforfinish();

    function<void(int)> meth = [](int time){
        this_thread::sleep_for(chrono::milliseconds(time));
        cout<<"Slept"<<endl;
    };
}

int main(){
    testmethod1();
    return 0;
}


