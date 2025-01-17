// 14jan 2025
// 5 min..
// in my way..didnt use sort by second element 
// verdict : PASS
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(),points.end(),[](const vector<int>& v1, const vector<int>& v2){
            return v1[0]<v2[0];
        });
        int ans = 0, cur = points[0][1], n = points.size();
        for(auto i=1;i<n;i++){
            if(cur >= points[i][0]){
                cur = min(cur,points[i][1]);
            } else {
                ans++;
                cur = points[i][1];
            }
        }
        ans++;
        return ans;
    }


class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(),points.end(),[](const vector<int>& p1, const vector<int>& p2){
            return p1[1] < p2[1];
        });
        int n = points.size(), cnt = 1, hitPoint = points[0][1];
        for(auto i=1;i<n;i++){
            if(points[i][0] <= hitPoint)continue;
            else {
                cnt++;
                hitPoint = points[i][1];
            }
        }
        return cnt;
    }
};


// could not think of the actual solution...was unclear on whether the intersection hitting was allowed.
