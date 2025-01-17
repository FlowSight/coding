class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    bool isBipartite(vector<vector<int>>& g) {
        int n = g.size();
        vi visited(n,0);
        for(auto i=0;i<n;i++){
            if(!visited[i] && !isBipartite(i,g,visited,1))return false;
        }
        return true;
    }
    bool isBipartite(int idx, vvi& g, vi& visited, int color){
        if(visited[idx]){
            return visited[idx] == color;
        }
        visited[idx] = color;
        for(auto v : g[idx]){
            if(!isBipartite(v,g,visited,-color))return false;
        }
        return true;
    }
};
