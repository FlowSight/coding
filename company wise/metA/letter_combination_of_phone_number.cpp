// 17 jan 2025..
// 8:15 mins 
// clean
// verdict : PASS

class Solution {
public:
    vector<string> ans;
    vector<vector<char>> charmap = {{'a','b','c'},{'d','e','f'},{'g','h','i'},
                                    {'j','k','l'},{'m', 'n','o'},{'p','q','r','s'},{'t','u','v'},
                                    {'w','x','y','z'}};
    vector<string> letterCombinations(string digits) {
        ans = {};
        if(digits.size() == 0) return ans;
        string cur = "";
        helper(digits,0,cur);
        return ans;
    }

    void helper(string digits,int idx, string& cur){
        if(idx == digits.size()){
            ans.push_back(cur);
            return;
        }
        auto digitIdx = digits[idx]-'2';
        for(auto c : charmap[digitIdx]){
            cur.push_back(c);
            helper(digits,idx+1,cur);
            cur.pop_back();
        }
    }
};