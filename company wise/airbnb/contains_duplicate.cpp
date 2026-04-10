// LC : 220
// severity : sev0 
// notes : corner cases
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexdiff, int valuediff) {
        map<int,int> mm;
        int l = 0, r= 0, n = nums.size();
        while((r<n) && (r-l<=indexdiff)) {
            mm[nums[r++]]++;
        }
        //r--;
        while(l<n){

            int num = nums[l], higher = nums[l] + valuediff, lower = nums[l]-valuediff;
            auto it1 = mm.lower_bound(higher);
            if((it1 == mm.end()) || (it1->first > higher)) it1--;
            if(higher == num) {
                if((it1->first == num) && (it1->second > 1)) return true;
            } else {
                if((it1->first != num) || (it1->second>1)) return true;
            }
            
            auto it2 = mm.lower_bound(lower);
            if(lower == num) {
                if(it2->second > 1) return true;
            } else {
                 if((it2->first != num)) return true;
            }
            
            mm[nums[l]]--;
            if(mm[nums[l]] == 0) mm.erase(nums[l]);
            l++;
            if(r<n){
                mm[nums[r++]]++;
            }
            
        }
        return false;

    }
};

// l....r (r-l<=indexdiff)
// put vals in set
// nums[l]+valuediff lower_bound
// nums[l]-valuediff upper bound