// 2jan 2024..completely defeated..learnt
// TODO: redo this and all similar problems

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

