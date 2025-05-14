// 13 may 2025..
// fumbled while coding..didnt do groud up..
// remember logn code and map code

class Solution {
    public:
        vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
            int m= mat1.size(), k = mat1[0].size(), n = mat2[0].size();
            vector<vector<vector<int>>> rowNonSparse(m), colNonSparse(n);
    
            // making the non sparse row vector
            for(auto i=0;i<m;i++){
                for(auto j=0;j<k;j++){
                    if(mat1[i][j]) {
                        rowNonSparse[i].push_back({j,mat1[i][j]});
                    }
                }
            }
            // making the non sparse col vector
            for(auto i=0;i<k;i++){
                for(auto j=0;j<n;j++){
                    if(mat2[i][j]) {
                        colNonSparse[j].push_back({i,mat2[i][j]});
                    }
                }
            }
            
            vector<vector<int>> ans(m,vector<int>(n,0));
            
            for(auto i=0;i<m;i++){
                for(auto j=0;j<n;j++){
                    ans[i][j] = mult(rowNonSparse[i],colNonSparse[j],k);
                }
            }
            return ans;
        }
    
    
        // sbroutie to multiply two non sparse arrays of len k
        int mult(vector<vector<int>>& arr1, vector<vector<int>>& arr2, int k){
            int ans = 0, m = arr1.size(), n = arr2.size();
            if(m>n) return mult(arr2,arr1,k);
            for(auto i=0,j=0;i<m;i++){
                // do a binary search
                int idxToSearch = arr1[i][0];
                auto idx = binSearch(arr2,j,n-1,idxToSearch);
                if(idx == -1) continue;
                ans += arr1[i][1] * arr2[idx][1];
                j = idx+1;
            }
            return ans;
        }
    
        /// finds the idx in arr where arr[idx][0] == num by doing binary search
        // always stays within l and r
        int binSearch(vector<vector<int>>& arr, int l, int r, int num){
            int mid = 0;
            while(l<r){
                mid = (l+r)/2;
                if(arr[mid][0] == num) return mid;
                if(arr[mid][0] > num) r = mid-1;
                else l = mid+1;
            }
            return arr[l][0] == num ? l : -1;
        }
    };