// 9 mar 2025
// 25 min..
// 1 compiler error..
// 1 logical error..
// above because i didnt want to double check as time went too high
// sev2

class Twitter {
    public:
        unordered_map<int,vector<vector<int>>> userToTweetMap;
        unordered_map<int,unordered_set<int>> followIn, followOut;
        unordered_map<int,set<pair<int,int>>> feedMap; // ts,tweetid
        int ts;
        Twitter() {
            ts = 0;
            userToTweetMap.clear();
        }
        /// O(no of follower * log(no of posts)) ====to optimize => O(no of follower)
        void postTweet(int userId, int tweetId) { 
            userToTweetMap[userId].push_back({ts,tweetId});
            for(auto it : followIn[userId]) { // no of follower
                feedMap[it].insert({ts,tweetId}); //O(log(no of posts))
            }
            feedMap[userId].insert({ts,tweetId});
            ts++;
        }
        
        // O(10)
        vector<int> getNewsFeed(int userId) {
            vector<int> ans;
            if(feedMap.find(userId) == feedMap.end()) return ans; //O(1)
            if(feedMap[userId].size() == 0) return ans;
    
            auto it = prev(feedMap[userId].end());
            for(auto i=0;i<10;i++) {
                ans.push_back(it->second);
                if (it == feedMap[userId].begin()) break;
                it--;
            }
            return ans;
        }
        
        /// O(no of follower * log(no of posts)) == to do => o(1)
        void follow(int followerId, int followeeId) {
            followIn[followeeId].insert(followerId);
            // pick all tweets of followeeId, put them in feed of followerId
            for(auto it : userToTweetMap[followeeId]) { // O(no of follower)
                feedMap[followerId].insert({it[0],it[1]}); // //O(log(no of posts))
            }
        }
        
        /// O(no of follower * log(no of posts)) == to do => o(1)
        void unfollow(int followerId, int followeeId) {
            followIn[followeeId].erase(followerId);
            for(auto it : userToTweetMap[followeeId]) {
                feedMap[followerId].erase({it[0],it[1]});
            }
        }
    };
    
    /**
     * Your Twitter object will be instantiated and called as such:
     * Twitter* obj = new Twitter();
     * obj->postTweet(userId,tweetId);
     * vector<int> param_2 = obj->getNewsFeed(userId);
     * obj->follow(followerId,followeeId);
     * obj->unfollow(followerId,followeeId);
     */