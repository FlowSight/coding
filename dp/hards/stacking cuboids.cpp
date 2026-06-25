/// Severity: Sev0
// Date: 17Jun26
// LC: 1691
// Where I failed: lis vs not sorting
// Pattern: dp
// Notes: additional_notes


// i thought if i sort( each it + whole) and do lis, it might work, but for case like (1,10,100) (2,3,101) it will not
// as sorting does not guarentee total order
/*
also we need sort for whole arr, because then we know ith elem cant come in lis after  i+1
*/


class Solution {
public:
    int maxHeight(vector<vector<int>>& arr) {
        for(auto& it: arr){
            sort(it.begin(),it.end());
        }
        //sort(arr.begin(),arr.end());
        int n = arr.size(), ans = 0;
        vector<int> dp(n,0);

        for(auto i=0;i<n;i++){
            dp[i] = arr[i][2];
            for(auto j=i-1;j>=0;j--){
                if((arr[i][0] >= arr[j][0]) && (arr[i][1] >= arr[j][1]) && (arr[i][2] >= arr[j][2]) ){
                    dp[i] = max(dp[i],dp[j] + arr[i][2]);
                }
            }
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};

adding custoomer to contract line :
    add customer to staging contract line customer
    if customer is already in staging contract customer : dont add 
    else :
        add to staging contract customer
        mark staging contract as changed if not already
Removing  customer from contract line :
    remove customer from staging contract line customer
    ** staging contract customer stays untouched **

Undo at staging Contract line changes :
    Delete contract line -> cascade delete all children entities
    Create minimal staging contract line with link to CO + state == unchanged
    Dont affect staging Contract (even if there was a staging contract customer added from delete contract line)

Undo at staging Contract changes :
    if staging contract customer exists which was is part of staging contract line customer : block it 