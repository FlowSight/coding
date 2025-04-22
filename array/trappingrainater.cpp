// 15 apr 2025
// silly mistake..didnt check hotspots..
// took much time to code.
// // didnt even remember 2 pointer approach.
// sev1 sev1

class Solution {
    public:
        int trap(vector<int>& height) {
            int n = height.size(), ans = 0;
            vector<int> rightMax(n,0);
            for(auto i=n-1;i>=0;i--) {
                rightMax[i] = max( (i==n-1 ? 0 : rightMax[i+1]),height[i]);
            }
            for(auto i=1,leftMax = height[0];i<n-1;i++){
                ans += max(0,min(leftMax,rightMax[i+1])-height[i]); 
                leftMax = max(leftMax,height[i]);
            }
            return ans;
        }
    };

// 24 dec 2024...18 mins..forgot original approach..took some time to remember after running in mind..
// then 3-5 index mistake..
// didnt even remember 2 pointer approach.
// verdict : FAIL



// this is genious..
//    2 pointer, smaller ones moves..
//     why?
//     1.  curr = (right-left)*arr[left]..
//         when left moved (right-left-1)*min(arr[right],arr[left+1])..but if right moved (right-left-1)*min(arr[right-1],arr[left])
//         so (right-left-1)*min(arr[right],arr[left+1]) vs (right-left-1)*min(arr[right-1],arr[left])
//         => min(arr[right],arr[left+1]) vs min(arr[right-1],arr[left])
//         => min(arr[right],arr[left+1])  : this value can be larger than arr[left] 
//         => min(arr[right-1],arr[left])  : this can NOT be larger than arr[left]
//         so, we move the smaller one,
//     2. each khamba contributes..= height of min(leftMax,rightMax) - height of khamba
//         if arr[left] < arr[right] .. bottleneck is left khamba..res += max(0,arr[leftMax]-arr[left]) ...vice versa

class Solution {
public:
    int trap(int A[], int n) {
        int left=0; int right=n-1;
        int res=0;
        int maxleft=0, maxright=0;
        while(left<=right){
            if(A[left]<=A[right]){
                if(A[left]>=maxleft) maxleft=A[left];
                else res+=maxleft-A[left];
                left++;
            }
            else{
                if(A[right]>=maxright) maxright= A[right];
                else res+=maxright-A[right];
                right--;
            }
        }
        return res;
    }
};
