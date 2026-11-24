/// Severity: Sev0
// Date: 15Nov26
// LC: 778
// Where I failed: overcomplicated
// Pattern: dijkstra and bin search
// Notes: we just need to get reachability.next smaller val cell will reach us there but max of all cells in path
// is the ans. 
// if the qs was get shortest path (with earlist day) : get day, then bfs



// 8 june 2025
// textbook dijsktra..

// 15 nov 2026
// forgot algo..redid after reading...
// sev0..sev0...sev0..
typedef vector<int> vi;
typedef vector<vi> vvi;
vvi dirs = {{0,1},{1,0},{-1,0},{0,-1}};
class Solution {
public:
    struct Cell {
        public:
        int r , c, val;
        Cell(int _r, int _c, int _val) {
            r = _r, c = _c, val = _val;
        }
        bool operator< (const Cell& cell) const {
            return this->val > cell.val;
        }
    };
    int swimInWater(vector<vector<int>>& grid) {
        priority_queue<Cell> pq;
        int m = grid.size(), n = grid[0].size(), ans = grid[0][0];
        pq.push(Cell({0,0,grid[0][0]}));
        grid[0][0] = -1;
        while(!pq.empty()) {
            auto tp = pq.top();
            pq.pop();
            auto r = tp.r, c = tp.c, val = tp.val;
            ans = max(ans,val);
            if((r== m-1) && (c == n-1)) break;
            for(auto d : dirs){
                auto xx = d[0] + r, yy = d[1] + c;
                if((xx<0) || (xx >=m) || (yy<0) || (yy>=n) || (grid[xx][yy] <0)) continue;
                pq.push(Cell({xx,yy,grid[xx][yy]}));
                grid[xx][yy] = -1;
            }
        }
        return ans;
    }
};


// 23 mar 2025..
// 17 mins..didnt do a optimization..so got tle at first..
// sev2


class Solution {
    public:
        vector<vector<int>> dirs = {{0,1},{1,0},{-1,0},{0,-1}};
        int swimInWater(vector<vector<int>>& grid) {
            int n = grid.size();
            priority_queue<vector<int>> pq; //{cost,i,j}
            vector<vector<int>> visited;
    
            pq.push({-grid[0][0],0,0});
            while(!pq.empty()){
                auto tp = pq.top();
                pq.pop();
    
                auto time = -tp[0], x = tp[1], y = tp[2];
                if((x==n-1) && (y==n-1)) return time;
    
                if(grid[x][y] == -1)continue;
                grid[x][y] = -1;
                
                for(auto d: dirs){
                    auto xx = d[0]+x, yy = d[1] + y;
                    if((xx<0) || (yy<0) || (xx>=n) || (yy>=n) || (grid[xx][yy] == -1)) continue;
                    auto timeToSwim = max(time,grid[xx][yy]);
                    pq.push({-timeToSwim,xx,yy});
                }
            }
            return -1;
        }
    };