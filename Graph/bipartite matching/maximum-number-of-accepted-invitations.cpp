/// Severity: Sev0
// Date: 07Sep26
// LC: 1820
// Where I failed: memset/fill
// Pattern: kuhns bipartite matching
// Notes: additional_notes


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vi matchb,matchg, visited;
    int maximumInvitations(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        matchb = vi(m,-1);
        matchg = vi(n,-1);
        visited = vi(n,0);
        for(auto i=0;i<m;i++){
            fill(visited.begin(),visited.end(),0);
            if(trykuhn(grid,i))ans++;
        }
        return ans;
    }

    bool trykuhn(vvi& grid, int u){
        for(auto i=0;i<grid[u].size();i++){
            if(grid[u][i] && !visited[i]) {
                visited[i] = 1;
                if((matchg[i] == -1) || trykuhn(grid,matchg[i])) {
                    matchb[u] = i;
                    matchg[i] = u;
                    return true;
                }
            }
        }
        return false;
    }
};