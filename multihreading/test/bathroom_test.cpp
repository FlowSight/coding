#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include<condition_variable>

using namespace std;

enum Party { NoParty = 0, Democrat, Republican};

struct Person {
    string name;
    int time;
    Party party;
    Person() = default;
    Person(string _n, int _t, Party _p){
        name = _n;
        time = _t;
        party = _p;
    }
};

class BathroomManager {
    public:
    explicit BathroomManager(int _cap,vector<Person> persons){
        cap = _cap;
        for(auto it : persons)timemap[it.name]= it;
        admitterdemo = thread(&BathroomManager::admitDemo,this);
        admitterrepub = thread(&BathroomManager::admitRepub,this);
        toilerprocesser = thread(&BathroomManager::usetoilet,this);
    }

    void addtoqueue(Person p){
        if(p.party == Party::Democrat){
            unique_lock<mutex> ul(mtxdemoq);
            demowait.push(p);
            cvdemowait.notify_one();
        } else {
            unique_lock<mutex> ul(mtxrepubq);
            repubwait.push(p);
            cvrepubwait.notify_one();
        }
    }
    void stop(){
        stopped = true;
        cvusing.notify_all();
        cvdemowait.notify_one();
        cvrepubwait.notify_one();
        if(admitterdemo.joinable()) admitterdemo.join();
        if(admitterrepub.joinable()) admitterrepub.join();
        if(toilerprocesser.joinable()) toilerprocesser.join();
    }

    private :

    void admitDemo(){
        Person p;
        while(true){
            {
                unique_lock<mutex> ul(mtxdemoq);
                cvdemowait.wait(ul,[this]{
                    return stopped || !demowait.empty();
                });
                if(stopped) return;
                p = demowait.front();
                demowait.pop();
                demoCnt++;
                cvdemowait.notify_all();
            }
            {
                unique_lock<mutex> ul1(mtxusing);
                cvusing.wait(ul1,[this]{
                    return stopped || canAdmit(Party::Democrat);
                });
                if(stopped) return;
                usingnow++;
                curparty = Party::Democrat;
                inbathroom.push(p);
                demoCnt--;
                cvusing.notify_all();
            }
        }
    }
    void admitRepub(){
        Person p;
        while(true){
            {
                unique_lock<mutex> ul(mtxrepubq);
                cvrepubwait.wait(ul,[this]{
                    return stopped || !repubwait.empty();
                });
                if(stopped) return;
                p = repubwait.front();
                repubwait.pop();
                repubCnt++;
                cvrepubwait.notify_all();
            }
            {
                unique_lock<mutex> ul1(mtxusing);
                cvusing.wait(ul1,[this]{
                    return stopped || canAdmit(Party::Republican);
                });
                if(stopped) return;
                usingnow++;
                curparty = Party::Republican;
                inbathroom.push(p);
                repubCnt--;
                cvusing.notify_all();
            }
        }

    }

    void usetoilet() {
        Person p;
        while(true){
            {
                unique_lock<mutex> ul1(mtxusing);
                cvusing.wait(ul1,[this]{
                    return stopped || (usingnow >0);
                });
                if(stopped) return;
                p = inbathroom.front();
                inbathroom.pop();
                cvusing.notify_all();
            }
            this_thread::sleep_for(chrono::milliseconds(p.time));
            cout<<"Person :"<<p.name<<" party : "<<p.party<<" is done using washroom"<<endl;
            {
                unique_lock<mutex> ul2(mtxusing);
                usingnow--;
                if(usingnow == 0) {
                    lastParty.store(curparty);
                    curparty =  Party::NoParty;
                }
                cvusing.notify_all();
            }
        }
    }

    bool canAdmit(Party party){
        if(curparty == Party::NoParty) {
            if(party == Party::Democrat){
                if(repubCnt <= 0) return true;
                if((lastParty != Party::Democrat)) return true;
            } else {
                 if(demoCnt <= 0) return true;
                if((lastParty == Party::Democrat)
                    || (lastParty != Party::Republican)) return true;
            }
            return false;
        }
        if(curparty != party) return false;
        if(usingnow >= cap) return false;
        return true;
    }

    int cap;
    atomic<int> usingnow{0}, stopped{0}, demoCnt{0}, repubCnt{0};
    queue<Person> demowait,repubwait;
    queue<Person> inbathroom;
    mutex mtxdemoq, mtxrepubq, mtxusing;
    thread admitterdemo, admitterrepub, toilerprocesser;
    atomic<Party> curparty{Party::NoParty}, lastParty{Party::NoParty};
    condition_variable cvdemowait, cvrepubwait, cvusing;
    unordered_map<string,Person> timemap;
};

void testmethod1(){
    vector<Person> arr = {
        Person("bush",1000,Party::Democrat),
        Person("Obama",150,Party::Republican),
        Person("Trump",8000,Party::Democrat),
        Person("Biden",1500,Party::Republican),
        Person("Lincoin",100,Party::Republican),
        Person("Clinton",2000,Party::Democrat)
    };
    BathroomManager bm(3,arr);
    for(auto it : arr){
        bm.addtoqueue(it);
    }
    this_thread::sleep_for(chrono::milliseconds(50000));
    bm.stop();

}

int main(){
    testmethod1();
    // //testmethod2();
    return 0;
}