class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);
        int ans = 0, n = s.size();
        for(auto i=0;i<n;i++){
            auto tp = st.top();
            if((st.top() != -1) && (s[st.top()] == '(') && (s[i] ==')')){
                st.pop();
                ans = max(ans,i-st.top());
            } else {
                st.push(i);
            }
        }
        return ans;
    }
};