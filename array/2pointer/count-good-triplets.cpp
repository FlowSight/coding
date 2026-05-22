/// Severity: Sev0
// Date: 21May26
// LC: 1534
// Where I failed: n^2 algo..
// Pattern: in 3 pointer..the one pointer thats monotonically moving..make the search 
    // space using that + number space..
// Notes: additional_notes



class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size(), ans = 0;
        vector<int> precnt(1001,0);
        for(auto j=0;j<n;j++){
            for(auto k=j+1;k<n;k++){
                if(abs(arr[j]-arr[k]) <= b){
                    int l = max(0,max({arr[j]-a,arr[k]-c})), r = min(1000,min({arr[j]+a,arr[k]+c}));
                    if(l<=r) ans += precnt[r]- (l?precnt[l-1]:0);
                }
            }
            for(auto i=arr[j];i<=1000;i++) precnt[i]++;
        }
        return ans;
    }
};