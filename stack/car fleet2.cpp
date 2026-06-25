/// Severity: Sev0..sev0..sev0 Sev0..sev0..sev0
// Date: 17Jun26
// LC: 1776
// Where I failed: algo
// Pattern: pattern_name
// Notes: additional_notes


// if current car has more or equal speed than next car, it will never catch, until when next car becomes a fleet
// and slows down, so pop the next car from fleet and check for next slower car 

class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size();
        vector<double> ans(n,-1);
        vector<int> st;
        for(auto i=n-1;i>=0;i--){
            auto curp = cars[i][0] , curv = cars[i][1];
            while(!st.empty() && 
                ( (curv <= cars[st.back()][1]) ||
                  (1.0*(cars[st.back()][0] - curp)/(curv - cars[st.back()][1]) >= ans[st.back()]) 
                    && (ans[st.back()] >= 0)))  {
                st.pop_back();
            }
            if(!st.empty()) {
                ans[i] = 1.0 * (cars[st.back()][0] - curp)/(curv - cars[st.back()][1]);
            }
            st.push_back(i);
        }
        return ans;
    }
};