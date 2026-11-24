/// Severity: Sev0..sev0..Sev0..sev0..Sev0..sev0..Sev0..sev0.Sev0..sev0..Sev0..sev0..Sev0..sev0..Sev0..sev0
// Date: 21Nov26
// LC: 715
// Where I failed: half open handling in seg tree
/*
Range issue: the API uses half-open intervals [left,right), while my tree
uses inclusive leaf-index ranges [l,r]. Leaf i represents [i,i+1), so
[left,right) maps to [left,right-1].

Cover state: I originally used one false state for both completely
uncovered and partially covered nodes. Three states are required:
0 = uncovered, 1 = mixed/partial, 2 = fully covered.

Pull-up: after a partial add/remove, recompute the parent from its children.
 Equal uniform children collapse into that state; otherwise parent is mixed.

Push-down: a standalone new node starts uncovered, but when splitting an
existing uniform parent for a partial update, both children must inherit
the parent's current covered/uncovered state.

Full overwrite: when an update fully covers a node, its old child state is
stale and must be discarded or overwritten before a future partial update.

*/
// Pattern: segtree, map
// Notes: additional_notes

class SegTree {
    public:
    SegTree* left = nullptr;
    SegTree* right = nullptr;
    int l, r, cover; // 0 : untracked, 1 : partially tracked, 2 : fully tracked
    SegTree(int _l, int _r) {
        cover = 0;
        l = _l;
        r = _r;
    }
    void addRange(int ll, int rr){
        if((ll>r) || (rr<l) || (cover == 2)) return;
        if((ll<=l) && (rr>=r)) {
            cover = 2;
            left = nullptr;
            right = nullptr;
            return;
        }
        int mid = l+(r-l)/2;
        if(ll<l) ll = l;
        if(rr>r) rr = r;
        if(ll<=mid){
            if(!left) left = new SegTree(l,mid);
            left->addRange(ll,rr);
        }
        if(rr>mid){
            if(!right) right = new SegTree(mid+1,r);
            right->addRange(ll,rr);
        }
        cover = 1;
        if(left && right && (left->cover == right->cover) && (left->cover == 2)){
            cover = 2;
            left = nullptr;
            right = nullptr;
        }
    }

    void removeRange(int ll, int rr) {
        if((ll>r) || (rr<l) || (cover == 0)) return;
        if((ll<=l) && (rr>=r)) {
            cover = 0;
            left = nullptr;
            right = nullptr;
            return;
        }
        int mid = l+(r-l)/2;
        if(ll<l) ll = l;
        if(rr>r) rr = r;

        if(!left) {
            left = new SegTree(l,mid);
            left->cover = cover;
        }
        if(!right) {
            right = new SegTree(mid+1,r);
            right->cover = cover;
        }

        if(ll<=mid){
            left->removeRange(ll,rr);
        }

        if(rr>mid){
            right->removeRange(ll,rr);
        }
        cover = 1;
        if(left && right && (left->cover == right->cover) && (right->cover == 0 )) {
            left = nullptr;
            right = nullptr;
            cover = 0;
        }
    }
    bool queryRange(int ll, int rr){
        if((ll>r) || (rr<l)) return true;
        if(cover == 0) return false;
        if((ll<=l) && (rr>=r)) {
            return (cover == 2);
        }
        int mid = l+(r-l)/2;
        if(ll<l) ll = l;
        if(rr>r) rr = r;
        if(ll<=mid){
            if(cover != 2) {
               if(!left || !left->queryRange(ll,rr)) return false;
            }
        }
        if(rr>mid){
            if(cover != 2) {
               if(!right || !right->queryRange(ll,rr)) return false;
            }
        }
        return true;
    }
};

class RangeModule {
public: 
    SegTree* root;
    RangeModule() {
        root = new SegTree(1,1e9);
    }
    
    void addRange(int left, int right) {
        root->addRange(left,right-1);
    }
    
    bool queryRange(int left, int right) {
        return root->queryRange(left,right-1);
    }
    
    void removeRange(int left, int right) {
        return root->removeRange(left,right-1);
    }
};



/// soluton 2
/// Severity: Sev1
// Date: 22Nov26
// LC: 715
// Where I failed:
// 1. With inclusive unit-segment ranges, touching intervals are continuous:
//    [10,15] and [16,22] must merge.
// 2. Merge boundaries must grow during the forward scan. Given [10,15],
//    [18,25], and add(16,22), first merge to [10,22], then continue and merge
//    [18,25], producing [10,25].
// 3. For ordered-map insertion, inspect the predecessor before scanning forward.
// Pattern: dynamic interval set with ordered map + chain merging


class RangeModule {
public:
    map<int,int> mm;
    RangeModule() {
        mm[0]=0;
        //mm[1e9] = 1e9;
    }
    
    void addRange(int left, int right) {
        right--;
        int ll = left, rr= right;
        vector<int> todel;
        auto it = mm.lower_bound(left);
        if(prev(it)->second  >= left-1) it--; // +-1 case (1)
        while((it != mm.end()) && (it->first <= rr+1)) { // +-1 case (2)
            todel.push_back(it->first);
            ll = min(ll,it->first);
            rr = max(rr,it->second);
            it++;
        }
        for(auto it : todel)mm.erase(it);
        mm[ll] = rr;
    }
    
    bool queryRange(int left, int right) {
        right--;
        int ll = left, rr= right;
        auto it = mm.lower_bound(left);
        if(prev(it)->second  >= left) it--;
        return (it->first <= left) && (it->second >= right);
    }
    
    void removeRange(int left, int right) {
        right--;
        int ll = left, rr= right;
        vector<int> todel;
        auto it = mm.lower_bound(left);
        if(prev(it)->second  >= left) it--;
        while((it != mm.end()) && (it->first <= rr)) {
            todel.push_back(it->first);
            ll = min(ll,it->first);
            rr = max(rr,it->second);
            it++;
        }
        for(auto it : todel)mm.erase(it);
        if(ll <= left-1) mm[ll] = left-1;
        if(right + 1 <= rr) mm[right+1] = rr;
    }
};
