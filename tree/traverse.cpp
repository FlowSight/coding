
// pre
        while(!st.empty() || root){
            if(root){
                st.push(root);
                ans.push_back(root->val);
                root = root->left;
            } else{
                root = st.top();
                st.pop();
                root = root->right;
            }
        }
// in
        while(!st.empty() || root){
            if(root){
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                ans.push_back(root->val);
                st.pop();
                root = root->right;
            }
        }
// post
        while(!st.empty() || root){
            if(root){
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                if(root->right && (root->right != lastPop)){
                    root = root->right; // process right only IF......
                }
                else {
                    ans.push_back(root->val);
                    st.pop();
                    lastPop = root;
                    root = nullptr;
                }
            }
        }

        // I make mistake of returning here..root is changed now..its not the origianl root.
