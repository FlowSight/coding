#include<bits/stdc++.h>

using namespace std;

class ReaderWriter {
    public:
    explicit ReaderWriter(){
        num_reader = 0;
        iswriter = 0;
    }
    void readLock(){
        unique_lock<mutex> ul(mtx);
        q.push_back(0); // 0 for read
        cv.wait(ul,[this]{
            return iswriter == 0 && (q.front() == 0);
        });
        q.pop_front();
        num_reader += 1;
    }
    void readUnlock(){
        unique_lock<mutex> ul(mtx);
        num_reader--;
        cv.notify_all();
    }
    void writeLock() {
        unique_lock<mutex> ul(mtx);
        q.push_back(1);
        cv.wait(ul,[this]{
            return (iswriter == 0 )&& (num_reader == 0) && (q.front() == 1);
        });
        q.pop_front();
        iswriter = 1;
    }
    void writeUnlock(){
        unique_lock<mutex> ul(mtx);
        iswriter = 0;
        cv.notify_all();
    }

    private:
    mutex mtx;
    condition_variable cv;
    int num_reader, iswriter;
    deque<int> q;
};

