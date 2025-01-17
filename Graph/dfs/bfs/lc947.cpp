class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi g;
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();a
        g = vvi(n);
        unordered_map<int,vi> xCord, yCord;
        for(auto i = 0;i<n;i++) {
            xCord[stones[i][0]].push_back(i);
            yCord[stones[i][1]].push_back(i);
        }
        for(auto& it : xCord){
            for(auto i=0;i<it.second.size()-1;i++){
                g[it.second[i]].push_back(it.second[i+1]);
                g[it.second[i+1]].push_back(it.second[i]);
            }
        }
        for(auto& it : yCord){
            for(auto i=0;i<it.second.size()-1;i++){
                g[it.second[i]].push_back(it.second[i+1]);
                g[it.second[i+1]].push_back(it.second[i]);
            }
        }
        int ans = 0;
        vi visited(n,0);
        for(auto i=0;i<n;i++){
            int cnt = 0;
            dfs(i,visited,cnt);
            ans += max(0,cnt-1);
        }
        return ans;
    }

    void dfs(int idx, vi& visited, int& cnt){
        if(visited[idx])return;
        visited[idx] = 1;
        cnt++;
        for(auto v : g[idx]){
            dfs(v,visited,cnt);
        }
    }
};
