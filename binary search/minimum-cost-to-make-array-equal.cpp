/// Severity: Sev0
// Date: 15Jun26
// LC: 2448
// Where I failed: algo..
// Pattern: ternery search
// Notes: additional_notes


class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        long long l = 0, r = 0, mid = 0;
        for(auto it : nums) {
            l = min(l,it*1LL);
            r = max(r,it*1LL);
        }

        while(l<r){
            if(l+1 == r) {
                auto curcost = getcost(nums,cost,l),
                nextcost = getcost(nums,cost,r);
                return curcost < nextcost ? curcost : nextcost;
            }
            mid = (l+r)/2;
            auto curcost = getcost(nums,cost,mid),
                nextcost = getcost(nums,cost,mid+1);
            // right half
            if(curcost < nextcost) {
                r = mid;
            } else if(curcost > nextcost) {
                l = mid+1;
            } else l = mid;
        }
        return getcost(nums,cost,l);
    }

    long long getcost(vector<int>& nums, vector<int>& cost,int target){
        int n = nums.size();
        long long ans = 0;
        for(auto i=0;i<n;i++){
            ans += abs(target-nums[i]*1LL) * cost[i] * 1LL;
        }
        return ans;
    }
};


