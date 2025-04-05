// 1 apr 2025.
// 14 min..
// considered neg numbers while dry running..
// still one complier error...
// sev3

// 5 feb 2025..
// 15 min.
// logical error : didnt consider negative numbers...
// severity : sev1
// verdict : FAIL

#include <cstddef>
#include <string>
#include <stack>

using namespace std;

class Codec
{

    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

public:
    // Encodes a tree to a single string.
    char nullStr = "$", sep = ";";
    void serialize(TreeNode* root, string& res) {
        if(!root) {
            res.push_back(sep);
            res.push_back(nullStr);
            return;
        }
        res.push_back(sep);
        res += to_string(root->val);
        serialize(root->left,res);
        serialize(root->right,res);
    }
    // iterative
    string serialize(TreeNode *root)
    {
        stack<TreeNode *> st;
        string ans = "";
        while (!st.empty() || root)
        {
            if (root)
            {
                auto cur = to_string(root->val);
                for (auto c : cur)
                    ans.push_back(c);
                st.push(root);
                root = root->left;
            }
            else
            {
                ans.push_back(nullStr[0]);
                root = st.top();
                st.pop();
                root = root->right;
            }
            ans.push_back(sep[0]);
        }
        return ans; // 1;2;$$3;4;$$5;$
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        int idx = 0;
        return deserialize(data, idx);
    }
    TreeNode *deserialize(string &s, int &l)
    {
        if (l == s.size())
            return nullptr;
        auto root = fetchNextVal(s, l);
        l++;
        if (!root)
            return root;
        root->left = deserialize(s, l);
        root->right = deserialize(s, l);
        return root;
    }

    // iterative
    TreeNode *deserialize(string &s) {
        if (s.empty())
            return nullptr;

        int l = 0;
        auto root = fetchNextVal(s, l);
        l++;
        if (!root)
            return root;

        stack<pair<TreeNode *, bool>> st;
        st.push({root, false});

        while (l < s.size())
        {
            auto node = fetchNextVal(s, l);
            l++;
            if (!st.top().second)
            {
                st.top().first->left = node;
                st.top().second = true;
                if(node)st.push({node, false});
            }
            else
            {
                st.top().first->right = node;
                st.pop();
                if(node) st.push({node, false});
            }
        }

        return root;
    }
    TreeNode* fetchNextVal(string &s, int &idx)
    {
        string cur = "";
        for (; (idx < s.size()) && (s[idx] != sep[0]); idx++)
        {
            cur.push_back(s[idx]);
        }
        return cur == nullStr ? nullptr : new TreeNode(stoi(cur));
    }
};

// TODO:  i-gotta iterative deserialize too
