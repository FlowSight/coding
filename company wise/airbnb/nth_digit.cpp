// LC : 400
// sev0 : failed to implement

class Solution {
public:
    int findNthDigit(int n) {
        long cnt = 9, len = 1, start = 1;
        // 1. get len of number
        while(n > cnt*len) {
            n -= cnt*len;
            len++;
            cnt *= 10;
            start*=10;
        }
        // 2. get number
        // 3. get idx in number
        int num = start + (n/len) - (n%len == 0), idx = (n-1)%len;
        return to_string(num)[idx] - '0';
    }
};

