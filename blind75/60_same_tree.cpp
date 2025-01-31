// 28 jan 2025..
// 7 min...
// 2 compiler error..
// verdict : FAIL

    bool isSameTree(TreeNode* p, TreeNode* q) {
        vector<TreeNode*> st1, st2;
        while((p || q) || (!st1.empty() || !st2.empty())) {
            if(p || q){
                if(p && !q) return false;
                if(!p && q) return false;
                if(p->val != q->val) return false;

                st1.push_back(p);
                st2.push_back(q);

                p = p->left;
                q = q->left;
            } else {
                if(st1.empty() && !st2.empty()) return false;
                if(!st1.empty() && st2.empty()) return false;

                p = st1.back();
                q = st2.back();
                st1.pop_back();
                st2.pop_back();

                p = p->right;
                q = q->right;
            }
        }
        return true;
    }
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        stack<TreeNode*> st1,st2;
        while((!st1.empty() || p) && (!st2.empty() || q)) {
            if((p && !q )|| (q && !p))return false;
            if(p){
                if(p->val != q->val)return false;
                st1.push(p);
                p = p->left;
                st2.push(q);
                q = q->left;
            } else {
                p = st1.top();
                st1.pop();
                p = p->right;

                q = st2.top();
                st2.pop();
                q = q->right;
            }
        }
        return (!p && !q) || ((p && q) && (p->val == q->val));
    }
};


////////////

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p && !q)return true;
        if(!p || !q)return false;
        return (p->val == q->val) && isSameTree(p->left,q->left) && isSameTree(p->right,q->right);
    }
};