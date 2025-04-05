// 18 mar 2025
// 30 mins..
// 2 compiler error
// 1 logical errror corner case : was in a hurry..
// sev1
// need to do the other optimial approach (TODO)

class Solution {
    public:
        string multiply(string num1, string num2) {
            string ans = "0";
            int cnt = 0, n = num2.size(), zero = 1;
            for(auto i=n-1;i>=0;i--,cnt++){
                auto cur = strMult(num1,num2[i]);
                for(auto j=1;j<=cnt;j++){
                    cur.push_back('0');
                }
                ans = sum(ans,cur);
            }
            reverse(ans.begin(),ans.end());
            while(ans.size() && (ans.back() == '0')){
                ans.pop_back();
            }
            reverse(ans.begin(),ans.end());
            return ans.size() ? ans : "0";
        }
    
        string strMult(string& num1, char op){
            int n = num1.size(), op1, op2, car = 0, ans = 0;
            string res = "";
            for(auto i=n-1;i>=0;i--){
                op1 = num1[i]-'0';
                ans = op1*(op-'0') + car;
                res.push_back(ans%10+'0');
                car = ans/10;
            }
            if(car) res.push_back(car+'0');
            reverse(res.begin(),res.end());
    
            return res;
        }
    
        string sum(string& num1, string& num2){
            int m = num1.size(), n = num2.size(), op1, op2, car = 0, res = 0;
            string ans = "";
            reverse(num1.begin(),num1.end());
            reverse(num2.begin(),num2.end());
    
            for(auto i=0;i<max(m,n);i++){
                op1 = (i>=m ? 0 :num1[i]-'0');
                op2 = (i>=n ? 0 :num2[i]-'0');
                res = op1+op2+car;
                ans.push_back(res%10+'0');
                car = res/10;
            }
            if(car)ans.push_back(car+'0');
    
            reverse(ans.begin(),ans.end());
            reverse(num1.begin(),num1.end());
            reverse(num2.begin(),num2.end());
            
            return ans;
        }
    };
    