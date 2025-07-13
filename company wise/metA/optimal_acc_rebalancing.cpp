14 june 2025
sev0

//catch is..for idx, give all money to another i, then idx becomes 0, then recurse for idx+1 

class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
       auto balances =  makeBalance(transactions);
       return helper(balances,0,balances.size());
    }

    int helper(vector<int>& balances,int idx, int n){
        while((idx<n) && (balances[idx] == 0)) idx++;
        if(idx == n) return 0;
        int ans = 1e9;
        for(auto i=idx+1;i<n;i++){
            if(balances[i] * balances[idx] >=0) continue;
            balances[i] += balances[idx];
            ans = min(ans,helper(balances,idx+1,n)+1);
            balances[i] -= balances[idx];
        }
        return ans;
    }

    vector<int> makeBalance(vector<vector<int>>& transactions){
        vector<int> ans;
        unordered_map<int,int> mm;
        for(auto it : transactions){
            mm[it[0]] -= it[2];
            mm[it[1]] += it[2];
        }
        for(auto it : mm){
            if(it.second) ans.push_back(it.second);
        }
        return ans;
    }
};

