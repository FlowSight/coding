// 16/2/25
// 15 min
// didnt read qs first..
// 1 compiler mistake
// verdict : FAIL
// sev1

class Solution {
public:
    vector<vector<int>>  ans;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size(),idx = 0;
        sort(nums.begin(),nums.end());
        vector<int> cur;

        helper(nums,idx,cur,n);
        return ans;
    }

    void helper(vector<int>& nums, int idx, vector<int>& cur, int n){
        if(idx == n){
            ans.push_back(cur);
            return;
        }
        int cnt = 1, num = nums[idx];
        idx++;
        for(;idx<n;idx++){
            if(nums[idx] == nums[idx-1]){
                cnt++;
            } else break;
        }
        helper(nums,idx,cur,n);

        for(auto i=1;i<=cnt;i++){
            cur.push_back(num);
            helper(nums,idx,cur,n);
        }
        for(auto i=1;i<=cnt;i++)cur.pop_back();
    }
};


// iterative..very good sol..
    class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > totalset = {{}};
        sort(S.begin(),S.end());
        for(int i=0; i<S.size();){
            int count = 0; // num of elements are the same
            while(count + i<S.size() && S[count+i]==S[i])  count++;
            int previousN = totalset.size();
            for(int k=0; k<previousN; k++){
                vector<int> instance = totalset[k];
                for(int j=0; j<count; j++){
                    instance.push_back(S[i]);
                    totalset.push_back(instance);
                }
            }
            i += count;
        }
        return totalset;
        }
};