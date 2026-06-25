class TweetCounts {
public: 
    unordered_map<string,multiset<int>> tweettsmap;
    unordered_map<string,unordered_map<int,int>> tweetminbucket,tweethrbucket,tweetdaybucket; 
    TweetCounts() {
        
    }
    
    void recordTweet(string tweetName, int time) {
        tweettsmap[tweetName].insert(time);
        int minbucket = (time/60)*60, hrbucket = (time/3600)*3600, daybucket = (time/86400)*86400;
        tweetminbucket[tweetName][minbucket]++;
        tweethrbucket[tweetName][hrbucket]++;
        tweetdaybucket[tweetName][daybucket]++;
    }
    
    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int start, int end) {
        vector<int> ans;
        if(tweettsmap.find(tweetName) == tweettsmap.end()) return ans;
        auto ss = tweettsmap[tweetName];
        int bucketgran = (freq == "minute" ? 60 : (freq == "hour" ? 3600 : 86400)), l = start, r = end;
        auto bucketmap = (freq == "minute" ? tweetminbucket : (freq == "hour" ? tweethrbucket : tweetdaybucket));
        while (l<=end) {
            int bucket = (l/bucketgran)*bucketgran, nextbucket = bucket + bucketgran;
            l = max(l,bucket);
            r = min(end,nextbucket-1);
            // if bucket start and covers whole bucket
            if((r-l+1==bucketgran)){
                ans.push_back(bucketmap[tweetName][bucket]);
            } else {
                auto it = ss.lower_bound(l);
                int cur = 0;
                while((it != ss.end()) && (*(it) <= r)) {
                    cur++;
                    it++;
                }
                ans.push_back(cur);
            }
            l = r+1;
        }
        return ans;
    }
};

// 100 1100
// 100-159 160-219

// 0: 60 : 120 : 
// tweet3:{0,10,60}
// 0-60
// 0-59,60-60