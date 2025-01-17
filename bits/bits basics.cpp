int count_one(int n) {
    while(n) {
        n = n&(n-1);
        count++;
    }
    return count;
}

bool isPowerOfFour(int n) {
    return !(n&(n-1)) && (n&0x55555555);
    //check the 1-bit location;
}

int getSum(int a, int b) {
    return b==0? a:getSum(a^b, (a&b)<<1); //be careful about the terminating condition;
}

int missingNumber(vector<int>& nums) {
    int ret = 0;
    for(int i = 0; i < nums.size(); ++i) {
        ret ^= i;
        ret ^= nums[i];
    }
    return ret^=nums.size();
}

long largest_power(long N) {
    //changing all right side bits to 1.
    N = N | (N>>1);
    N = N | (N>>2);
    N = N | (N>>4);
    N = N | (N>>8);
    N = N | (N>>16);
    return (N+1)>>1;
}


    bool isPowerOfFour(int n) {
        return (n & ((long)n-1)) ==0 && (n%3==1);
    }

       boolean isPowerOfFour(int num) {
        return num > 0 && (num&(num-1)) == 0 && (num & 0x55555555) != 0;
    }

    bool isPowerOfThree(int n) {
        return n > 0 && (1162261467 % n == 0);
    }
     bool isPowerOfThree(int n) {
        int ma = pow(3,(int)(log(INT_MAX)/log(3)));
        return n > 0 && (ma % n == 0);
    }