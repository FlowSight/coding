// 14 apr 2025
// very basic idea..but fucked up as i didnt think of negative numbers..
// didnt ask clarifying qs..and didnt dry run with negative numbers..
// sev0

class Solution {
    public:
        int evalRPN(vector<string>& tokens) {
            vector<int> st;
            for(auto it : tokens){
                if(isOp(it)) {
                    auto num2 = st.back();
                    st.pop_back();
                    auto num1 = st.back();
                    st.pop_back();
                    st.push_back(eval(num1,num2,it[0]));
                } else {
                    st.push_back(stoi(it));
                }
            }
            return st.back();
        }
    
        bool isOp(string& s){
            if(s.size() >1 ) return false;
            char c = s[0];
            return (c=='+') || (c=='-') || (c=='*') || (c=='/');
        }
    
        int eval(int num1, int num2, char c){
            if(c=='+') return num1+num2;
            if(c=='-') return num1-num2;
            if(c=='*') return num1*num2;
            return num1/num2;
        }
    };
    