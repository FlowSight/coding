// 16 apr 2025
// did 2-3 logical mistakes..
// while in call..
// stupid
// sev2

// 13 mar 2025
// did whole thing..
// but missed the fact that it can have A=Z also 
// sev1

class Solution {
    public:
        string minWindow(string s, string t) {
            unordered_map<char,int> cnt, cnt1;
            // O(t.size())
            for(auto c: t){
                cnt[c]++;
            }
            int n = s.size(), ansL = -1, ans = n+1;
            for(auto l=0,r=0;r<n;r++){ //O(s.size())
                cnt1[s[r]]++;
                while(covered(cnt,cnt1)){ //O(52)
                    if(ans > r-l+1){
                        ans = r-l+1;
                        ansL = l;
                    }
                    cnt1[s[l++]]--;
                }
            }
            return ansL == -1 ? "" : s.substr(ansL,ans);
        }
        // O(52)
        bool covered(unordered_map<char,int>& cnt1, unordered_map<char,int>& cnt2){
            for(auto it : cnt1){
                if(cnt2.find(it.first) == cnt2.end()) return false;
                if(cnt2[it.first] < it.second) return false;
            }
            return true;
        }
    };



class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size(),ans = n+1, ansL = -1;
        vector<int> freq(256,0), cur(256,0);
        for(auto c: t)freq[c]++;
        for(auto l=0,r=0;r<s.size();r++){
            cur[s[r]]++;
            while(l<r && (cur[s[l]] > freq[s[l]] )){
                cur[s[l]]--;
                l++;
            }
            if(covered(freq,cur) && (r-l+1 < ans)){
                ans = r-l+1;
                ansL = l;
            }
        }
        return ans == n+1 ? "" : s.substr(ansL,ans);
    }

    bool covered(vector<int>& freq, vector<int>& cur){
        for(auto i=0;i<256;i++){
            if(freq[i] > cur[i])return false;
        }
        return true;
    }
};

