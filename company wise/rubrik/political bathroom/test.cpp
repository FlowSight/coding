#include <bits/stdc++.h>
using namespace std;

enum Party { NoParty = -1, Demo = 1, Repub = 2};

class PoliticalBathroom{
    public:
    explicit PoliticalBathroom() {}

    // blocks until the person can enter, uses the bathroom for durationMs, then exits
    void useBathroom(string name, Party party, int durationMs) {
        {
            unique_lock<mutex> ul(mtx);
            cv.wait(ul,[this,party]{
                return (curparty.load() == Party::NoParty) ||
                    ((curparty.load() == party) && (curepochcnt.load() < 3)) ||
                    ((curparty.load() != party) && (curepochcnt.load() == 3) && (curcount.load() == 0)) ;
            });
            if(curparty.load() == party) {
                curepochcnt.fetch_add(1);
                curcount.fetch_add(1);
            } else {
                curepochcnt.store(1);
                curcount.store(1);
                curparty.store(party);
                cv.notify_all();
            }
        }

        cout<<"using bathroom for person: "<< name<<" party: "<<party<<endl;
        this_thread::sleep_for(chrono::milliseconds(durationMs));
        {
            unique_lock<mutex> ul(mtx);
            if(curcount.fetch_sub(1) == 1){
                curparty.store(Party::NoParty);
            }
            cv.notify_all();
            cout<<"Exiting bathroom for person: "<< name<<" party: "<<party<<endl;
        }
    }

    private:
    condition_variable cv;
    mutex mtx;
    atomic<Party> curparty{Party::NoParty};
    atomic<int> curcount{0}, curepochcnt{0};
};







// max 3 people
// no mixing of parties
// optimal scheduling


// atomic curusing, curparty;