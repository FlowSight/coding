// 23 apr 2025
// 10 min..
// clean

class Solution {
    public:
        typedef vector<int> vi;
        typedef vector<vi> vvi;
        int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
            vvi g(n,vi());
            for(auto &e : edges){
                auto u = e[0], v = e[1];
                g[u].push_back(v);
                g[v].push_back(u);
            }
            return collect(g,0,-1,hasApple).second;
        }
    
        pair<int,int> collect(vvi& g, int v, int par, vector<bool>& hasApple){
            int steps = 0, apples = hasApple[v];
            for(auto u : g[v]) {
                if(u == par) continue;
                auto cur = collect(g,u,v,hasApple);
                if(cur.first == 0) continue; // no apple in subtree
                apples += cur.first;
                steps = steps + cur.second + 2;
            }
            return {apples, steps};
        }
    };
    
    
    
        // rr = collect(root->right);