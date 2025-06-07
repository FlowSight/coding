// 4 june 2025
// sev0..could not think of lees way..my way had many cases missed

   // lee solution
   int res = 0;
    int minCameraCover(TreeNode* root) {
        return (dfs(root) < 1 ? 1 : 0) + res;
    }

    int dfs(TreeNode* root) {
        if (!root) return 2;
        int left = dfs(root->left), right = dfs(root->right);
        if (left == 0 || right == 0) {
            res++;
            return 1;
        }
        return left == 1 || right == 1 ? 2 : 0;
    }


class Solution {
public:
    unordered_map<TreeNode*, vector<int>> mm;
    int minCameraCover(TreeNode* root) {
        return helper(root);
    }

    int helper(TreeNode* root, bool is_camera = false, bool is_lit = false){
        if(!root) return 0;
        if(mm.find(root) != mm.end()){
            if(is_camera && (mm[root][0] != -1)) return mm[root][0];
            if(!is_lit && (mm[root][2] != -1)) return mm[root][2];
            if((is_lit ^ is_camera) && (mm[root][1] != -1)) return mm[root][1];
        }
        int ans = 0;
        // if camera dont put camera
        if(is_camera){
            ans = helper(root->left,0,1) + helper(root->right,0,1);
        } else {
                // if no camera, but lit, then put or dont put camera
            if(is_lit) {
                ans = helper(root->left,0,0) + helper(root->right,0,0);
                if(root->left || root->right) {
                    ans = min(ans,1+helper(root->left,0,1) + helper(root->right,0,1));
                }
            } else {
                // put lamp in root
                ans = 1+helper(root->left,0,1) + helper(root->right,0,1);
                // put lamp in children
                if(root->left) { 
                    ans = min(ans,1+helper(root->left,1,1)+helper(root->right,0,0));
                }
                if(root->right) {
                    ans = min(ans,1+helper(root->left,0,0)+helper(root->right,1,1));
                }

            }
        }
       
        if(mm.find(root) == mm.end()) mm[root] = {-1,-1,-1};

        if(is_camera) mm[root][0] = ans;
        else if(is_lit) mm[root][1] = ans;
        else mm[root][2] = ans;

        return ans;
    }
};

