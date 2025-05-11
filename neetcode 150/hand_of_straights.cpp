// 15 mar 2025
// 12 min
// did from airport...fucked up basic stuff..
// also fumbled with the idea, confused between map and set and pq
// sev0

class Solution {
    public:
        bool isNStraightHand(vector<int>& hand, int groupSize) {
            map<int,int> mm;
            int n = hand.size();
            if(n%groupSize) return false;
            
            int time = n/groupSize;
            for(auto it : hand) mm[it]++;
            for(auto i=1;i<=time;i++) {
                auto first = mm.begin()->first;
                mm[first]--;
                if(mm[first] == 0) mm.erase(first);
                for(auto j=1;j<groupSize;j++){
                    auto cur = first+j;
                    if((mm.find(cur) == mm.end() )|| (mm[cur]==0)) return false;
                }
                for(auto j=1;j<groupSize;j++){
                    auto cur = first+j;
                    mm[cur]--;
                    if(mm[cur] == 0)mm.erase(cur);
                }
            }
            return true;
        }
    };
    

    //O(N)  Solution
    bool isNStraightHand(vector<int>& nums, int k) {
        unordered_map<int, int> ctr;
        for (int num : nums)
            ctr[num]++;
        for (int num : nums) {
            int start = num;
            while (ctr[start - 1])
                start--;
            for (; start <= num; start++) {
                int times = ctr[start];
                if (times) {
                    for (int victim = start; victim < start + k; victim++) {
                        if (ctr[victim] < times)
                            return false;
                        ctr[victim] -= times;
                    }
                }
            }
        }
        return true;
    }