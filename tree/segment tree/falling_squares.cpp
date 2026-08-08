/// Severity: Sev0
// Date: 28Jul26
// LC: 699
// Where I failed: implement
// Pattern: segment tree
// Notes: additional_notes




class SegTree {
    public:
    int l, r, maxheight;
    SegTree* left;
    SegTree* right;
    SegTree(int _l, int _r) : l(_l), r (_r), maxheight(0) {
        int mid = (l+r)/2;
        left = nullptr; // i missed considering left and right children
        right = nullptr;
    }
    int findmax(int ll, int rr){

        if((ll > r) || (rr < l)) return 0;
        if((ll <= l) && (rr >= r)) return maxheight;
        if(!left && !right) return maxheight; // i missed this condition
        int mid = (l+r)/2, lh = 0, rh = 0;
        if((ll<=mid) && left) { // i was confused what to calculate if left/right was null
            lh = left->findmax(max(ll,l),min(rr,mid));
        }
        if((rr> mid) && right) {
            rh = right->findmax(max(mid+1,ll) ,min(r,rr));
        }
        return max(lh,rh);
    }
    void update(int ll, int rr, int& hei){
        if((ll > r) || (rr < l)) return;
        if((ll <= l) && (rr >= r)) {
            maxheight = hei;
            left = nullptr;
            right = nullptr;
            return;
        }
        int mid = (l+r)/2;
        if(ll<=mid) {
            if(!left) left = new SegTree(l,mid);
            left->update(max(ll,l),min(rr,mid),hei);
            maxheight = max(maxheight,left->findmax(l,mid)); // i was confused on how to calc max height
        }
        if(rr> mid) {
            if(!right) right = new SegTree(mid+1,r);
            right->update(max(mid+1,ll),min(rr,r),hei);
            maxheight = max(maxheight,right->findmax(mid+1,r));
        }
    }
};

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        SegTree* root = new SegTree(1,1e8);
        int n = positions.size(), curmax = 0;
        vector<int> ans;

        for(auto i = 0 ;i<n;i++){
            auto left = positions[i][0], len = positions[i][1], right = left + len-1; // i missed adding the -1
            int maxheight = root->findmax(left,right), newheight = maxheight + len;
            curmax = max(curmax,newheight);
            ans.push_back(curmax);
            root->update(left,right,newheight);
        }
        return ans;
    }
};

