// 1. addJob(id,recurrence,startTime, runtime)
// 2. fetchRunningJobs(ts)
// 3. fetchNextRuns(ts,window)
// 4. fetchNextRun(id,ts)
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// --- Task Status Enum ---
enum TaskStatus {
    PENDING,
    RUNNING,
    COMPLETED,
    FAILED
};

// --- Task Interface ---
class ITask {
public:
    virtual void execute() = 0;
    virtual TaskStatus getStatus() const = 0;
    virtual string getTaskName() const = 0;
    virtual long getScheduledTime() const = 0;
    virtual ~ITask() = default;
};

// --- Concrete Task Implementation ---
class GenericTask : public ITask {
    string name;
    TaskStatus status;
    int instanceId;
    long scheduledTime;
public:
    GenericTask(const string& taskName, int instId = 0, long schedTime = 0) 
        : name(taskName), status(PENDING), instanceId(instId), scheduledTime(schedTime) {}
    
    void execute() {
        cout << "Executing task: " << name << " (instance " << instanceId 
             << ", scheduled at: " << scheduledTime << ")\n";
        status = RUNNING;
        // Simulate task execution
        status = COMPLETED;
        cout << "Task " << name << " (instance " << instanceId << ") completed\n";
    }
    
    TaskStatus getStatus() const {
        return status;
    }
    
    string getTaskName() const {
        return name;
    }
    
    int getInstanceId() const {
        return instanceId;
    }
    
    long getScheduledTime() const {
        return scheduledTime;
    }
};

// --- Strategy Interface ---
class IRecurrenceStrategy {
public:
    virtual bool nextRun(long start, long now, long& result) const = 0;
    virtual ~IRecurrenceStrategy() = default;
};

// --- Concrete Strategies ---
class OneTimeStrategy : public IRecurrenceStrategy {
public:
    bool nextRun(long start, long now, long& result) const {
        if (now < start) {
            result = start;
            return true;
        }
        return false;
    }
};

class FixedIntervalStrategy : public IRecurrenceStrategy {
    long interval;
public:
    FixedIntervalStrategy(long i) : interval(i) {}
    bool nextRun(long start, long now, long& result) const {
        if (now < start) {
            result = start;
            return true;
        }
        long k = (now - start) / interval + 1;
        result = start + k * interval;
        return true;
    }
};

// --- Job Entity using Strategy ---
class Job {
    int id;
    long startTime;
    long runTime;
    shared_ptr<IRecurrenceStrategy> recurrence;
    shared_ptr<ITask> taskTemplate;
    vector<shared_ptr<ITask>> taskInstances;
public:
    Job(int id_, long start, long run, shared_ptr<IRecurrenceStrategy> strat, shared_ptr<ITask> t)
        : id(id_), startTime(start), runTime(run), recurrence(std::move(strat)), taskTemplate(std::move(t)) {}

    int getId() { return id; }

    bool isRunning(long ts) {
        long next;
        if (!recurrence->nextRun(startTime, ts, next)) return false;
        return (ts >= next && ts <= next + runTime);
    }

    bool getNextRun(long ts, long& result) {
        return recurrence->nextRun(startTime, ts, result);
    }
    
    void executeTask() {
        if (taskTemplate) {
            taskTemplate->execute();
        }
    }
    
    TaskStatus getTaskStatus() const {
        if (taskTemplate) {
            return taskTemplate->getStatus();
        }
        return PENDING;
    }
    
    // Create multiple task instances for upcoming runs
    void createNextRuns(int num) {
        if (!taskTemplate) return;
        
        string baseName = taskTemplate->getTaskName();
        int startId = taskInstances.size();
        long currentTime = startTime;
        
        for (int i = 0; i < num; ++i) {
            long nextRunTime;
            if (recurrence->nextRun(startTime, currentTime, nextRunTime)) {
                shared_ptr<ITask> newTask(new GenericTask(baseName, startId + i, nextRunTime));
                taskInstances.push_back(newTask);
                currentTime = nextRunTime + 1; // Move to next timestamp for next run calculation
            }
        }
        
        cout << "Created " << taskInstances.size() - startId << " task instances for job " << id 
             << ". Total instances: " << taskInstances.size() << "\n";
    }
    
    // Get all task instances
    const vector<shared_ptr<ITask>>& getTaskInstances() const {
        return taskInstances;
    }
    
    // Execute a specific task instance by index
    void executeTaskInstance(int index) {
        if (index >= 0 && index < static_cast<int>(taskInstances.size())) {
            taskInstances[index]->execute();
        } else {
            cout << "Invalid task instance index: " << index << "\n";
        }
    }
    
    // Get task instance count
    int getTaskInstanceCount() const {
        return taskInstances.size();
    }
};

// --- Demo ---
int main() {
    shared_ptr<IRecurrenceStrategy> oneTime(new OneTimeStrategy());
    shared_ptr<IRecurrenceStrategy> recurring(new FixedIntervalStrategy(10));
    
    shared_ptr<ITask> task1(new GenericTask("BackupDatabase"));
    shared_ptr<ITask> task2(new GenericTask("SendEmails"));

    Job j1(1, 100, 5, oneTime, task1);
    Job j2(2, 100, 5, recurring, task2);

    cout << "\n=== Job Information ===\n";
    cout << "Job " << j1.getId() << "\n";
    cout << "Job " << j2.getId() << "\n";

    long result;
    if (j1.getNextRun(90, result)) {
        cout << "\nJob1 next run at: " << result << "\n";
    } else {
        cout << "\nJob1 next run at: -1\n";
    }
    
    if (j2.getNextRun(115, result)) {
        cout << "Job2 next run at: " << result << "\n";
    } else {
        cout << "Job2 next run at: -1\n";
    }
    
    cout << "\n=== Creating Task Instances ===\n";
    j1.createNextRuns(3);
    j2.createNextRuns(5);
    
    cout << "\n=== Executing Task Instances ===\n";
    cout << "Job 1 has " << j1.getTaskInstanceCount() << " task instances\n";
    for (int i = 0; i < j1.getTaskInstanceCount(); ++i) {
        j1.executeTaskInstance(i);
    }
    
    cout << "\nJob 2 has " << j2.getTaskInstanceCount() << " task instances\n";
    for (int i = 0; i < j2.getTaskInstanceCount(); ++i) {
        j2.executeTaskInstance(i);
    }
    
    cout << "\n=== Task Instance Status ===\n";
    const vector<shared_ptr<ITask>>& j1Tasks = j1.getTaskInstances();
    for (size_t i = 0; i < j1Tasks.size(); ++i) {
        cout << "Job1 Task " << i << " - scheduled at: " << j1Tasks[i]->getScheduledTime()
             << ", status: " << j1Tasks[i]->getStatus() << " (2=COMPLETED)\n";
    }
    
    cout << "\n";
    const vector<shared_ptr<ITask>>& j2Tasks = j2.getTaskInstances();
    for (size_t i = 0; i < j2Tasks.size(); ++i) {
        cout << "Job2 Task " << i << " - scheduled at: " << j2Tasks[i]->getScheduledTime()
             << ", status: " << j2Tasks[i]->getStatus() << " (2=COMPLETED)\n";
    }
}
