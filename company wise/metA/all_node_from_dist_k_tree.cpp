// gayer jor e kora basically..
// O(1) space is tricky
// sev0 sev0

// 12 june 2025
// good
// I did it on O(1) space..O(n) time..

class Solution {
public:
    vector<int> ans;
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        helper(root,target,k);
        return ans;
    }

    int helper(TreeNode* root, TreeNode* target, int k){
        int res = -1;
        if(!root) return res;
        if(root == target) {
            helper2(root,k,0);
            return 0;
        }
        auto ll = helper(root->left, target,k), 
            rr = helper(root->right, target,k);
        if(ll != -1) {
            if(ll +1 == k) {
                ans.push_back(root->val);
                return ll+1;
            }
            helper2(root->right,k,ll+2);
            return ll+1;
        }
        if(rr != -1) {
            if(rr +1 == k) {
                ans.push_back(root->val);
                return rr+1;
            }
            helper2(root->left,k,rr+2);
            return rr+1;
        }
        return -1;
    }

    void helper2(TreeNode* root, int k, int dist){
        if(!root) return;
        if(dist > k) return;
        if(dist == k) {
            ans.push_back(root->val);
            return;
        }
        helper2(root->left,k,dist+1);
        helper2(root->right,k,dist+1);
    }
};

// for a node
// tartget can be in left or right subtree
// if it is in any. subtree, the recursion will return distance of root->left/right to target
// we do call both helper(left) helper(rght)
// then if any is a number >=0, then call the other child with helper2(child,dist+2)
// helper2 will go upto depth k


find all nodes at distance k from target node in tree 
