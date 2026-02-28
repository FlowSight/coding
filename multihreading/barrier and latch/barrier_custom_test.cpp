

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

class Barrier {
    public:
    explicit Barrier(int num){
        _cnt = num;
        _runningCnt = 0;
        // for(auto i=0;i<num;i++){
        //     condition_variable cv;
        //     _cvArr.push_back(cv);
        // }
    }

    void arrive_and_wait(){
        unique_lock<mutex> ul(_mtx);
        if(_runningCnt == _cnt) {
            _cv.notify_all();
            _runningCnt = 0;
        } else {
             _cv.wait(ul, [&] { return _runningCnt != _cnt; });
        }
    }

    private:
    int _cnt, _runningCnt;
    mutex _mtx;
    condition_variable _cv;
    //vector<condition_variable> _cvArr;
};

Barrier bar(3);

void worker(int id) {
    // Phase 1
    this_thread::sleep_for(chrono::milliseconds(100 * (id + 1)));  // simulate work
    cout << "Thread " << id << " finished phase 1\n";
    bar.arrive_and_wait();
    // ─── barrier: all threads finished phase 1 ───

    // Phase 2
    this_thread::sleep_for(chrono::milliseconds(100 * (3 - id)));
    cout << "Thread " << id << " finished phase 2\n";
    bar.arrive_and_wait();
    // ─── barrier: all threads finished phase 2 ───

}

void testMethod(){
    vector<thread> arr;
    for(auto i=0;i<3;i++){
        arr.push_back(thread(&worker,i));
    }
    for(auto &it : arr) it.join();
}
int main() {
    testMethod();
    return 0;
}
