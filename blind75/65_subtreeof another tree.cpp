// 29 apr 2025
// did serialization..15 mins..
// my main problem is that think while coding..little lack of clarity in preorder vs postorder..
// im thinking preorder..but i say or write postorder
// sev0

// 4 feb 2025
// forgot kmp code
// forgot how to do iterative serializing
// forgot how to do recursive serializing...actually
// forgot rabin karp method
// verdict : FAILED



class Solution {
public:
    char null = '$', sep = ';';
    long mod = 1e11+7;
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        string sRoot = ";", sSubRoot = ";";
        serialize(root,sRoot);
        serialize(subRoot,sSubRoot);
        return isSubstr(sRoot,sSubRoot);
    }

    bool isSubstr(string& s1, string& s2) {
        long targetHash = 0, curHash = 0;
        int m = s1.size(), n = s2.size();
        vector<long> exp(n,1);
        for(auto i=1;i<n;i++){
            exp[i] = (exp[i-1]*256)%mod;
        }
        for(auto i=0;i<n;i++){
            targetHash  = ((targetHash*256)%mod + (int)s2[i])%mod;
        }
        for(auto i=0;i<m;i++){
            if(i>=n) {
                curHash  = ( curHash - (s1[i-n]*exp[n-1])%mod + mod)%mod;
            }
            curHash  = ((curHash*256)%mod + (int)s1[i])%mod;
            if(curHash == targetHash){
                int match = 1, k = 0;
                for(auto j=i-n+1;j<=i;j++){
                    if(s1[j] != s2[k++]){
                        match = 0;
                        break;
                    }
                }
                if(match)return true;
            }
        }
        return false;
    }

    void serialize(TreeNode* root, string& res) {
        if(!root) {
            res.push_back(null);
            res.push_back(sep);
            return;
        }
        res += to_string(root->val);
        res.push_back(sep);
        serialize(root->left,res);
        serialize(root->right,res);
    }

};

// serialize... forgot that we need to make sure each tree is starts with a separator;
//rabin karp...forgot..didnt realize rabin karp wouldnt work for one case...where 12;$;$ and 2;$;$ ...this would also match...
//learnt merkle tree..forgot rabin karp
// rabin karp learning : when window is sliding...remove last one first, then add new one...can be proved by maths

    size_t getMerkleHash(TreeNode* root, int putInMap = 1){
        if(!root || ans)return INT_MAX;
        hash<string> str_hash;
        auto lHash = getMerkleHash(root->left), rHash = getMerkleHash(root->right), rootHash = str_hash(to_string(root->val));
        auto calcHash = str_hash(to_string(lHash)+to_string(rootHash)+to_string(rHash));
        if(putInMap) mm[root->val].insert(calcHash);
        if(target == calcHash)ans = 1;
        return calcHash;
    }