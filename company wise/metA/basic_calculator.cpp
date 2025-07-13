// 18 may 2025..
// stream approach : cur_eval and cur_mult

class Solution {
public:
    bool isOp(char c){
        return (c=='+') || (c=='-') ||  (c=='*') || (c=='/');
    }
    bool isDigit(char c){
        return (c>='0') && (c<='9');
    }
    int calculate(string s) {
        int n = s.size(), idx = 0;
        long cur_eval = 0, cur_mult = 0;
        return helper(s,idx,n);
    }
    int helper(string& s, int& idx, int n){
        long  val = 0, cur_eval = 0, cur_mult = 0;
        char op = '+';
        for(;idx<n;idx++){
            if(s[idx] == ' ') continue;
            if(isOp(s[idx])) {
                op = s[idx];
                continue;
            }
            if(s[idx] == '(') {
                idx++;
                val = helper(s,idx,n);
                calc(cur_eval, cur_mult,val,op);
                continue;
            } else if(s[idx] == ')') {
                return cur_eval;
            }
            while((idx<n) && isDigit(s[idx])){
                val = val*10 + (s[idx]-'0');
                idx++;
            }
            calc(cur_eval, cur_mult,val,op);
            idx--;
        }
        return cur_eval;
    }

    void calc(long& cur_eval, long& cur_mult, long& val, char& op) {
        if(op == '+'){
            cur_eval += val;
            cur_mult = val;
        } else if(op == '-'){
            cur_eval += -val;
            cur_mult = -val;
        } else if(op == '*'){
            cur_eval = cur_eval - cur_mult + cur_mult*val;
            cur_mult *= val;
        } else {
            cur_eval = cur_eval - cur_mult + cur_mult/val;
            cur_mult /= val;
        }
        val = 0;
    }
};


// given a expression in string, evaluate it.
// Input: s = "1 + 1"
// Output: 2
// Example 2:

// Input: s = " 2-1 + 2 "
// Output: 3


// given a expression in string, evaluate it.
// Input: s = "1 + 1"
// Output: 2
// Example 2:

// Input: s = " 2-1 + 2 "
// Output: 3

// when u do this qs understand the series..
// basic version is only +/
// then adding ()
// then  +-*/ no ()
// then +-*/ with ()
// then + - * / with ()


// 9 apr 2025
// i got it done by a innovative method..still missed a corner case..as didnt dry run
// also forogt the actual approach
// sev2

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
