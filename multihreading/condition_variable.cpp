#include<iostream>
#include<thread>

using namespace std;

mutex _mtx1, _mtx2;
condition_variable _cv1, _cv2;
string  msg1 = "1", msg2 = "2";

void method1 (){
    while(true) {
        unique_lock<mutex> ul(_mtx1);
        _cv1.wait(ul,[]{
            return !msg2.empty();
        });
        cout<<" Got message from 2 : "<<msg2<<endl;
        if(stol(msg2) == 99) {
            msg1 = to_string(99);
            _cv2.notify_one();
            break;
        }
        msg2 = "";
        msg1 = to_string(rand()%100);
         _cv2.notify_one();
        this_thread::sleep_for(chrono::milliseconds(100));
    }

}

void method2(){
    while (true) {
        unique_lock<mutex> ul(_mtx2);
        _cv2.wait(ul,[]{
            return !msg1.empty();
        });
        cout<<" Got message from 1 : "<<msg1<<endl;
        if(stol(msg1) == 99) {
            msg2 = to_string(99);
            _cv1.notify_one();
            break;
        }
        msg1 = "";
        msg2 = to_string(rand()%100);
        _cv1.notify_one();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void testMethod(){
    thread th1(&method1);
    thread th2(&method2);
    th1.join();
    th2.join();
}

int main() {
    testMethod();
    return 0;
}