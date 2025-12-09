#include<mutex>
#include<iostream>
#include<vector>
#include<thread>

using namespace std;

mutex mtx; 

int var = 0;

void testFuncEven(){
    mtx.lock();
    for(auto i=0;i<10;i+=2)var+=i;
    cout<<"From even: "<<var<<endl;
    mtx.unlock();
}

void testFuncOdd(){
    mtx.lock();
    for(auto i=1;i<10;i+=2)var+=i;
    cout<<"From odd: "<<var<<endl;
    mtx.unlock();
}

namespace interview {

enum StrategyConfig {
    FixedWindow,SlidingWindow
};

struct UserData {
    public:
    int curWindow, curCount, limit;
    string userId;
    UserData(string _userId = "NA", int _curWindow = 0, int _curCount = 0, int _limit = 0) {
        userId = _userId;
        curWindow = _curWindow;
        curCount = _curCount;
        limit = _limit;
    }
};

struct UserConfig {
    string userId;
    StrategyConfig config;
    int limit;
    public:
    UserConfig(string _userId = "NA", StrategyConfig _config = StrategyConfig::FixedWindow,int _limit = 0) {
        userId = _userId;
        config = _config;
        limit = _limit;
    }
};

class UserDataRepository {
    unordered_map<string,UserData>  dataMap;
    unordered_map<string,UserConfig>  configMap;
    public:
    UserData getUserData(string userId){
        auto it = dataMap.find(userId);
        if(it == dataMap.end()) return UserData();
        return it->second;
    }
    void insertUserData(UserData ud){
        auto userId = ud.userId;
        dataMap[userId] = ud;
    }

    bool updateUserData(string userId, UserData ud){
        dataMap[userId] = ud;
        return true;
    }

    UserConfig getUserConfig(string userId){

    }
    void insertUserConfig(string userId, UserConfig uc){

    }

    bool updateUserConfig(string userId, UserConfig uc){

    }
};

class RateLimitManager {
    UserDataRepository userDataRepo;
    public:
    bool acceptReq(string userId, int ts){
        if(!canAccept(userId,ts)) return false;
        auto ud = userDataRepo.getUserData(userId);
        auto curWindow = ud.curWindow, curCount = ud.curCount, 
            window = ts/10, limit = ud.limit;
        if(window == curWindow){
            if(curCount >= limit) return false;
            curCount++;
            ud.curCount = curCount;
        } else {
            ud.curWindow = window;
            ud.curCount = 1;
        }
        userDataRepo.updateUserData(userId,ud);
        return true;
    }

    bool canAccept(string userId, int ts){
        auto ud = userDataRepo.getUserData(userId);
        if(ud.userId == "NA") return false;
        auto curWindow = ud.curWindow, curCount = ud.curCount, 
            window = ts/10, limit = ud.limit; 
        return curCount < limit;
    }

    bool registerReq(string userId, UserConfig config){
        userDataRepo.updateUserConfig(userId,config);
        userDataRepo.insertUserData(UserData(userId,0,0,config.limit));
    }
};

void testRateLimiting() {
    RateLimitManager rm;
    rm.registerReq("Anirban",UserConfig("Anirban",StrategyConfig::FixedWindow,5));
    for(auto i=0;i<6;i++){
        cout<<rm.acceptReq("Anirban",i)<<endl;
    }
}

};
int main(){
    interview::testRateLimiting();

    return 1;
}

