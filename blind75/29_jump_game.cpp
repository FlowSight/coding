// 2 jan 2025..
// 6 mins
// verdict : PASS

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxJump = 0, n = nums.size();
        for(auto i=0;(i<n)&& (i<=maxJump) && (maxJump<n-1);i++){
            maxJump = max(maxJump,i+nums[i]);
        }
        return maxJump>=n-1;
    }
};


// 14 dec 2024...6 mins..failed in logic check (double check miss) ,...verdict : FAIL
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        for(auto i=0,maxJump = 0;i<n;i++){
            if(i>maxJump) return false;
            maxJump = max(maxJump,i+nums[i]);
            if(maxJump >= n-1) return true;
        }
        return false;
    }
};

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        for(auto i=0,lim = 0;i<=min(n-1,lim);i++){
            lim = max(lim,i+nums[i]);
            if(lim >=n-1)return true;
        }
        return false;
    }
};