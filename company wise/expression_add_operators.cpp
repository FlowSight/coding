// 9 apr 2025
// got the idea..but to get hold of the actual impplementation took long time..
// also missed things like : no 0 starting operand, can have operands more than single digit..these i missed.
// also 1-2 corener cases..
// sev0

class Solution {
    public:
        vector<string>  ans;
        vector<string> addOperators(string num, int target) {
            vector<long> res = {};
            string formed = "";
            helper(num,0,res,formed,target);
            return ans;
        }
    
        void helper(string& num, int idx, vector<long>& res, string& formed, int target){
            if(idx == num.size()) {
                long sum = 0;
                for(auto it: res)sum+=it;
                if(sum != target) return;
                ans.push_back(formed);
                return;
            }
            string val = "";
            for(auto i=idx;i<num.size();i++){
                val.push_back(num[i]);
                if((val[0] == '0') && (val.size() > 1)) break;
                res.push_back(stol(val));
                if(idx == 0){
                    formed += val;
                    helper(num,i+1,res,formed,target);
                    for(auto j=1;j<=val.size();j++)formed.pop_back();
                    res.pop_back();
                    continue;
                }
                
                formed.push_back('+');
                formed += val;
                helper(num,i+1,res,formed,target);
                for(auto j=0;j<=val.size();j++)formed.pop_back();
    
                // add -
                formed.push_back('-');
                formed += val;
                res.back() = -stol(val);
                helper(num,i+1,res,formed,target);
                for(auto j=0;j<=val.size();j++)formed.pop_back();
    
                // add *
                res.pop_back();
    
                formed.push_back('*');
                formed += val;
    
                auto last = res.back();
                res.back() = last*stol(val);
                helper(num,i+1,res,formed,target);
                
                for(auto j=0;j<=val.size();j++)formed.pop_back();
                res.back() = last;
            }
        }
    };
    