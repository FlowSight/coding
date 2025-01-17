// 2jan 2024..completely defeated..learnt
// TODO: redo this and all similar problems

class Solution {
public:
    int calculate(string s) {
       vector<int> nums;
       char sign = '+';
       int cur = 0, res = 0;
       s.push_back('+');
       for(auto c:s){
            if(c == ' ')continue;
            if((c>='0') && (c<='9')){
                cur = cur*10 + (c-'0');
            } else {
                nums.push_back(cur);
                calc(nums,sign);
                sign = c;
                cur = 0;
            }
       }
       for(auto it : nums)res+=it;
       return res;
    }

    void calc(vector<int>& nums, char op) {
        auto num2 = nums.back(), num1 = 0;
        nums.pop_back();
        if(op == '+'){
            nums.push_back(num2);
        } else if(op == '-') {
            nums.push_back(-num2);
        } else if(op == '*') {
            num1 = nums.back();
            nums.pop_back();
            nums.push_back(num1*num2);
        } else {
            num1 = nums.back();
            nums.pop_back();
            nums.push_back(num1/num2);
        }
    }
};