// 11 feb 2025..
// 16 mins .. iterative
// 2 logical mistake
// verdict : FAIL
// severity : sev2

class Solution {
public:
    vector<vector<char>> charMap = {{'a','b','c'},{'d','e','f'},
        {'g','h','i'},{'j','k','l'},
        {'m','n','o'},{'p','q','r','s'},
        {'t','u','v'},{'w','x','y','z'}};

    vector<string> letterCombinations(string digits) {
        string cur = "";
        int n = digits.size();
        vector<string> ans;
        deque<pair<string,int>> q;

        if(n == 0) return ans;

        q.push_back({cur,0});

        while(!q.empty()) {
            auto sz = q.size();
            while(sz--){
                auto curEle =  q.front();
                auto curStr = curEle.first;
                auto curIdx = curEle.second;
                q.pop_front();

                if(curIdx == n) {
                    ans.push_back(curStr);
                    continue;
                }

                auto curMapIdx = digits[curIdx]-'2';
                for(auto& c : charMap[curMapIdx]) {
                    curStr.push_back(c);
                    q.push_front({curStr,curIdx+1});
                    curStr.pop_back();
                }
            }
        }

        return ans;
    }
};


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