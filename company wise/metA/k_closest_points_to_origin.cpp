// 15 jan 2025..
// 5 min
// 1 compiling mistake : revised but didnt do semantic check...
// couldnt think of quick sort way...
// verdict : FAIL

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<double,int>> pq;
        vector<vector<int>> ans;
        int n = points.size();
        for(auto i=0;i<n;i++){
            auto dist = points[i][1]*points[i][1] + points[i][0]*points[i][0];
            pq.push({dist,i});
            if(pq.size() > k)pq.pop();
        }
        while(!pq.empty()){
            ans.push_back(points[pq.top().second]);
            pq.pop();
        }
        return ans;
    }
};

