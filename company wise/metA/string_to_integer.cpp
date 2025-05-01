// 27 apr 2025
// 28 mins..TOO MUCH TIME
// clean..
// SEV3 

class Solution {
    public:
        int myAtoi(string s) {
            int n = s.size(), val = 0, sign = 1, limit = INT_MAX,idx = 0;
            while((idx<n) && (s[idx] == ' '))idx++; // skip all initial ' '
            if((idx>=n) || isEngChar(s[idx])) return 0;
    
            // if next char is sign then set sign
            if((s[idx] == '+') || (s[idx] == '-')) sign = (s[idx++] == '+') ? 1 : -1;
            if(sign == -1) limit = INT_MIN;
            while ((idx<n) && isDigit(s[idx])) {
                if((val < INT_MIN/10) || (val > INT_MAX/10)){
                    val = limit;
                    break;
                }
                val = val*10;
                int dig = s[idx]-'0';
                if(val && ((val > 0) && (INT_MAX-val < dig)) || ((val < 0) && (val - INT_MIN < dig))) {
                    val = limit;
                    break;
                }
                val = val + sign*dig;
                idx++;
            }
            return val;
    
        }
    
        bool isEngChar(char c){
            return ((c>='a') && (c<='z')) || ((c>='A') && (c<='Z'));
        }
        bool isDigit(char c){
            return ((c>='0') && (c<='9'));
        }
    };