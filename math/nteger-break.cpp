/// Severity: Sev0
// Date: 29Aug26
// LC: 343
// Where I failed: algo
// Pattern: optimal splitting into 3s
// Notes: additional_notes


class Solution {
public:
    int integerBreak(int n) {
        if(n<=3) return n==3?2:1;
        int prod = 1;
        while(n>4){
            prod*=3;
            n-=3;
        }
        prod*=n;
        return prod;
    }
};