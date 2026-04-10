#include<iostream>
#include<set>

using namespace std;

typedef vector<string> vs;
typedef vector<vs> vvs;

struct User
{
    string name, plan;
    int date, duration;
    User() = default;
    User(string _n,string _p,int _d,int _du ){
        name = _n, plan = _p;
        date = _d, duration = _du; 
    }
};


struct PlanChange
{
    string name, plan;
    int date;
    PlanChange() = default;
    PlanChange(string _n,string _p,int _d ){
        name = _n, plan = _p;
        date = _d;
    }
    bool operator< (PlanChange p) const {
        return date < p.date;
    }
};

struct Schedule
{
    string start, end;
    unordered_map<int,string> customs;
    Schedule() = default;
    Schedule(string _s,string _e,vector<string> arr){
       start = _s, end = _e;
       for(auto i=0;i<arr.size();i++){
        if(i%2) customs[stoi(arr[i-1])] = arr[i];
       }
    }
};

struct cmp {
    bool operator() (vs v1, vs v2) const {
            int i1 = stoi(v1[0]), i2 = stoi(v2[0]);
            return i1<i2;
    }
};
class EmailNotifManager{
    public:
    EmailNotifManager() = default;
    void send_emails(vector<User> users, Schedule sc,vector<PlanChange> pc) {
        multiset<vs,cmp> ss;
        for(auto it : users)usermap[it.name] = it;
        for(auto it : pc) {
            planchangemap[it.name].push_back(it);
            ss.insert({to_string(it.date),"Changed",it.name,it.plan});
        } 
        for(auto it : users){
            int date = it.date;
            auto name = it.name;
            string plan = getCurPlan(name,date), origplan = it.plan;
            int changed = (plan != origplan);
            ss.insert({to_string(date),sc.start,name,plan});

            date = it.date+it.duration;
            plan = getCurPlan(name,date);
            ss.insert({to_string(date),sc.end,name,plan});

            for(auto it1 : sc.customs){
                date = it.date+it.duration+it1.first;
                plan = getCurPlan(name,date);
                ss.insert({to_string(date),it1.second,name,plan});
            }
        }
        for(auto it : ss){
            cout<<it[0]<<": ["<<it[1]<<"] Subscription for "<<it[2]<<" ("<<it[3]<<")"<<endl;
        }
    }

    string getCurPlan(string name, int day){
        string plan = usermap[name].plan;
        auto it = planchangemap.find(name);
        if(it == planchangemap.end()) return plan;
        for(auto it1 : planchangemap[name]){
            if(it1.date > day) break;
            plan = it1.plan;
        }
        return plan;

    }
    unordered_map<string,vector<PlanChange>> planchangemap;
    unordered_map<string,User> usermap;

};

void testmethod(){
    EmailNotifManager enm;
    vector<User> users = {
        User("John","Silver",0,30),
        User("Alice","Gold",1,15),
    };
    vs arr = {"-15","Upcoming expiration"};
    vector<PlanChange> plans = {
        PlanChange("John","Gold",5)
    };
    Schedule sc("Welcome","Expired",arr);
    enm.send_emails(users,sc,plans);
}


int main(){
    testmethod();
    return 0;
}

//  dupe user? many plans? yes


//  save rule 
//  per user plan + (acc date,duration)
//  per user:
//     add notif events in set ordered 
//     iterate over set + print