//sev0..could not come up with idea
// 6 nov 25

class Solution {
public:
    vector<vector<int>> dirs = {{0,1},{1,0},{-1,0},{0,-1}};
    int minimumTime(vector<vector<int>>& grid) {
        if(grid[0][1] >1 && (grid[1][0]>1)) return -1;
        unordered_set<string> visited;
        priority_queue<vector<int>,vector<vector<int>> , greater<vector<int>>> pq;
        pq.push({grid[0][0],0,0});
        int time = 0, m = grid.size(), n = grid[0].size(), step = 1;
        while(!pq.empty()){
            auto tp = pq.top();
            pq.pop();
            auto time = tp[0], r = tp[1], c = tp[2];
            if((r == m-1) && (c == n-1)) return tp[0];
            if(visited.find(makeKey(r,c)) != visited.end()) continue;
            visited.insert(makeKey(r,c));
            for(auto d : dirs){
                auto xx = d[0]+r, yy = d[1]+c;
                if((xx<0) || (yy<0) || (xx>=m) || (yy>=n) || (visited.find(makeKey(xx,yy)) != visited.end())) continue;
                int newTime = (time+1 >= grid[xx][yy])?time+1:grid[xx][yy] + ((grid[xx][yy] - time)%2 == 0);
                pq.push({newTime,xx,yy});
            }
        }
         return -1;
    }

    string makeKey(int& r, int& c){
        return to_string(r)+"_"+to_string(c);
    }
};


// [0,1,99]
// [3,99,99]
// [4,5,6]

// when at (0,0), we still insert {1,0,1} and {3,1,0} in heap.
// for cell 1,0 it is correct, because, if there is another cell to ping pong with from
// cell 0,0, we can always come back to cell 1,0. 
// And this is true for all cells.