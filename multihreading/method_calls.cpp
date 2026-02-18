#include <iostream>
#include <string>
#include <thread>
using namespace std;

// static method : & not required 
// non-static emthod: & is required + object

class Example {
public:
    void run() {
        std::thread th1(&Example::doTask, "Good day");
        th1.join();
        std::thread th2(&Example::doTask1, this);  // Pass 'this' for non-static member function
        th2.join();
    }
    void doTask1() {
        cout << "no task" << endl;
    }
    static void doTask(string message) {
        cout << message << endl;
    }

private:

};



int main() {
    Example example;
    example.run();
    cout<<"from main now"<<endl;
    thread th(&Example::doTask1,example);
    
    // no join, child kill and abruptly end.
    // detach() -> child killed
    //th.detach();  // uncomment to see effect
    th.join();
    return 0;
}