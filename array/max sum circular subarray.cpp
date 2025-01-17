class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int maxSubarraySumCircular(vector<int>& nums) {
        int ans = kadane(nums), n = nums.size();
        vi sufMax(n,-100000);
        for(auto i=n-1,cur = 0,curMax = INT_MIN;i>0;i--){
            cur+=nums[i];
            sufMax[i] = max(curMax,cur);
            curMax = max(curMax,cur);
        }
        for(auto i=0,cur = 0,curMax = INT_MIN;i<n-1;i++){
            cur+=nums[i];
            ans = max({ans,cur+sufMax[i+1]});
        }
        return ans;
    }

    int kadane(vector<int>& nums){
        int n = nums.size(), cur = 0, ans = INT_MIN;
        for(auto it : nums){
            cur+=it;
            ans = max({ans,cur,it});
            if(cur<0)cur = 0;
        }
        return ans;
    }
};

//best way...

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int maxSum = INT_MIN, minSum = INT_MAX, maxCur = 0, minCur = 0,tot = 0;
        for(auto it: nums){
            maxCur+=it;
            minCur+=it;

            maxSum = max(maxCur,maxSum);
            minSum = min(minSum,minCur);

            if(maxCur < 0) maxCur = 0;
            if(minCur > 0) minCur = 0;
            tot+=it;
        }
        return maxSum > 0 ? max(maxSum,tot-minSum) : maxSum;
    }
};

// PROOF:

// my proof 

// is there a case where min subarray isnt the middle subarray?
// case 1 : min subarray is smaller than mid subarray
// any element beyond min subarrray, is increasing the sum of min subarray. So it should be part of max subarray pref or suf (violating original condition)
// case 2: min subarray is crossing mid subarray
//     opposite of above exp.

// Lee's proof

// max(prefix+suffix)
// = max(total sum - subarray)
// = total sum + max(-subarray)
// = total sum - min(subarray)