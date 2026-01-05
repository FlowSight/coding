#include <iostream>
#include <thread>
#include <mutex>
#include<chrono>

using namespace std;

class FunctorClass {
    public:
    void operator() (string message) {
        cout<<message<<endl;
    }
};

void loopMethod(){
    for(auto i=0;i<10;i++)cout<<i<<" "<<this_thread::get_id()<<endl;
}

void printMethod(shared_ptr<string> message){
    cout<<*(message.get())<<endl;
}

int main(){
    string message = "hello world";
    auto message_ptr = make_shared<string>(message);
    thread t1(&printMethod,message_ptr);
    t1.join();
    return 0;
}