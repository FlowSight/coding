27 dec 2024..
got humiliated..such a simple one..
one delete two delete etc.. are extensions
TODO
verdict : FAIL

class Solution {
public:
    bool validPalindrome(string s) {
       int l = 0, r = s.size()-1;
       while(l<r){
        if(s[l] != s[r]){
            if(isPalin(s,l+1,r) || isPalin(s,l,r-1)) return true;
            return false;
        }
        l++;
        r--;
       }
       return true;
    }

    bool isPalin(string& s, int l, int r){
        while(l<r){
            if(s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }
};
