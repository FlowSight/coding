
public:
    unordered_map<int,int> mm;
    TreeNode* buildTree(vector<int>& preOrder, vector<int>& inOrder) {
        int n = inOrder.size(), idx = 0;
        for(auto i=0;i<n;i++)mm[inOrder[i]] = i;
        return helper(preOrder,inOrder,idx,0,n-1);
    }

    TreeNode* helper(vector<int>& preOrder, vector<int>& inOrder, int& idx, int l , int r){
        if(l>r)return nullptr;
        auto root = new TreeNode(preOrder[idx]);
        int i = l;
        while((i<=r) && (inOrder[i]!=preOrder[idx]))i++;
        idx++;
        root->left = helper(preOrder,inOrder,idx,l,mm[root->val]-1);
        root->right = helper(preOrder,inOrder,idx,mm[root->val]+1,r);
        return root;
    }

O(n) with no extra space
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int inPos = 0;
        int prePos = 0;
        return build(preorder, inorder, INT_MIN, inPos, prePos);
    }
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int stop, int& inPos, int& prePos){
        if(prePos >= preorder.size()) return NULL;
        if(inorder[inPos] == stop) {inPos++; return NULL;}
        TreeNode* node = new TreeNode(preorder[prePos]);
        prePos++;
        node->left = build(preorder, inorder, node->val, inPos, prePos);
        node->right = build(preorder, inorder, stop , inPos, prePos);
        return node;
    }
};