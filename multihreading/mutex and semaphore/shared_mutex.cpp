


#include <iostream>
#include <numeric>
#include <chrono>
#include <thread>
#include <shared_mutex>
#include <mutex>
using namespace std;



volatile int resource = 0;
shared_mutex rwmut;



void readFunc(int waitTime) {
    std::this_thread::sleep_for(std::chrono::seconds(waitTime));

    shared_lock<shared_mutex> sl(rwmut);

    cout << "read: " << resource << endl;

}



void writeFunc(int waitTime) {
    std::this_thread::sleep_for(std::chrono::seconds(waitTime));

    unique_lock<shared_mutex> ul(rwmut);

    resource = rand()%100;
    cout << "write: " << resource << endl;
}



int main() {
    constexpr int NUM_THREADS_READ = 10;
    constexpr int NUM_THREADS_WRITE = 4;
    constexpr int NUM_ARGS = 3;

    std::thread lstThRead[NUM_THREADS_READ];
    std::thread lstThWrite[NUM_THREADS_WRITE];
    int lstArg[NUM_ARGS];


    // INITIALIZE
    // lstArg = { 0, 1, 2, ..., NUM_ARG - 1 }
    std::iota(lstArg, lstArg + NUM_ARGS, 0);


    // CREATE THREADS
    for (auto&& th : lstThRead) {
        int arg = lstArg[ rand()%NUM_ARGS ];
        th = std::thread(&readFunc, arg);
    }

    for (auto&& th : lstThWrite) {
        int arg = lstArg[ rand()%NUM_ARGS];
        th = std::thread(&writeFunc, arg);
    }


    // JOIN THREADS
    for (auto&& th : lstThRead) {
        th.join();
    }

    for (auto&& th : lstThWrite) {
        th.join();
    }


    return 0;
}