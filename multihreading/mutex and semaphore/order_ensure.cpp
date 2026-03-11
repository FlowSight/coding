#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include <semaphore>
#include<condition_variable>

using namespace std;

binary_semaphore binSem(0), binSem1(0);
class PrintInOrder {
public:
    PrintInOrder() { /* initialize semaphores */ }

    void printFirst()  { 
       // binSem.acquire();
        /* ... */ cout << "First\n";  /* ... */ 
        binSem.release();
    }
    void printSecond() { 
        binSem.acquire();
        cout << "Second\n"; 
        binSem1.release();
    }
    void printThird() { 
        binSem1.acquire();
        cout << "Third\n"; 
    }
    
};

int main() {
    PrintInOrder p;
    // launch in REVERSE order to prove it still works
    thread t3(&PrintInOrder::printThird,  &p);
    thread t2(&PrintInOrder::printSecond, &p);
    thread t1(&PrintInOrder::printFirst,  &p);
    t1.join(); t2.join(); t3.join();
}