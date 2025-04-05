// 11 mar 2025..
// 20 mins..
// 1 stupid mistake..which i did anyway thinking my algo was incorrect..my algo was correct
// sev1

class Solution {
    public:
        int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
            int n = gas.size(), sum = 0, diff = 0, l = -1, r = -1, ansL = -1, ansR = -1, ans = -1, tot = 0;
            for(auto i=0;i<2*n;i++){
                diff = gas[i%n]-cost[i%n];
                sum += diff;
                tot+= diff;
                if(sum <0){
                    sum = 0;
                    l = r = -1;
                } else {
                    r = i%n;
                    if(l == -1)l = i%n;
                }
                if(sum > ans){
                    ansL = l;
                    ansR = r;
                    ans = sum;
                }
            }
            return tot>=0 ? ansL : -1;;
        }
    };
