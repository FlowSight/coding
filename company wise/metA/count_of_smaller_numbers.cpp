/// Severity: Sev2
// Date: 28Feb26
// LC: 315
// Where I failed: corner cas + inplace merge
// Pattern: merge sort



// 18 apr 2025 
// devastated
// sev0 sev0 sev0 sev0 sev0

class Solution {
    public:
        vector<int> ans;
        typedef vector<pair<int,int>>::iterator vvi_it;
        vector<int> countSmaller(vector<int>& nums) {
            vector<pair<int,int>> arr;
            int n = nums.size();
            ans = vector<int>(n,0);
            for(auto i=0;i<n;i++) {
                arr.push_back({nums[i],i});
            }
    
            helper(arr,arr.begin(),arr.end());
            return ans;
        }
        void helper(vector<pair<int,int>>& arr, vvi_it l, vvi_it r) {
            if(l+1 >= r) return;
            vvi_it mid = l + (r-l)/2;
            helper(arr,l,mid);
            helper(arr,mid,r);
    
            for(auto i=l,j=mid;(i!=mid);++i) {
                while((j != r) && (i->first >  j->first)) {
                    ++j;
                } 
                ans[i->second] += (j-mid);
                
            }
    
            inplace_merge(l,mid,r);
        }
    };
    
    //2 5 1 6
    
    //0 2 1