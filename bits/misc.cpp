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

