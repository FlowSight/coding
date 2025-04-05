class Solution {
public:
    int getSum(int a, int b) {
        int ans = 0;
        bool car = 0 ,abit, bbit;
        for(auto i=0;i<32;i++){
            abit = a&(1<<i);
            bbit = b&(1<<i);
            if(abit ^ bbit ^ car) ans ^= (1<<i);
            car = ((abit ^ bbit)&car) | (abit & bbit);
        }
        return ans;
    }
};