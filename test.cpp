#include<bits/stdc++.h>
using namespace std;


struct Task
{
    public:
    string id, payload, status;
    int maxret,delaysec, retrycnt;
    
    Task() = default;
    Task(string _id, string _payload, int _maxret, int _delay){
        id = _id;
        payload = _payload;
        maxret = _maxret;
        delaysec = _delay;
        status = "not picked";
        retrycnt = 0;
    }
    /* data */
};

class TaskStore  {
    int ts;
    set<pair<int,string>> invisibletasks;
    unordered_map<string,int> tasktovisibilitytomap;
    set<pair<int,string>> taskqueue;
    unordered_map<string,string> taskworkermap;
    unordered_map<string,Task> taskmap;
    unordered_map<string,int> workertovisibilityto;


    TaskStore(){
        ts = 0;
    }
 //Adds a task to the pending queue. If delaySeconds > 0, the task    must not be claimable before now + delaySeconds.  
void enqueue(string taskId, string payload, int delaySeconds, int maxRetries) {

    Task task(taskId,payload,maxRetries,delaySeconds);
    taskmap[taskId] = task;
    taskqueue.insert({delaySeconds+ts,taskId});
    ts++;
}
 


//Atomically claims the next available task for workerId.    The task must not be visible to other workers for visibilityTimeout seconds.    Returns null if no tasks are ready.  
string claimNext(string workerId, int visibilityTimeout) {
    
    auto task = *(taskqueue.begin());
    taskqueue.erase(taskqueue.begin());

    auto& taskobj = taskmap[task.second];
    taskobj.status = "queued";
    taskobj.retrycnt++;

    workertovisibilityto[workerId] = visibilityTimeout;
    taskworkermap[workerId] = task.second;
    int timeout = visibilityTimeout+ts;
    invisibletasks.insert({timeout,task.second});
    tasktovisibilitytomap[task.second] = timeout;


    ts++;
}

//Extends the visibility timeout of a claimed task by visibilityTimeout.    Returns false if the task is no longer owned by this worker.  
bool heartbeat(string taskId, string workerId) {
    auto it = taskworkermap.find(workerId);
    if(it == taskworkermap.end()) return false;


    auto taskid = it->second;
    auto timeout = tasktovisibilitytomap[taskid];

    auto it = invisibletasks.find({timeout,taskid});
    invisibletasks.erase(it);

    auto visibilityto = workertovisibilityto[workerId];
    timeout += visibilityto;

    invisibletasks.insert({timeout,taskId});

}

// Marks a task as SUCCEEDED. Throws if taskId not owned by workerId. 
void complete(string taskId, string  workerId) {
    auto it = taskworkermap.find(workerId);
    if(it == taskworkermap.end()) {
        throw runtime_error("not owned");
    }
    if(it->second != taskId) {
         throw runtime_error("not owned");
    }

    auto& taskobj = taskmap[taskId];
    taskobj.status = "SUCCEEDED";

    auto visto = tasktovisibilitytomap.find(taskId);
    invisibletasks.erase(invisibletasks.find({visto,taskId}));

    taskworkermap.erase(taskworkermap.find(taskId));
} 

// Marks the execution attempt as failed. If retries remain, re-schedules    the task with exponential backoff. Otherwise moves it to DLQ. 
void fail(string taskId, string workerId, string error) {
    auto it = taskworkermap.find(workerId);
    if(it == taskworkermap.end()) {
        throw runtime_error("not owned");
    }
    if(it->second != taskId) {
         throw runtime_error("not owned");
    }

    auto& taskobj = taskmap[taskId];
    taskobj.status = "Failed";
    taskobj.retrycnt++;

    if(taskobj.retrycnt == taskobj.maxret) {
        cout<<"move to DLQ"<<endl;
    } else {
        taskqueue.insert({taskobj.retrycnt * 10 +ts,taskId});
    }

    auto visto = tasktovisibilitytomap.find(taskId);
    invisibletasks.erase(invisibletasks.find({visto,taskId}));

    taskworkermap.erase(taskworkermap.find(taskId));
}   
 
//Returns the current state of the task. 
string getStatus(string taskId) {
    auto taskobj = taskmap[taskId];
    return taskobj.status;
}    
 
//Scans for tasks whose visibility timeout has expired and re-queues them.    Returns count of tasks re-queued. (Called by a background sweeper.)
int reapStuckTasks(){
    int ans = 0;
    while (invisibletasks.size()){
        auto it = invisibletasks.begin();
        if(it->first < ts) {
            ans++;
            taskqueue.insert({ts,it->second});
            invisibletasks.erase(it);
        } else break;
    }
    return ans;
} 


int main() {

    return 0;
}