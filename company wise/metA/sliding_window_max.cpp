// 6 apr 2025
// 7 min..
// 1 stupid compiler mistake
// sev3


// 27 dec 2024..7.30 mins
// verdict : PASS

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> q;
        vector<int> ans;
        int n = nums.size();
        for(auto r=0;r<n;r++) {
            while(!q.empty() && (nums[q.front()] <= nums[r])){
                q.pop_front();
            }
            q.push_front(r);
            if(q.back() <= r-k) q.pop_back();
            if(r>=k-1) {
                ans.push_back(nums[q.back()]);
            }
        }
        return ans;
    }