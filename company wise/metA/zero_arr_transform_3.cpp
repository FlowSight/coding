12 june 2025
could not do..
sev0


class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), q = queries.size(), cnt = 0, idx = 0, prev = 0,ahead = 0;
        sort(queries.begin(),queries.end());
        priority_queue<int,vector<int>,greater<int>> relevant;
        priority_queue<int> available;
        for(auto i=0;i<n;i++){
            while(!relevant.empty() && (relevant.top()<i)) relevant.pop();
            while((idx<q) && (queries[idx][0] <=i)) available.push(queries[idx++][1]);
            while((relevant.size() < nums[i])
                && !available.empty() && (available.top() >= i)) {
                    relevant.push(available.top());
                    available.pop();
                    cnt++;
            }
            if(relevant.size() < nums[i]) return -1;
        }
        return q-cnt;
    }
};