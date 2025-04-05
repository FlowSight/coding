// 15 mar 2025
// remembered half of the solution..
// not fully..
// sev0

// 7 feb 2025
// could not come up with the solution
// sev0
// verdict : FAIL 

class Solution {
public:
    bool checkValidString(string s) {
        int openMin = 0, openMax = 0;
        for(auto c : s){
            if(c=='('){
                openMin++;
                openMax++;
            }
            else if(c==')'){
                openMin--;
                openMax--;
            } else {
                openMin--;
                openMax++;
            }
            if(openMax<0) return false;
            openMin = max(openMin,0);
        }
        return openMin == 0;
    }
};