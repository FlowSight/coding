#include<stack>
#include<iostream>

using namespace std;

struct TreeNode {
    public:
    int val;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _val, TreeNode* _left, TreeNode* _right){
        left = _left;
        right = _right;
        val = _val;
    }
};


class Solution {
    Solution();
    void traversal(TreeNode* root){
        TreeNode* par = nullptr;
        TreeNode* lastPop = nullptr;
        stack<TreeNode*> st;
        while(root || par){
            if(root){
                par = root;
                root = root->left;
            } else {
                root = st.top();
                if(!root->right || (lastPop == root->right)){
                    lastPop = root;
                    par = par->parent;
                    cout<<root->val<<" ";
                    root = nullptr;
                } else {
                    root = par->right;
                }
            }
        }
    }
};