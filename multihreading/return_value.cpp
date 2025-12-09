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

void testFunc(int num, shared_ptr<int> ret){
    cout<<"inside testfunc "<<endl;
    (*ret) = 2*num;
}

int main(){
    int num = 1, ret = 0;
    auto shared_num = make_shared<int>(num),
        shared_ret = make_shared<int>(ret);
    thread t1(&testFunc,num,shared_ret);
    //t1.join();
    t1.join();
    cout<<*(shared_ret)<<" " <<ret<<endl;

    return 0;
}