// 14 apr 2025
// 2 compiler error..
// sev3

class Solution {
    public:
        vector<string> ans;
        vector<string> generateParenthesis(int n) {
            ans = vector<string>();
            int idx = 0,sum = 0;
            string cur = "";
            helper(n,sum,cur);
            return ans;
        }
    
        void helper(int& n, int sum, string& cur){
            if((sum <0) || (sum > n)) return;
            if(cur.size() == 2*n) {
                if (sum) return;
                ans.push_back(cur);
                return;
            }
            cur.push_back('(');
            helper(n,sum+1,cur);
            cur.back() = ')';
            helper(n,sum-1,cur);
            cur.pop_back();
        }
    
    };
