// 13 apr 2025
// beaten
// sev0 sev0 sev0
// didnt get idea..got the hint from solution..still didnt get it..
// implemented..then got stuck at a stupid mistake..later realized cnt of subarry sum is diff
// because here the arr is already prefix sum.
// didnt quite comprehend the prefix sum and two row (or two col) segmenting part
// initially. Its basicaally a 2D prefix sum. 
// I could also skip the first part where prefix sum is calculated. It can be calculated later
// in cntSubarrSum

class Solution {
    public:
        int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
            int m = matrix.size(), n = matrix[0].size(),ans = 0;
            for(auto i=0;i<m;i++) {
                for(auto j=1;j<n;j++){
                    matrix[i][j] += matrix[i][j-1];
                }
            }
            vector<int> arr;
            for(auto r1=0;r1<m;r1++) {
                arr = vector<int>(n,0);
                for(auto r2 = r1;r2<m;r2++){
                    for(auto c = 0;c<n;c++){
                        arr[c] += matrix[r2][c];
                    }
                    ans += cntSubarrSum(arr, target);
                }
            }
            return ans;
        }
    
        int cntSubarrSum(vector<int>& arr,int& target){
            unordered_map<int,int> mm;
            mm[0] = 1;
            int sum = 0, rem = 0, ans = 0;
            for(auto it : arr){
                rem = it - target;
                if(mm.find(rem) != mm.end()) ans += mm[rem];
                mm[it]++;
            }
            return ans;
        }
    };