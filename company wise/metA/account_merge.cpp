// sev0..did miss n+m based index

// 22 apr 2025..
// didnt read that we have to return in sorted order..+ 20 mins
// sev2

// the issue with this qs is that it takes time to implement union find, and index manipulation  + result processing is tricky

class UnionFind {
    public:
    int n;
    vector<int> par;

    UnionFind(int _n) {
        n = _n;
        for(auto i=0;i<n;i++) par.push_back(i);
    }

    int find(int u){
        return par[u] == u ? u : find(par[u]);
    }
    
    void add(int u, int v) {
        auto px = find(u), py = find(v);
        par[px] = py;
    }
};


class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size(), tot = n;
        unordered_map<string,int> emailIdx;
        unordered_map<int,set<string>> res;
        vector<vector<string>> ans;

        for(auto it : accounts) {
            for(auto i=1;i<it.size();i++){
                if(emailIdx.find(it[i]) == emailIdx.end()) {
                    emailIdx[it[i]] = tot++;
                }
            }
        }

        UnionFind uf = UnionFind(tot);

        for(auto i=0;i<n;i++) {
            for(auto j=1;j<accounts[i].size();j++){
                int idx = emailIdx[accounts[i][j]], 
                    par = uf.find(idx);
                uf.add(par,i);
            }
        }
        for(auto it : emailIdx) {
            auto par = uf.find(it.second);
            res[par].insert(it.first);
        }
        for(auto it : res){
            ans.push_back({});
            string name = accounts[it.first][0];
            ans.back().push_back(name);
            for(auto it1: it.second) {
                ans.back().push_back(it1);
            }
        }
        return ans;
    }
};