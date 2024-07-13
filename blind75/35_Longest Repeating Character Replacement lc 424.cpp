class Solution {
public:
    unordered_map<char,int> cnt;
    int characterReplacement(string s, int k) {
        cnt.clear();
        int n = s.size(), remaining = 0, ans = 0, highest = 0;
        for(auto r = 0, l = 0;r<n;r++){
            cnt[s[r]]++;
            remaining = getRemaining(r-l+1);
            while((remaining > k) && l<r){
                cnt[s[l++]]--;
                remaining = getRemaining(r-l+1);
            }
            if(l<=r)ans = max(ans,r-l+1);
        }
        return ans;
    }

    int getRemaining(int len){
        int high = 0;
        for(auto it : cnt){
            high = max(high,it.second);
        }
        return len-high;
    }
};