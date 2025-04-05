// 29 mar 2025..
// 8 min..no mistake..
// didnt think of union find..
// sev3

class Solution {
    public:
        typedef vector<int> vi;
        typedef vector<vi> vvi;
        vvi g;
        vi visited;
        bool validTree(int n, vector<vector<int>>& edges) {
            g = vvi(n,vi());
            visited = vi(n,0);
            for(auto &it : edges){
                g[it[0]].push_back(it[1]);
                g[it[1]].push_back(it[0]);
            }
            int seenCnt = 0, idx = 0, par = -1;
            if(isCycle(idx,par,seenCnt)) return false;
            return seenCnt == n;
        }
    
        bool isCycle(int& idx, int& par,int& seenCnt){
            if(visited[idx]) return true;
            visited[idx] = true;
            seenCnt++;
            for(auto &v : g[idx]){
                if(par == v) continue;
                if(isCycle(v,idx,seenCnt)) return true;
            }
            return false;
        }
    };
    