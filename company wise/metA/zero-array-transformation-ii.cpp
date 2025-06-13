12 june 2025
sev0..could not do..

// theres a bs sol..which i thought of
// but TODO a O(n+q) sol

    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), qLen = queries.size(), idx = 0,cursum = 0, changed = 0;
        vector<int> variations(n+1,0);

        for(auto i=0;i<n;i++) {
            while(cursum + variations[i] + nums[i] > 0){
                if(idx == queries.size()) return -1;
                auto l = queries[idx][0], r = queries[idx][1], val = queries[idx][2];
                idx++;
                if(r<i) continue;
                variations[max(l,i)] -= val;
                variations[r+1] += val;
            }
            cursum += variations[i];
        }

        return idx;
    }