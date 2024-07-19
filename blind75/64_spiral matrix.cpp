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