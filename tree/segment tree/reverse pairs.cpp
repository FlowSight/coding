/// Severity: Sev0
// Date: 08Jun26
// LC: 493
// Where I failed: segtree approach..how to coordinate compress..
// Pattern: pattern_name
// Notes: additional_notes



class SegTree{
    public:
    long long  cnt, left, right, mid = 0;
    SegTree* leftch;
    SegTree* rightch;
    SegTree(int l, int r){
        if(l>r) return;
        left = l, right = r,cnt = 0;
        leftch = nullptr;
        rightch = nullptr;
        mid = (left+right)/2;
    }
    void add(int idx){
        if((idx<left) || (idx> right)) return;
        cnt++;
        if(left == right) return;
        if(idx <= mid) {
            if(!leftch) leftch = new SegTree(left,mid);
            leftch->add(idx);
        }
        else {
            if(!rightch) rightch = new SegTree(mid+1,right);
            rightch->add(idx);
        }
    }
    int find(long long l, long long r){
        if((r<left) || (l> right)) return 0;
        if((l<=left) && (r>= right)) return cnt;
        if(left == right) return cnt;
        int ans = 0;
        if(l<=mid) {
            ans +=  leftch ? leftch->find(l,min(r,mid)) : 0;
        }
        if(r>mid) {
            ans += rightch ? rightch->find(max(l,mid+1),r) : 0;
        }
        return ans;
    } 

};

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<long long> arr;
        for(auto i=0;i<n;i++){
            arr.push_back(2LL*nums[i]+1); 
            arr.push_back(nums[i]);
        }
        sort(arr.begin(),arr.end());
        auto last = unique(arr.begin(),arr.end());
        arr.erase(last,arr.end());

        int m = arr.size();
        SegTree* root = new SegTree(0, m-1);
        for(auto i=0;i<n;i++){
            int idx = getidx(arr,nums[i]*2LL+1);
            ans += root->find(idx,m-1);
            idx = getidx(arr,nums[i]); 
            root->add(idx);
        }
        return ans;
    }
    int getidx(vector<long long>& arr, long long num){
        int l = 0, r = arr.size()-1 , mid = 0;
        while(l<r){
            if(l+1 == r) return arr[l]>=num?l:r;
            mid = (l+r)/2;
            if(arr[mid] >=num) r = mid;
            else l = mid+1;
        }
        return l;
    }
};