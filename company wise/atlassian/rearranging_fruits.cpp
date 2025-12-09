//sev0..8 nov
// sum of eachhas to be even
// each element that has to be moved from A to B, get the swap count = (req-cur_count)/2
// create arr and sort i.e. if 2 needs 2 swap, add 2 2's
// arr size == n. ===> n/2 swaps
// either swap with another higher...or swap twice with absolute min ===> cost = 2*global_min
// BIG CATCH : MINVAL is global min, may not be in swap array i.e. not required to swap.

class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int,int> totalMap,firstMap;
        vector<int> arr;
        long long ans = 0;
        int minVal = INT_MAX;
        for(auto it : basket1) {
            firstMap[it]++;
            totalMap[it]++;
        }
        for(auto it : basket2) {
            totalMap[it]++;
        }
        for(auto it : totalMap){
            minVal = min(minVal,it.first);
            if(it.second %2) return -1;
            int goal = it.second/2, 
                present = (firstMap.find(it.first) == firstMap.end() 
                        ? 0 : firstMap[it.first]),
                gap = abs(goal-present);
            for(auto i=1;i<=gap;i++)arr.push_back(it.first);
        }
        if(arr.size() == 0) return 0;
        sort(arr.begin(),arr.end());
        int swapNeeded = arr.size()/2;
        for(auto i=1;i<=swapNeeded;i++){
            ans += min(arr[i-1],2*minVal);
        }
        return ans;
    }
};
