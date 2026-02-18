// 3feb2026..
// was easy..still 1 logical and 1 implementation bug..
// did above with O(n) space and O(n^2) time..
// need to do with O(n) time.
//sev0..sev0..

class Solution {
public:
    unordered_map<int,int> mm;
    bool parseBoolExpr(string exp) {
        int n = exp.size(), idx = 0;
        stack<int> st;
        for(auto i=0;i<n;i++){
            if(exp[i] == '(')st.push(i);
            else if(exp[i] == ')'){
                mm[st.top()] = i;
                st.pop();
            }
        }
        return helper(exp,0,n-1)[0];
    }

    vector<bool> helper(string& exp, int l, int r){
        char op = '#';
        vector<bool> arr;
        for(;l<=r;l++){
            if(exp[l] == ',')continue;
            if(isOp(exp[l])) {
                op = exp[l];
                auto tmp = helper(exp,l+2,mm[l+1]-1);
                arr.push_back(calculatorCore(tmp,op));
                l = mm[l+1];
            }
            else arr.push_back(exp[l]=='t');
            op = '#';
        }
        return arr;
    }

    bool calculatorCore(vector<bool> &arr, char op){
        bool ans = (op == '&' ? true : false);
        if(op == '!') return !arr[0];
        for(auto it : arr) {
            if((op == '&') && !it) return false;
            if((op == '|') && it) return true;
        }
        return ans;
    }
    bool isOp(char& c){
        return (c== '&') || (c== '|') || (c== '!');
    }
};

