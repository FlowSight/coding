// LC : 1125

class Solution {
public:
    unordered_map<string,int> mmidx;
    typedef vector<int> vi;
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int m = req_skills.size(), n = people.size();
        for(int i = 0; i < m; i++) mmidx[req_skills[i]] = i;

        int reqbm = (1 << m) - 1;
        vector<vector<int>> dp(reqbm + 1, vi(n+1,-1));
        dp[0] = {};

        for(int i = 0; i < n; i++){
            int curbm = getPersonBm(people[i]);

            for(int mask = reqbm; mask >= 0; mask--){
                if(dp[mask].size() >= (n + 1)) continue;
                int newbm = mask | curbm;
                if(dp[newbm].size() > dp[mask].size() + 1){
                    dp[newbm] = dp[mask];
                    dp[newbm].push_back(i);
                }
            }
        }
        return dp[reqbm];
    }

    int getPersonBm(vector<string> skills){
        int ans = 0;
        for(auto it : skills){
            if(mmidx.find(it) == mmidx.end()) continue;
            ans |= (1<<mmidx[it]);
        }
        return ans;
    }
};
