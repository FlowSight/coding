/*
RACE CONDITIONS AND DATA RACES
*/


#include <iostream>
#include <chrono>
#include <thread>
using namespace std;



using sysclock = std::chrono::system_clock;


mutex mtxCounter;
int counter = 0;


void declareWinner(string str){
    unique_lock<mutex> ul(mtxCounter);
    cout<<str<<" Won!"<<endl;
}

void doTaskA(sysclock::time_point timePointWakeUp) {
    std::this_thread::sleep_until(timePointWakeUp);

    while (counter < 10)
        ++counter;
    declareWinner("A");
}



void doTaskB(sysclock::time_point timePointWakeUp) {
    std::this_thread::sleep_until(timePointWakeUp);

    while (counter > -10)
        --counter;
    declareWinner("B");
}





int main() {
    auto tpNow = sysclock::now();
    auto tpWakeUp = tpNow + std::chrono::seconds(1);

    auto thA = std::thread(&doTaskA, tpWakeUp);
    auto thB = std::thread(&doTaskB, tpWakeUp);

    thA.join();
    thB.join();

    return 0;
}