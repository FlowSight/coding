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


// with stack .. iterative
class Solution {
public:
    unordered_map<char,int> mm;
    int calculate(string s) {
        mm['+'] = mm['-'] = 1;
        mm['*'] = mm['/'] = 2;
        mm['('] = mm[')'] = 0;
        int n = s.size(), ans = 0, val = 0, sign = 1;
        stack<int> st;
        stack<char> ops;
        for(auto i=0;i<n;i++){
            if(s[i] == ' ')continue;
            if(isDigit(s[i])){
                while((i<n) && (isDigit(s[i]))) {
                    val = val*10 + (s[i++]-'0');
                }
                i--;
                st.push(val);
                val = 0;
            }
            else {
                if(s[i] == '(') ops.push(s[i]);
                else if(isOp(s[i])) {
                    while(!ops.empty() && (mm[ops.top()] >= mm[s[i]])) calc(st,ops);
                    ops.push(s[i]);
                }
                else if(s[i] == ')') {
                    while(!ops.empty() && (ops.top() != '(')) calc(st,ops);
                    ops.pop();
                }
            }
        }
        while(!ops.empty()) calc(st,ops);
        return st.top();
    }
    void calc(stack<int>& st, stack<char>& ops){
        auto op = ops.top();
        ops.pop();
        auto num1 = st.top();
        st.pop();
        auto num2 = st.top();
        st.pop();
        int ans = 0;
        if(op == '+'){
            ans = num1 + num2;
        } else if(op == '-'){
            ans = num2 - num1;
        } else if(op == '*'){
            ans = num1 * num2;
        } else {
            ans = num2 / num1;
        }
        st.push(ans); 
    }

    bool isOp(char c){
        return (c=='+') || (c=='-') || (c=='/') || (c=='*');
    }

    bool isDigit(char c){
        return (c>='0') && (c<='9');
    }
};