/// Severity: Sev2
// Date: 30Aug26
// LC: 120
// Where I failed: corner case issue
// Pattern: array
// Notes: additional_notes



int minimumTotal(vector<vector<int>>& triangle) {
        int ans = INT_MAX;
        for(auto i=1;i<triangle.size();i++){
            for(auto j=0;j<triangle[i].size();j++){
                triangle[i][j] += min(j < triangle[i-1].size() ? triangle[i-1][j] : INT_MAX , (j ? triangle[i-1][j-1]: INT_MAX));
                if(i==triangle.size()-1){
                    ans = min(ans,triangle[i][j]);
                }
            }
        }
        return ans == INT_MAX ? triangle[0][0] : ans;