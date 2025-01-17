// 15 dec 2024..3.40 min..3-4 mistake..Verdict : FAIL
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> st;
        long last = LONG_MIN;
        while(!st.empty() || root){
            if(root) {
                st.push(root);
                root = root->left;
            } else {
                auto tp = st.top();
                st.pop();
                if(last >= tp->val) return false;
                last = tp->val;
                root = tp->right;
            }
        }
        return true;
    }
};
// 15 dec 2024..3.40 min...
// 1 mistake : didnt check number limit..int->long.
// Verdict : FAIL

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBSTHelper(root)[0];
    }

    // return type : {valid, min, max}
    vector<long> isValidBSTHelper(TreeNode* root){
        if(!root) return {1,LONG_MAX,LONG_MIN};
        auto ll = isValidBSTHelper(root->left), rr = isValidBSTHelper(root->right);
        int valid =  ll[0] && (ll[2] < root->val) && rr[0] && (rr[1] > root->val);
        return {valid, min({(long)root->val,ll[1],rr[1]}), max({(long)root->val,ll[2],rr[2]}) };
    }
};