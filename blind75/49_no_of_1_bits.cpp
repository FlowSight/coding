// 14 dec 2024..chalaki marte giye dheriyechi..but mone chilo main trick ta..
// verdcit : FAIL 

class Solution {
public:
    int hammingWeight(int n) {
        int ans = 0;
        while(n){
            ans++;
            n &= (n-1);
        }
        return ans;
    }
};
