// 27 may 2025..
// sev1..missed a corner case..
// 19 min..

// 8 apr 2025
// 33 mins
// the idea hit quickly that its gonna be a recursive structured solution..
// but i didnt do in one pass..made moduled..i know this is one point where they can put pressure.
// still there were 4-5 corner cases I missed..as i didnt dry run..i felt impatient
// sev0
// BTW I HATE THIS QS


class Solution {
    public:
        bool isNumber(string s) {
            int n = s.size();
            for(auto i=0;i<n;i++){
                if((s[i] == 'e') || (s[i] == 'E')){
                    if(isInteger(s,0,i-1) && isInteger(s,i+1,n-1)) return true;
                    if(isDecimal(s,0,i-1) && isInteger(s,i+1,n-1)) return true;
                }
            }
            return isInteger(s,0,n-1) || isDecimal(s,0,n-1);
        }
        bool isInteger(string& s,int i, int j) {
            if(!isDigit(s[i]) && !isSign(s[i])) return false;
            int digCount = isDigit(s[i]);
            for(auto idx = i+1;idx<=j;idx++) {
                if(!isDigit(s[idx])) return false;
                digCount++;
            }
            return digCount;
        }
    
        bool isDecimal(string& s,int i, int j) {
            if(!isDigit(s[i]) && !isSign(s[i]) && (s[i] != '.')) return false;
            int idx = isSign(s[i]) ? i+1 : i, leftDig = 0, rightDig = 0;
            for(;idx<=j;idx++) {
                if(s[idx] == '.')break;
                if(!isDigit(s[idx])) return false;
                leftDig++;
            }
            if((idx==j+1)) return false; // no dot
            for(auto k = idx+1;k<=j;k++){
                if(!isDigit(s[k])) return false;
                rightDig++;
            }
            return leftDig || rightDig;
        }
    
    
        bool isDigit(char c){
            return (c>='0') && (c<='9');
        }
    
        bool isSign(char c){
            return (c=='+') || (c == '-');
        }
    
    };
    
    // a-z A-Z 0-9 +/0 .