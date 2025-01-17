// 18 dec 2024..compile error 2-3 times ..
// verdict : FAIL

class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size(), l = 0, r = n-1;
        while(l<r) {
            if(!isValid(s[l])) l++;
            else if(!isValid(s[r])) r--;
            else {
                if(isEqual(s[l],s[r])) {
                    l++;
                    r--;
                } else return false;
            }
        }
        return true;
    }
    bool isValid(char& c){
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
    }
    bool isEqual(char& c1, char& c2){
        c1 = (c1>='A' && c1<='Z') ? c1-'A'+'a' : c1;
        c2 = (c2>='A' && c2<='Z') ? c2-'A'+'a' : c2;
        return c1==c2;
    }
};

