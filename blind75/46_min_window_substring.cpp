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

