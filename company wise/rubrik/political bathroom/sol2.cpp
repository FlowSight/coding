#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <numeric>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>
#include <chrono>
#include <unordered_set>


using namespace std;
using Clock = chrono::steady_clock;
using Time = chrono::milliseconds;



enum Party { Democrat = 0, Republican};
struct Person {
    Time timetaken;
    Party party;
    string name;
    Person() = default;
    Person(Time _time, Party _p, string _name){
        timetaken = _time;
        party = _p;
        name = _name;
    }

    bool operator> (const Person& p1) const {
        return timetaken >  p1.timetaken;
    }
};


class BathroomService {
    public:
    explicit BathroomService(int _numth){
        numTh = _numth;
        for(auto i=0;i<numTh;i++)workers.emplace_back(&BathroomService::workerloop,this);
        scheduler = thread(&BathroomService::schedulerfunc,this);
        inwashroom = vector<Person>(3);
    }

    void admit(Person p){
        unique_lock<mutex> ul(mtxDRq);
        if(p.party == 0) {
            demoQueue.push(p);
        }
        else {
            repubQueue.push(p);
        }
        cvScheduler.notify_one();
    }
    void shutdown() {
        stopped.store(true);
        cvworker.notify_all();
        cvScheduler.notify_all();
        for(auto& th : workers){
            if(th.joinable()) th.join();
        }
        if(scheduler.joinable()) scheduler.join();
    }

    ~BathroomService() {
        shutdown();
    }

    private:
    int numTh;
    vector<thread> workers;
    thread scheduler;
    queue<Person> entered;

    priority_queue<Person,vector<Person>,greater<Person>> demoQueue, repubQueue;
    mutex mtxDRq, mtxentered;
    condition_variable cvScheduler, cvworker;
    atomic<bool> stopped{false};
    atomic<int> usingnow{0}, curParty{-1};
    vector<Person> inwashroom;

    void workerloop(){
        Person p;
        while (true)
        {
            {
                unique_lock<mutex> ul1(mtxentered);
                cvworker.wait(ul1,[this] { 
                    return stopped || !entered.empty();
                });
                if(stopped) return;
                p = entered.front();
                entered.pop();
                curParty.store(p.party);
             }

            cout<<"using washroom for "<<p.name<<" for "<< to_string(p.timetaken.count()) <<" ms"<<endl;
            this_thread::sleep_for(p.timetaken);
            cout<<"done using washroom for "<<p.name<<endl;
            {
                unique_lock<mutex> ul2(mtxentered);
                usingnow.fetch_add(-1);
                if(usingnow.load() == 0) curParty.store(-1);
                else curParty.store(p.party);
                cvScheduler.notify_one();
            }
            
        }
    }
    
    // mtxentered : entered, usingnow,curparty
    // mtxdrqueue : pq1, pq2

    void schedulerfunc(){
        Person p;
        bool found = false;
        while(true) {
                {
                    unique_lock<mutex> ul1(mtxentered);
                    cvScheduler.wait(ul1,[this]{
                        if(stopped) return true;
                        return usingnow.load() < 3;
                    });
                    if(stopped) return;
                    while(usingnow.load() < 3){
                        {
                            unique_lock<mutex> ul2(mtxDRq);
                            if(curParty.load() == 0) {
                                
                                if(demoQueue.empty()) break;
                                p = demoQueue.top();
                                demoQueue.pop();
                                found = true;
                            }
                            else if(curParty.load() == 1) {
                                if(repubQueue.empty()) break;
                                p = repubQueue.top();
                                repubQueue.pop();
                                found = true;
                            } else {
                                if(demoQueue.empty() && repubQueue.empty()) break;
                                if(!repubQueue.empty()) {
                                    p = repubQueue.top();
                                    repubQueue.pop();
                                    found = true;
                                } else{
                                    p = demoQueue.top();
                                    demoQueue.pop();
                                    found = true;
                                }
                            }
                            if(found) {
                                entered.push(p);
                                usingnow.fetch_add(1);
                                curParty.store(p.party);
                                cvworker.notify_one();
                            } else {
                                break;
                            }
                            found = false;
                        }
                    }
                }
            }
        }
};


void testmethod1(){
    BathroomService bs(3);
    for(auto i=0;i<5;i++){
        Time time = Time(rand()%1000);
        Party party = rand()%2 ? Party::Republican : Party::Democrat;
        string name = "person"+to_string(i);
        bs.admit(Person(time,party,name));
    }
    this_thread::sleep_for(Time(10000));
    bs.shutdown();
    
}

void testmethod2(){

}

int main(){
    testmethod1();
    //testmethod2();

    return 0;
}