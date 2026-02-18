

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;



void doTask(string& msg) {
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << msg << " from " << this_thread::get_id()<<endl;
}

void doTaskNoRef(string msg) {
    cout << msg << endl;
}

int main() {
    string a = "lorem ipsum";
    string b = "dolor amet";

    // error, thread will make a copy of a, but
    // doTask accepts a ref
    // auto thFoo = std::thread(doTask, a); 

    // below will work, as arg is non-ref, so new object is used in arg, 
    // original a is not touched by thread
    auto th1 = std::thread(doTaskNoRef, a); 

    // Tells std::thread: "Don't copy! Use the original variable"
    // The wrapper itself is copied, but it points to original var
    // When thread calls doTask, the wrapper unwraps to string&
    auto thFoo = std::thread(&doTask, std::ref(a));
    auto thBar = std::thread(&doTask, std::ref(b));

    thFoo.join();
    thBar.join();
    th1.join();

    return 0;
}