#include<bits/stdc++.h>
using namespace std;

class ReaderWriter {
    public:
    ReaderWriter() {}
    void reader(int num){
        { 
            unique_lock<mutex> ul(mtx);
            cv.wait(ul,[this]{
                return !iswriter.load() && !writewaiting.load();
            });
            reader_cnt.fetch_add(1);
        }
        //read//
        { 
            unique_lock<mutex> ul(mtx);
            reader_cnt.fetch_sub(1);
            cv.notify_all();
        }
    }
    void writer(int num){
        { 
            unique_lock<mutex> ul(mtx);
            writewaiting.store(true);
            cv.wait(ul,[this]{
                return !iswriter.load() && (reader_cnt.load() == 0);
            });
            writewaiting.store(false);
            iswriter.store(true);
        }
        //write//
        { 
            unique_lock<mutex> ul(mtx);
            iswriter.store(false);
            cv.notify_all();
        }
    }

    private:
    mutex mtx;
    condition_variable cv;
    atomic<bool> iswriter{false}, writewaiting{false};
    atomic<int> reader_cnt{0};
};