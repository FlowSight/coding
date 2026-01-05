class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        stk.push(-1);
        int ans = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                } else {
                    ans = max(ans, i - stk.top());
                }
            }
        }
        return ans;
    }
};

//another cool idea with dp
// dp[i] = longest valid palin ending at i
   int longestValidParentheses(string s) {
            if(s.length() <= 1) return 0;
            int curMax = 0;
            vector<int> longest(s.size(),0);
            for(int i=1; i < s.length(); i++){
                if(s[i] == ')'){
                    if(s[i-1] == '('){
                        longest[i] = (i-2) >= 0 ? (longest[i-2] + 2) : 2;
                        curMax = max(longest[i],curMax);
                    }
                    else{ // if s[i-1] == ')', combine the previous length.
                        if(i-longest[i-1]-1 >= 0 && s[i-longest[i-1]-1] == '('){
                            longest[i] = longest[i-1] + 2 + ((i-longest[i-1]-2 >= 0)?longest[i-longest[i-1]-2]:0);
                            curMax = max(longest[i],curMax);
                        }
                    }
                }
                //else if s[i] == '(', skip it, because longest[i] must be 0
            }
            return curMax;
        }

// another naive approch
// stack based rolling..put the sum on stack and keep compact
    class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> arr;
        int ans = 0, cur = 0;
        for(auto c:s){
            if(c=='(') arr.push_back(-1);
            else {
                cur = compact(arr);
                if(!arr.empty() && (arr.back() == -1)){
                    cur+=2;
                    arr.back() = cur;
                } 
                else arr.push_back(-2);
                ans = max(ans,cur);
            }
        }
        cur = 0;
        while(!arr.empty()) {
            cur = 0;
            if(arr.back() < 0) {
                arr.pop_back();
            }
            else {
                cur = compact(arr);
                ans = max(ans,cur);
            }
        }
        return ans;
    }

    int compact(vector<int>& arr){
        int ans = 0;
        while(!arr.empty() && (arr.back() >0)) {
            ans+= arr.back();
            arr.pop_back();
        }
        return ans;
    }
};