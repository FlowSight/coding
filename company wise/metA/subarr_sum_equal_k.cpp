// 11 jan 2025..
// stupidly did..didnt check corner cases
// plus 1 compiler error..was half asleep
// verdict : FAIL
    int subarraySum(vector<int>& nums, int k) {
        int  cur = 0, ans = 0;
        unordered_map<int,int> mm;
        mm[0]=1;
        for(auto &it : nums){
            cur+=it;
            int rem = cur-k;
            if(mm.find(rem)!=mm.end()) ans+=mm[rem];
            mm[cur]++;
        }
        return ans;
    }
};