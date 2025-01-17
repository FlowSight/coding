
//14 jan 2025..2 mins..1 compiling mistake.
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0 , r = height.size()-1, ans = 0;
        while(l<r){
            ans = max(ans,(r-l)*min(height[l],height[r]));
            if(height[l]<height[r])l++;
            else r--;
        }
        return ans;
    }
};


//5 nov 2024..2 mins..one compiling mistake.

class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size()-1, ans = 0;
        while(l<r){
            ans = max(ans,(r-l)*min(height[l],height[r]));
            if(height[l] < height[r])l++;
            else r--;
        }
        return ans;
    }
};