#include <iostream>
#include <string>
#include <tuple>
#include <chrono>
#include <thread>
#include <barrier>
using namespace std;



auto syncPoint = std::barrier(2); // participant count = 2

auto syncPointA = std::barrier(2);
auto syncPointB = std::barrier(2);


// ok here
void processRequest1(string userName, int waitTime) {
    std::this_thread::sleep_for(std::chrono::seconds(waitTime));

    cout << "Get request from " << userName << endl;
    syncPointA.arrive_and_wait();

    cout << "Process request for " << userName << endl;
    syncPointB.arrive_and_wait();

    cout << "Done " << userName << endl;
}

// stuck here
void processRequest(string userName, int waitTime) {
    std::this_thread::sleep_for(std::chrono::seconds(waitTime));

    cout << "Get request from " << userName << endl;
    syncPoint.arrive_and_wait();

    cout << "Process request for " << userName << endl;
    syncPoint.arrive_and_wait();

    cout << "Done " << userName << endl;
}



int main() {
    constexpr int NUM_THREADS = 4;
    std::thread lstTh[NUM_THREADS];

    tuple<string,int> lstArg[NUM_THREADS] = {
        { "lorem", 1 },
        { "ipsum", 3 },
        { "dolor", 3 },
        { "amet", 10 }
    };

    for (int i = 0; i < NUM_THREADS; ++i) {
        auto&& arg = lstArg[i];
        lstTh[i] = std::thread(&processRequest1, std::get<0>(arg), std::get<1>(arg));
    }


    for (auto&& th : lstTh) {
        th.join();
    }

    return 0;
}