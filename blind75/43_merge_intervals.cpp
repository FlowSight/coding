class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& arr) {
        arr.push_back({INT_MAX,INT_MAX});
        sort(arr.begin(),arr.end(),[](const vector<int>& v1, const vector<int>& v2) {
            return v1[0] < v2[0];
        });
        int n = arr.size(), curStart = arr[0][0],curEnd = arr[0][1];
        vector<vector<int>>  ans;
        for(auto i=1; i<n; i++){
            if(curEnd >= arr[i][0]) curEnd = max(curEnd,arr[i][1]);
            else {
                ans.push_back({curStart,curEnd});
                curStart = arr[i][0];
                curEnd = arr[i][1];
            }
        }
        //ans.push_back({curStart,curEnd});
        return ans;
    }
};
