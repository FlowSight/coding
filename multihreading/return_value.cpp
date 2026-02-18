// learnings
//  promises are non-copyable (move-only),Must use std::ref(prom) 


#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <atomic>

using namespace std;

class ThreadSafe {
    int val;
    std::mutex mtx;
    public:
    ThreadSafe() {
        val = 0;
    }
};

void setSharedPointer(int num, shared_ptr<int> ret){
    cout << __func__ << endl;
    (*ret) = 2*num;
}

void setPointer(int num, int* ret){
    cout << __func__ << endl;
    (*ret) = 2*num;
}

void setPromise(int arg, std::promise<int> & prom) {
    int result = arg * 2;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    prom.set_value(result);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "This thread is exiting" << endl;
}

string doubleValue(int arg) {
    int result = arg * 2;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    cout << "This thread is exiting" << endl;
    return to_string(result);
}

void testYield(){
    // std::this_thread::yield() hints the scheduler to let other threads run.
    // Useful in spin-wait loops to avoid burning CPU.
    std::atomic<bool> ready{false};

    auto worker = [&ready]() {
        cout << "Worker: doing some work..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ready.store(true);
        cout << "Worker: done, flag set." << endl;
    };

    thread t(worker);

    // Spin-wait with yield instead of busy-looping
    int yieldCount = 0;
    while (!ready.load()) {
        std::this_thread::yield(); // politely give up time slice
        yieldCount++;
    }
    cout << "Main: flag is true after " << yieldCount << " yields" << endl;

    t.join();
}

void testPackageTask(){
    // without manually caling setvalue from promise, packaged_task does it
    auto ptask = std::packaged_task<string(int)>(doubleValue);
    auto fut = ptask.get_future(); // fut is std::future<string>

    auto th = std::thread(std::move(ptask), 5);

    // Block until ptask finishes
    string result = fut.get();

    cout << result << endl;

    th.join();
}

int main(){
    int num = 1, ret = 0;
    auto shared_ret = make_shared<int>(ret);

    cout<<"After setting with shared pointer "<<endl;
    thread t1(&setSharedPointer,num,shared_ret);
    t1.join();
    cout<<*(shared_ret)<<" "<<ret<<endl;

    
    cout<<"After setting with raw pointer "<<endl;
    thread t2(&setPointer,num,&ret);
    t2.join();
    cout<<*(shared_ret)<<" "<<ret<<endl;


    cout<<"After setting with promise "<<endl;
    auto prom = std::promise<int>();
    auto fut = prom.get_future(); // fut is std::future<int>
    auto t3 = thread(&setPromise, 5, std::ref(prom)); // because promises are non-copyable (move-only)
    // Block until prom.set_value() executes
    int result = fut.get();
    t3.join();
    cout << result << endl;

    testPackageTask();

    cout << "\nAfter testing yield" << endl;
    testYield();

    return 0;
}