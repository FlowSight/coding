/// Severity: Sev0
// Date: 20Jun26
// LC: 1368
// Where I failed: algo..i though dfs would work, in weighted graph dfs doesnt work. i didnt know 0-1 bfs. i though djkstra. which is suboptimal
// Pattern: 01 bfs, modified 01 bfs
// Notes: additional_notes



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dp;
    vvi dirs = {{0,0},{0,1},{0,-1},{1,0},{-1,0}};
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        dp = vvi(m,vi(n,m*n));
        deque<vi> q; // {r,c,cost}
        q.push_front({0,0,0});

        while(!q.empty()){
            auto tp = q.front();
            int r = tp[0], c= tp[1], cost = tp[2];
            q.pop_front();
            if((r== m-1) && (c==n-1)) return cost;
            if(dp[r][c] <= cost) continue;
            dp[r][c] = cost;

            for(auto i=1;i<=4;i++){
                auto xx= dirs[i][0]+r, yy = dirs[i][1]+c;
                if((xx<0) || (xx>=m) || (yy<0) || (yy>=n) || (dp[xx][yy] <= cost+(i!=grid[r][c]))) continue;
                if(i == grid[r][c]) q.push_front({xx,yy,cost});
                else q.push_back({xx,yy,cost+1});
            }
        }
        return m+n;
    }

};
