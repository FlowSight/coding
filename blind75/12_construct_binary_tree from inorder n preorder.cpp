// 28 jan 2025..
// 10 mins..
// 1 compiler mistake..bad .. 
// // forgot the O(1) space solution..(TODO)
// verdict : FAIL

    unordered_map<int,int> mm;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        mm.clear();
        int n = preorder.size(), idx = 0;
        for(auto i=0;i<n;i++)mm[inorder[i]] = i;
        return helper(preorder,inorder,idx,0,n-1);
    }

    TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int& idx, int left, int right){
        if(idx >= preorder.size() || (idx<0) || (left > right)) return nullptr;
        auto root = new TreeNode(preorder[idx++]);
        int rootIdx = mm[root->val];
        root->left = helper(preorder,inorder,idx,left,rootIdx-1);
        root->right = helper(preorder,inorder,idx,rootIdx+1,right);
        return root;
    }
};



// 16 dec 2024
// recursive basic sol..6.30 min..no mistake..Verdict : PASS
// time optimization in 30s..Verdict : PASS
// forgot the O(1) solution..(TODO)


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

// iterative
// forgot this completely..(TODO)
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size()==0) return nullptr;
        stack<TreeNode*> st;
        TreeNode* root= new TreeNode(preorder[0]);
        TreeNode* curr = root;
        int n=preorder.size();
        for(int i=1,j=0;i<n;i++)
        {
            if(curr->val!=inorder[j]) 
            {
                curr->left= new TreeNode(preorder[i]);
                st.push(curr);
                curr=curr->left;
            }
            else
            {
                j++;
                while(!st.empty() && st.top()->val==inorder[j])
                    {
                        curr=st.top();
                        st.pop();
                        j++;
                    }
                curr=curr->right = new TreeNode(preorder[i]);
            }
        }
        return root;
    }