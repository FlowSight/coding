Extract last bit A&-A or A&~(A-1) or x^(x&(x-1))   

Remove last bit A&(A-1)

Get all 1-bits ~0

int count_one(int n) {
    while(n) {
        n = n&(n-1);
        count++;
    }
    return count;
}


int getSum(int a, int b) {
    return b==0? a:getSum(a^b, (a&b)<<1); //be careful about the terminating condition;
}


uint32_t reverseBits(uint32_t n) {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }
//     for 8 bit binary number abcdefgh, the process is as follow:

// abcdefgh -> efghabcd -> ghefcdab -> hgfedcba
