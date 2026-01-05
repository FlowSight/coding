#include <iostream>
#include <thread>
#include <mutex>
#include<chrono>

using namespace std;


void printMethod(shared_ptr<string> message, int depth){
    if(depth == 5) return;
    printMethod(message,depth+1);
    cout<<*(message.get())<<" "<<"depth : "<<depth<<"ref count : " << message.use_count()<<endl;
}


void testRefCount() {
    // ref count in thread gets removed in recursion when stack pops.
    string message = "hello world";
    auto message_ptr = make_shared<string>(message);
    cout<<"main: ref count1: "<< message_ptr.use_count()<<endl;
    thread t1(&printMethod,message_ptr,0);
    t1.join();
    cout<<"main: ref count2: "<< message_ptr.use_count()<<endl;
    cout<<"main: ref count3: "<< message_ptr.use_count()<<endl;
}
int main(){
    testRefCount();
    return 0;
}