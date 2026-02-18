//29jan2026..stupid optimization..sev0
// there are at least 2/3 optimization
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size(),ans = INT_MAX, negsum = 0, posSum = 0;
        for(auto it : nums) {
            negsum += min(0,it);
            posSum += max(0,it);
        }
        if((goal <= negsum) || (goal >= posSum)) return min(abs(goal-negsum),abs(posSum-goal));

        vector<int> firstHalfArr = getAllSums(nums,0,n/2),secondHalfArr = getAllSums(nums,n/2+1,n-1);
        int n1 = firstHalfArr.size(), n2 = secondHalfArr.size(), l = 0, r = n2-1;
        while((l<n1) && (r>=0)){
            auto sum = firstHalfArr[l] + secondHalfArr[r];
            ans = min({ans,abs(goal-sum),abs(sum-goal)});
            if(ans == 0) return 0;
            if(sum>goal) r--;
            else l++;
        }
        return ans;
    }

    vector<int> getAllSums(vector<int>& arr, int l, int r){
        unordered_set<int> sums,tmp;
        sums.insert(0);
        for(auto i=l;i<=r;i++){
            tmp = sums;
            for(auto it:sums) tmp.insert(it+arr[i]);
            sums = tmp;
        }
        vector<int> ans(sums.begin(),sums.end());
        sort(ans.begin(),ans.end());
        return ans;
    }
};