// 14 apr 2025
// 12 min..clean

class Solution {
    public:
        vector<int> dailyTemperatures(vector<int>& temperatures) {
            int n = temperatures.size();
            vector<int> st;
            vector<int> ans = vector<int>(n,0);
            for(auto i=0;i<n;i++){
                while(!st.empty() && (temperatures[st.back()] < temperatures[i])) {
                    ans[st.back()] = i-st.back();
                    st.pop_back();
                }
                st.push_back(i);
            }
            return ans;
        }
    };
