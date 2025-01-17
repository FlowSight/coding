// 2 jan 2025..
// verdict : FAILED, BEATEN
// TODO

class Solution {
public:
    int calculate(string s) {
        int n = s.size();
        int tot = 0, cur = 0;
        vector<int> ops = {1,1}; // imp line
        for(auto i=0;i<n;i++){
            if(isDigit(s[i])) {
                cur = 0;
                while(i<n && isDigit(s[i])) {
                    cur = cur*10 + (s[i++]-'0');
                }
                tot = tot+ ops.back()*cur;
                ops.pop_back();
                i--;
            } else if (s[i] == '('){
                ops.push_back(ops.back());
            } else if(isOp(s[i])) {
                ops.push_back(ops.back() * (s[i] == '+'? 1 : -1));
            } else if(s[i] == ')'){
                ops.pop_back();
            }
        }
        return tot;
    }

    bool isDigit(char c){
        return (c>='0') && (c<='9');
    }
    bool isOp(char c){
        return (c=='+') || (c=='-');
    }
};
