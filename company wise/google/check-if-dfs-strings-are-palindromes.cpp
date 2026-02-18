/// Severity: Sev0..sev0
// Date: 16Feb26
// 
// How much solved: Fully
// Where I failed: algo
// Pattern: manachar
// Notes: additional_notes



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi g, limits;
    
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int idx = 0, n = s.size(), pos = 0;
        vector<bool> ans(n,false);
        string dfsString = string(2*n+1,'#');
        limits = vvi(n,vi());
        g = vvi(n,vi());
        for(auto i=1;i<n;i++)g[parent[i]].push_back(i);
        
        // gwt the whole string
        dfs(parent,dfsString,s,idx,pos);
        auto manch = manachar(dfsString);
        for(auto i=0;i<n;i++){
            auto l = limits[i][0], r = limits[i][1];
            int mid = (l+r)/2;
            ans[i] = (manch[mid] >= (r-l)/2);
        }
        return ans;
    }

    void dfs(vi& par, string& dfsString, string& color, int& idx, int& pos){
        int l = 2*pos+1;
        for(auto v : g[idx]) dfs(par,dfsString,color, v,pos);
        dfsString[2*pos+1] = color[idx];
        limits[idx] = {l,2*pos+1};
        pos++;
    }

    vi manachar(string& str){
        int n = str.size(), right = 0, center = 0;
        vi dp(n,0);
        for(auto i=1;i<n;i++){
            if(right >i) dp[i] = min({right-i,dp[2*center-i]});
            while((i+dp[i]+1<n) && (i-dp[i]-1 >=0) && (str[i+dp[i]+1] == str[i-dp[i]-1])) dp[i]++;
            if(i+dp[i] > right){
                right = i+dp[i];
                center = i;
            }
        }
        return dp;
    }
};
