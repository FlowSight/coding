// 7 feb 2025
// 15 min
// i major base case mistake..
// sev1
// verdict : FAIL 

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi ans;
    vector<vector<int>> combinationSum2(vector<int>& arr, int target) {
        sort(arr.begin(),arr.end());
        vi tmp;
        combinationSum2Util(arr,target,0,tmp);
        return ans;
    }

    void combinationSum2Util(vi& arr, int target, int idx, vi& cur){
        if(target == 0){
            ans.push_back(cur);
            return;
        }
        if(target<0)return;
        for(auto firstTime = 1,i=idx;i<arr.size();i++){
            if(i && arr[i] == arr[i-1] && !firstTime)continue;
            firstTime = 0;
            cur.push_back(arr[i]);
            combinationSum2Util(arr,target-arr[i],i+1,cur);
            cur.pop_back();
        }   
    }
};

