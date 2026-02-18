//29jan26..
// n^2: corner case miss 
// O(n) time n space : pass all 
// iterative : sev0..could not
//sev0
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        int n = preorder.size(), idx = 0;
        return helper(preorder,idx,INT_MIN,INT_MAX);
    }
    bool helper(vector<int>& arr, int& idx, int low, int high){
        if(idx>=arr.size()) return true;
        auto root = arr[idx];
        if((root<=low )|| (root>=high)) return false;
        idx++;
        helper(arr,idx,low,root);
        return helper(arr,idx,root,high);
    }
};
