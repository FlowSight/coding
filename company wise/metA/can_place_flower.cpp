// 31 may 2025
// corner case 2 miss
// sev0

// 20 may 2025..
// failed badly...very surprising..
//sev0

class Solution {
public:
    bool canPlaceFlowers(vector<int>& arr, int k) {
        int n = arr.size(), last = -2, ans = 0;
        for(auto i=0;i<n;i++){
            if(arr[i]) {
                int range = (i-last-1);
                ans += max(0,(range-1))/2;
                last = i;
            }
        }
        ans += (n-1-last)/2;
        return ans >= k;
    }
};
