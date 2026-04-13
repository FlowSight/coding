

#include <bits/stdc++.h>
#include<semaphore>

using namespace std;

using Function = function<void(int)>;

struct Job {
    public:
    Job() = default;
    int id;
    Function func;
    vector<Job> dependents;
    vector<Job> getDependentTasks(){
        return dependents;
    }
    void runtask(int num){
        func(num);
    }
};

class JobScheduler {
    public:
    explicit JobScheduler(int _numworker) : numworker(_numworker) {
        for(auto i=0;i<numworker;i++) workers.emplace_back(&JobScheduler::workerloop, this);
    }

    bool execute(vector<Job> seed ){
        makeGraph(seed);
        bool failed = false;

        {
            unique_lock<mutex> ul(mtx);
            for(auto it : seed) q.push(move(it));
            cv.notify_all();
        }

        
        {
            unique_lock<mutex> ul(mtx);
            cv.wait(ul,[this]{
                return (running_cnt.load() == 0) && (q.empty() || stopped.load());
            });
            if(stopped) failed = true;
            stopped = true;
            cv.notify_all();
        }

        for(auto &it : workers) {
            if(it.joinable()) it.join();
        }
        return !failed;
    }

    void stop(){
        stopped = true;
        cv.notify_all();
    }

    private:
    int numworker;
    unordered_map<int,atomic<int>> ind;
    vector<thread> workers;
    queue<Job> q;
    mutex mtx;
    atomic<bool> stopped{false};
    atomic<int> running_cnt{0};
    condition_variable cv;

    void workerloop(){
        Job job;
        while(true){
            {
                unique_lock<mutex> ul(mtx);
                cv.wait(ul,[this]{
                    return stopped || !q.empty();
                });
                if(stopped) {
                    cv.notify_all();
                     return;
                }
                job = move(q.front());
                q.pop();
                running_cnt.fetch_add(1);
            }
            
            try
            {
                int num = rand()%100;
                 job.runtask(num);
            }
            catch(const std::exception& e)
            {
                stopped = true;
                std::cerr << e.what() << '\n';
            }
            
            {
                unique_lock<mutex> ul2(mtx);
                running_cnt.fetch_sub(1);
                cv.notify_all();
                if(stopped) return;

            }
            
            auto tasks = job.getDependentTasks();
            for(auto it : tasks) {
                if(ind[it.id].fetch_sub(1) == 1) {
                    unique_lock<mutex> ul1(mtx);
                    q.push(move(it));
                    cv.notify_all();
                }
            }
        }
    }

    void makeGraph(vector<Job> seed){
        queue<Job> q;
        for(auto it : seed) {
            ind[it.id] = 0;
            q.push(it);
        }
        while(!q.empty()){
            auto sz = q.size();
            while(sz--){
                auto tp = q.front();
                q.pop();
                auto tasks = tp.getDependentTasks();
                for(auto &it : tasks){
                    if(ind.find(it.id) == ind.end()) q.push(it);
                    ind[it.id].fetch_add(1);
                } 
            }
        }
    }
};


// ─────────────────────────────────────────────
// Helpers / Tests
// ─────────────────────────────────────────────


vector<Job> makegraph(bool fail = false){
    vector<Job> jobs;
    Function func = [](int num){
        this_thread::sleep_for(chrono::milliseconds(num));
    };
    Function failfunc = [](int num){
        throw runtime_error("failed forced");
    };
    for(auto i=0;i<10;i++) {
        Job job;
        job.id = i;
        job.func = func;
        if(fail){
            if(i==7) job.func = failfunc;
        }
        jobs.push_back(job);
    }
    for(auto i=3;i<10;i++){
        int idx = rand()%i;
        jobs[i].dependents.push_back(jobs[idx]);
    }
    return jobs;
}

void testAllSucceed() {
    auto jobs = makegraph();
    JobScheduler js(3);
    js.execute({jobs[0],jobs[1],jobs[2]});
    this_thread::sleep_for(chrono::milliseconds(10000));
    js.stop();
}

void testFailFast() {
    auto jobs = makegraph(1);
    JobScheduler js(3);
    js.execute({jobs[0],jobs[1],jobs[2]});
    this_thread::sleep_for(chrono::milliseconds(10000));
    js.stop();
}

int main() {
    testAllSucceed();
    //testFailFast();
    std::cout << "All tests passed.\n";
    return 0;
}
