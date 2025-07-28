class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int cnt5 = 0, cnt10 = 0;
        for(auto it : bills){
            if(it == 5) cnt5++;
            else if(it == 10) {
                if(cnt5 == 0) return false;
                cnt5--;
                cnt10++;
            } else {
                if(cnt10 && cnt5) {
                    cnt10--;
                    cnt5--;
                } else if(cnt5>=3) {
                    cnt5-=3;
                } else return false;
            }
        }
        return true;
    }
};