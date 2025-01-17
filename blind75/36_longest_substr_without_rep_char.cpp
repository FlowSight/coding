// 26 dec 2024..6 mins..
// silly logic mistake in the end..
// verdict : FAIL
    int lengthOfLongestSubstring(string s) {
        int n = s.size(), ans = 0;
        unordered_map<int,int> mm;
        for(auto i=0,l = 0;i<n;i++){
            mm[s[i]]++;
            while((mm[s[i]] > 1) && (l<i)) {
                mm[s[l++]]--;
            }
            ans = max(ans,i-l+1);
        }
        return ans;
    }


// 1nov 2024..3 mins..no mistakes
    int lengthOfLongestSubstring(string s) {
        int n = s.size(), ans = 0;
        unordered_map<char,int> mm;
        for(auto l=0,r=0;r<n;r++){
            mm[s[r]]++;
            while(mm[s[r]] > 1 && l<r) {
                mm[s[l]]--;
                l++;
            }
            ans = max(ans,r-l+1);
        }
        return ans;
    }

    
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