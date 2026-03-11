
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;


class TestClass{
    public:
    TestClass(){}
    void run(){
        cout<<"10^2 is "<<10*10<<endl;
    }
};

void testMethod1(){
    promise<int> p;
    future<int> f = p.get_future();
    thread t1([](promise<int> p){
        this_thread::sleep_for(chrono::seconds(1));
        p.set_value(22);
        cout<<"thread has set "<<endl;
    },std::move(p));

    cout<<"waiting for result"<<endl;
    int res = f.get();
    cout<<"got "<<res<<endl;
    t1.join();
}

void testMethod2(){
    promise<int> p;
    future<int> f = p.get_future();
    thread t1([](promise<int> p){
        this_thread::sleep_for(chrono::seconds(1));
        try {
            throw runtime_error("thread exception");
            p.set_value(23);
        } catch(...) {
            p.set_exception(current_exception());
        }
        cout<<"thread has set "<<endl;
    },std::move(p));

    cout<<"waiting for result"<<endl;
    try {
        auto res = f.get();
        cout<<"got "<<res<<endl;
    } catch (const exception& e) {
        cout<<"exception : "<<e.what()<<endl;
    }
    t1.join();
}

void testMethod3(){
    TestClass tc;
    packaged_task<void()> pt([&tc]{ tc.run(); });
    future<void> fut = pt.get_future();

    thread t1(std::move(pt));
    t1.join();
    fut.get();
}

int main() {
    testMethod1();
    testMethod2();
    testMethod3();
    return 0;
}