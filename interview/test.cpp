
#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;


struct UserRankData {
    string userId;
    double avgRating;
    int count;
UserRankData(string _userId, double _avg, int _count){
    count = _count;
    userId = _userId;
    avgRating = _avg;
}

};



class RatingRepo {
    public:
    unordered_map<int,unordered_map<string, pair<int,int>>> ratings; 
    pair<int,int> getRating(string userId, int month) {
        auto it = ratings.find(month);
        if(it == ratings.end()) return {-1,-1};
        auto it1 = ratings[month].find(userId);
        if(it1 == ratings[month].end()) return {-1,-1};
        return ratings[month][userId];
    }

    void updateRating(string userId, int rating, int month) {
        auto it = getRating(userId,month);
        if(it.first ==  -1) {
            ratings[month][userId] = {rating,1};
        } else {
            auto curRating = it.first, curCount = it.second;
            curRating+=rating;
            curCount++;
            ratings[month][userId] = {curRating,curCount};
        }
    }
    unordered_map<string, pair<int,int>> getRatings(int month){
        return ratings[month];
    }
};

class RankingStrategy2 {
    public:
    RatingRepo* repo;
    RankingStrategy2() {
    }

    void doUpdate(RatingRepo* _repo) {
        repo = _repo;
    }

    vector<UserRankData> getAgentRanking(int month){ 
        vector<UserRankData> arr;
        auto ratings = repo->getRatings(month);
        for(auto it : ratings){
            double score = it.second.first, cnt = it.second.second;
            double rating = (double)score/cnt;
            arr.push_back({it.first,rating,(int)cnt});
        }
        sort(arr.begin(),arr.end(),[](UserRankData p1, UserRankData p2){
            if (p1.avgRating == p2.avgRating) return p1.count > p2.count;
            return p1.avgRating > p2.avgRating;
        });
        return arr;
    }
};

class RankingStrategy {
    public:
    RatingRepo* repo;
    RankingStrategy() {
    }

    void doUpdate(RatingRepo* _repo) {
        repo = _repo;
    }

    vector<pair<double,string>> getAgentRanking(int month){ 
        vector<pair<double,string>> arr;
        auto ratings = repo->getRatings(month);
        for(auto it : ratings){
            double score = it.second.first, cnt = it.second.second;
            double rating = (double)score/cnt;
            arr.push_back({rating,it.first});
        }
        sort(arr.begin(),arr.end(),[](pair<double,string> p1, pair<double,string> p2){
            return p1.first > p2.first;
        });
        return arr;
    }
};

class RatingManager {
    RankingStrategy2 strategy;
    RatingRepo repo;
    // {rating,count}
    public:
    RatingManager() {
        strategy.doUpdate(&repo);
    }
    void acceptRating(string userId, int rating, int month){
        repo.updateRating(userId,rating,month);
    }
    vector<UserRankData> getAgentRanking(int month){
        return strategy.getAgentRanking(month);
    }


};

void ratingTester(){
    RatingManager rm;
    rm.acceptRating("abc",1,1);
    rm.acceptRating("abc",2,1);
    rm.acceptRating("abc",4,2);
    rm.acceptRating("xyz",2,1);
    rm.acceptRating("xyz",1,1);
    rm.acceptRating("xyz",2,2);
    //rm.acceptRating("xyz",1);
    rm.acceptRating("anirban",4,1);
    rm.acceptRating("anirban",1,2);
    rm.acceptRating("acd",2,1);
    // for(auto i=0;i<5;i++){
    //     rm.acceptRating("abc",i+1);
    // }
    // for(auto i=0;i<5;i++){
    //     rm.acceptRating("xyz",(i+1));
    // }
    
    // for(auto i=0;i<20;i++){
    //     rm.acceptRating(to_string(i/2),rand()%5+1);
    // }
    auto tmp = rm.getAgentRanking(1);
    for(auto it : tmp){
        cout<<it.userId<<" "<< it.avgRating<<endl;
    }

}

int main(){
    ratingTester();
    return 1;
}

// customer supprot agent
// rate agents
// acceptRating() 1-5 O(1)
// get avergae rating for all agents , ordered by higherst to low 
//     O(nlogn)
// users id : string 

// Ratingmanager 


