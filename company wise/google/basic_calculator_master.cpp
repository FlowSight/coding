// 24/12/25...sev0

// works for 
// 1. ()
// 2. * and /
// 3. (-20) case
// 4. custom operator


class Solution {
public:
    int calculate(string s) {
        int ans = 0, n = s.size();
        long cur = 0;
        vector<long> vals;
        vector<char> ops;
        char last = '(';
        unordered_map<char,int> priority;
        priority['+'] = priority['-'] = 1;
        priority['/'] = priority['*'] = 2;
        for(auto i=0;i<n;i++){
            if(isDigit(s[i])){
                while((i<n) && isDigit(s[i])) {
                    cur = cur*10 + (s[i++]-'0');
                }
                i--;
                vals.push_back(cur);
                cur = 0;
            } else if(isOp(s[i])) {
                if(last == '(') vals.push_back(0);
                while(!ops.empty() && (priority[ops.back()] >= priority[s[i]])) calc(ops,vals);
                ops.push_back(s[i]);
            } else if(s[i] == '(') {
                ops.push_back(s[i]);
            } else if(s[i] == ')') {
                while(!ops.empty() && (ops.back() != '(')) {
                    calc(ops,vals);
                }
                ops.pop_back();
            } else continue;
            last = s[i];
        }
        while(!ops.empty()) {
            calc(ops,vals);
        }
        return vals.back();
    }

    bool isDigit(char c){
        return (c>='0') && (c<='9');
    }
    bool isOp(char c){
        return (c=='+') || (c=='-') || (c=='*') || (c=='/');
    }
    void calc(vector<char>& ops, vector<long>& vals){
        auto op = ops.back();
        ops.pop_back();
        long val1 = vals.back();
        vals.pop_back();
        long val2 = vals.back();
        vals.pop_back();
        if(op == '+') vals.push_back(val1+val2);
        else if(op == '-') vals.push_back(val2-val1);
        else if(op == '*') vals.push_back(val1*val2);
        else vals.push_back(val2/val1);
    }
};

// vals= {6 4 2}
// ops = {- /}
// last = /