// 16/2/25
// 17 min .
// 1 compiler mistake
// sev1

class Solution {
public:
    vector<vector<string>> ans;
    vector<vector<int>> dp;
    vector<vector<string>> partition(string s) {
        int n = s.size(), idx = 0;
        dp = vector<vector<int>>(n,vector<int>(n,0));
        
        for(auto i=0;i<n;i++)dp[i][i] = 1;
        for(auto len=2;len<=n;len++){
            for(auto i=0;i+len-1<n;i++){
                if(len == 2)dp[i][i+len-1] = (s[i]==s[i+len-1]);
                else dp[i][i+len-1] = (s[i]==s[i+len-1]) ? dp[i+1][i+len-2] : 0;
            }
        }

        vector<int> cur;
        helper(s,idx,cur,n);

        return ans;
    }
    void helper(string& s, int idx, vector<int>& cur,int& n){
        if(idx == n){
            vector<string> cur_ans;
            int start = 0;
            for(auto it : cur){
                cur_ans.push_back(s.substr(start,it-start+1));
                start = it+1;
            }
            ans.push_back(cur_ans);
            return;
        }
        for(auto i=idx;i<n;i++){
            if(dp[idx][i]) {
                cur.push_back(i);
                helper(s,i+1,cur,n);
                cur.pop_back();
            }
        }
    }
};