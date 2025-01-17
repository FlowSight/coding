// 17 jan 2025..11 mins.. 
// 2 compiler mistakess..didnt check..
// 1 logical mistake : didnt check..
// verdict : FAIL

    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vi ans;
        int dirIdx = 0, x = 0, y = 0, m = matrix.size(), n = matrix[0].size();
        while(!isInvalid(matrix,x,y,m,n)){
            ans.push_back(matrix[x][y]);
            matrix[x][y] = 101;
            auto xx = x+dirs[dirIdx][0] , yy = y+dirs[dirIdx][1];
            if(isInvalid(matrix, xx,yy,m,n)){
                dirIdx = (dirIdx+1)%4;
            }
            x += dirs[dirIdx][0];
            y += dirs[dirIdx][1];
        }
        return ans;
    }

    bool isInvalid(vvi& matrix,int xx, int yy, int m, int n){
        return xx<0 || yy <0 || xx>=m || yy>=n || matrix[xx][yy] > 100;
    }


typedef vector<int> vi;
typedef vector<vi> vvi;
class Solution {
public:
    vvi dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(),idx = 0;
        vi next = {0,0};
        vi ans;
        while(next[0] >=0 && next[0] < m && next[1] >= 0 && next[1] < n && matrix[next[0]][next[1]] != -101) {
            ans.push_back(matrix[next[0]][next[1]]);
            matrix[next[0]][next[1]] = -101;
            vi tmp = getNext(next,idx);
            if(tmp[0] <0 || tmp[0] >= m || tmp[1] <0 || tmp[1] >=n || (matrix[tmp[0]][tmp[1]] == -101)){
                idx = (idx+1)%4;
                next = getNext(next,idx);
            } else {
                next = tmp;
            }
        }
        return ans;
    }

    vi getNext(vi& next, int idx){
        vi ans = next;
        ans[0] += dirs[idx][0];
        ans[1] += dirs[idx][1];
        return ans;
    }
};