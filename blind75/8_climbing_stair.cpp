class Solution {
public:
    int climbStairs(int n) {
        int i1 = 1, i2 = 2, i3 = 0;
        for(auto i=3;i<=n;i++){
            i3 = i1 + i2;
            i1 = i2;
            i2 = i3;
        }
        return n<=2 ? n : i3;
    }
};