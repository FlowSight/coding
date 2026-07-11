/// Severity: Sev0
// Date: 30Jun26
// LC: 440
// Where I failed: tree formation..dist to next idea
// Pattern: tree+math
// Notes: additional_notes



class Solution {
public:
    int findKthNumber(int n, int k) {
        int cur = 1;
        k--;
        while(k){
            int steps = getsteps(n,cur);
            if(steps <=k) {
                k -= steps;
                cur++;
            } else {
                cur*=10;
                k--;
            }
        }
        return cur;
    }
    long getsteps(long n, long num){
        long next = num+1, ans = 0;
        while(num <= n){
            ans += min(n+1,next) - num;
            num *= 10;
            next *= 10;
        }
        return ans;
    }
};

