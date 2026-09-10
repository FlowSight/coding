/// Severity: Sev2
// Date: 05Sep26
// LC: 2360
// Where I failed: compile error, first approach was unnecessarily complicated
//  because i did textbook tarjan
// Pattern: simplified tarjan
// Notes: additional_notes


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vi disc;
    int ans, time;
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        ans = 0;
        time = 1;
        disc =  vi(n,-1);
        for(auto i=0;i<n;i++){
            if(disc[i] == -1) dfs(edges, i);
        }
        return ans ? ans : -1;
    }
    void dfs(vi& g,int idx){
        disc[idx] = time++;
        if(g[idx] != -1){
            if(disc[g[idx]] == -1){
                dfs(g,g[idx]);
            } else if(disc[g[idx]] >0 ){
                ans = max(ans,disc[idx]-disc[g[idx]]+1);
            }
        }
        disc[idx] = 0;
    }
};