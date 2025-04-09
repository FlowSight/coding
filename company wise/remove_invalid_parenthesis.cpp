// 8 apr 2025
// got the idea..but misread the qs and answered something else..
// sev1
// TODO: dietpepsi idea


// dietpepsi idea
public List<String> removeInvalidParentheses(String s) {
    List<String> ans = new ArrayList<>();
    remove(s, ans, 0, 0, new char[]{'(', ')'});
    return ans;
}

public void remove(String s, List<String> ans, int last_i, int last_j,  char[] par) {
    for (int stack = 0, i = last_i; i < s.length(); ++i) {
        if (s.charAt(i) == par[0]) stack++;
        if (s.charAt(i) == par[1]) stack--;
        if (stack >= 0) continue;
        for (int j = last_j; j <= i; ++j)
            if (s.charAt(j) == par[1] && (j == last_j || s.charAt(j - 1) != par[1]))
                remove(s.substring(0, j) + s.substring(j + 1, s.length()), ans, i, j, par);
        return;
    }
    String reversed = new StringBuilder(s).reverse().toString();
    if (par[0] == '(') // finished left to right
        remove(reversed, ans, 0, 0, new char[]{')', '('});
    else // finished right to left
        ans.add(reversed);
}



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