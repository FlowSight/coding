
#include <queue>
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include<nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;


class RateLimiter {
private:
public:
    RateLimiter(long _limit, long _window_seconds) {
        maxReq = _limit;
        window = _window_seconds;
        maxts = 0;
    }

    void hit(string userid, long ts) {
        if(!allowed(userid,ts)) return;
        maxts = ts;
        reqs[userid].push_front(ts);
    }
    bool allowed(string userid, long ts){
        if(reqs.find(userid) == reqs.end()) return true;
        cleanup(userid,ts);
        return reqs[userid].size() < maxReq;
    }

    private:

    void cleanup(string userid, long ts){
        auto& deq = reqs[userid];
        long startwinow = ts - window + 1;
        while(!deq.empty() && (deq.back() < startwinow)) deq.pop_back();
    }
    long maxReq, window, maxts;
    unordered_map<string,deque<long>> reqs;

};

void jsonDemo() {
    json config = {
        {"ttl_ms", 1000},
        {"limit", 5},
        {"users", 
            {
                {"alice", {{"limit",5},{"window",10}}}
            }
        }
    };
    cout<<config.dump(2)<<endl;
    auto users = config["users"];
    if (users.contains("alice")) {
        cout << config["users"]["alice"]["limit"];  // 5
    }
}


void testmethod(){
    RateLimiter limiter(3,10);
    limiter.hit("user_1", 1);
    limiter.hit("user_1", 2);
    cout<<limiter.allowed("user_1", 3)<<endl;
    limiter.hit("user_1", 3);
    cout<<limiter.allowed("user_1", 4)<<endl;
}

int main() {
    jsonDemo();
    cout << "\n--- Rate Limiter Test ---\n";
    //testmethod();
    return 0;
}