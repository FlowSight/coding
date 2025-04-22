// 8 apr 2025
// got the idea..but misread the qs and answered something else..
// sev1
// TODO: dietpepsi idea


// dietpepsi idea (TODO)
class Solution {
    public:
        vector<string> removeInvalidParentheses(string s) {
            vector<string> ans;
            vector<char> par = {'(', ')'};
            remove(s, ans, 0, 0, par);
            return ans;
        }
         void remove(string s, vector<string>& ans, int last_i, int last_j,  vector<char> par) {
            for (int stack = 0, i = last_i; i < s.size(); ++i) {
                if (s[i] == par[0]) stack++;
                if (s[i] == par[1]) stack--;
                if (stack >= 0) continue;
                //
                for (int j = last_j; j <= i; ++j) { // we need to loop as deleting diff ( would result diff answers
                    // 
                    if (s[j] == par[1] && (j == last_j || s[j - 1] != par[1])) { // either this is at border or cant delete both (( as they will result in same result
                        remove(s.substr(0, j) + s.substr(j + 1), ans, i, j, par);
                    }
                }
                
                //for (int j = last_j; j <= i; ++j)
    
                return;
            }
            string reversed = s;
            reverse(reversed.begin(),reversed.end());
            if (par[0] == '(') // finished left to right
                remove(reversed, ans, 0, 0, {')','('});
            else // finished right to left
                ans.push_back(reversed);
        }
    };

class Solution {
    public:
        unordered_set<string>  ans;
        vector<string> removeInvalidParentheses(string s) {
            int idx = 0, sum = 0, remove = 
            string cur = "";
            helper(s,idx,sum,cur);
            return vector<string>(ans.begin(),ans.end());
        }
    
        void helper(string& s, int idx, int sum, string& cur){
            if(sum<0) return;
            if(idx == s.size()) {
               if (sum == 0) {
                    if(ans.size() && (ans.begin()->size() < cur.size())) {
                        ans.clear();
                    }
                    if(ans.empty() || (ans.begin()->size() == cur.size())) {
                       ans.insert(cur);
                    }
                }
                return;
            }
            if((s[idx] >='a') && (s[idx] <='z')) {
                cur.push_back(s[idx]); // take any non () char
                helper(s,idx+1,sum,cur);
                cur.pop_back(); 
                return;
            }
            cur.push_back(s[idx]); // take
            helper(s,idx+1,sum+ (s[idx] == '(' ? 1 : -1),cur);
            cur.pop_back();
            helper(s,idx+1,sum,cur); // dont take
        }
    };