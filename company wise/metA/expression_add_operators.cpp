18 may 2025
// learnt something new + was not able to code past one due to RE 
// pattern
// key : operator then number + calculate when number ends

class Solution {
public:
    vector<char> ops = {'+','-','*'};
    vector<string>  ans;
    vector<string> addOperators(string num, int target) {
        string cur = "";
        int idx = 0, n = num.size();
        long cur_sum = 0, cur_mult = 0;
        char op = '+';
        vector<int> st;
        helper(num,target,cur,idx,n,cur_sum,cur_mult,op);
        return ans;
    }

    void helper(string& num, int& target, string& cur, int idx, int& n, long& cur_sum, long& cur_mult, char& op){
        if((cur_sum > INT_MAX) || (cur_mult > INT_MAX)) return;

        if(idx == num.size()) {
            if(cur_sum == (long)target){
                ans.push_back(cur);
            }
            return;
        }

        int cnt = 0;
        long tmp_sum, tmp_mult;
        string tmp = "";
        for(auto i=idx;i<n;i++) {
            if((num[idx] == '0') && (i-idx)) break;
            cnt++;
            cur.push_back(num[i]);
            tmp.push_back(num[i]);
            long cur_tmp = stol(tmp);
            if(op == '+') {
                tmp_sum = cur_sum + cur_tmp;
                tmp_mult = cur_tmp;
            } else if(op == '-') {
                tmp_sum = cur_sum - cur_tmp;
                tmp_mult = -cur_tmp;
            } else {
                tmp_sum = cur_sum - cur_mult + cur_mult*cur_tmp;
                tmp_mult = cur_mult * cur_tmp;
            }
            if(i == n-1) helper(num,target,cur,i+1,n,tmp_sum,tmp_mult,ops[0]);
            else {
                for(auto op : ops){
                    cur.push_back(op);
                    helper(num,target,cur,i+1,n,tmp_sum, tmp_mult,op);
                    cur.pop_back();
                }
            }
        }
        while(tmp.size()) {
            cur.pop_back();
            tmp.pop_back();
        }
    }
};



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
    