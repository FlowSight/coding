#include <iostream>
#include <thread>
#include <mutex>
#include<chrono>

using namespace std;

class ThreadSafe {
    int val;
    std::mutex mtx;
    public:
    ThreadSafe() {
        val = 0;
    }
};

class ThreadFunctor {
    public:
    void test(int num) {
        cout<<"thread id: "<<this_thread::get_id()<<" func"<<endl;
    } 
};
volatile int running = 0;
void testFunc(shared_ptr<int> num){
    while(running){
        cout<<"Running"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    //cout<<"thread id: "<<this_thread::get_id()<<" test func "<<*(num)<<endl;
}

int main(){
    ThreadFunctor tf;
    int num = 1;
    running = 1;
    auto shared_num = make_shared<int>(num);
    // thread t1(&ThreadFunctor::test,&tf,num);
    thread t2(&testFunc,shared_num);
    this_thread::sleep_for(chrono::seconds(6));

    running = 0;

    //t1.join();
    t2.join();

    return 0;
}