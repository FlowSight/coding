class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> occ;
        int n = s.size(), ans = 0;
        for(auto l=0,r=0;r<n;r++){
            if(occ.find(s[r]) != occ.end()){
                  while((l<r) && (s[l] != s[r])) {
                    occ.erase(s[l++]);
                  }
                  occ.erase(s[l++]);
            }
            occ[s[r]] = r;
            ans = max(ans, r-l+1);
        }
        return ans;
    }
};

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size(), ans = INT_MIN, cur = 0;
        for(auto i=0;i<n;i++){
            cur+=nums[i];
            ans = max({ans,cur});
            if(cur<0)cur = 0;
        }
        return ans;
    }
};