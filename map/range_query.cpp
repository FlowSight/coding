class RangeModule {
public:
    map<int,int> mm;
    RangeModule() {
        mm[INT_MIN] = INT_MIN;
        mm[INT_MAX] = INT_MAX;
    }

    void addRange(int left, int right) {
        auto it = prev(mm.upper_bound(left));
        if(it->second < left)it++;
        auto it1 = it;
        int rStart = left, rEnd = right;
        while((it != mm.end() ) && (it->first<=right)){
            rStart = min(rStart,it->first);
            rEnd = max(rEnd,it->second);
            it++;
        }
        mm.erase(it1,it);
        mm[rStart] = rEnd;
    }
    
    bool queryRange(int left, int right) {
        auto it = prev(mm.upper_bound(left));
        return it->second >= right;
    }
    
    void removeRange(int left, int right) {
        auto it = prev(mm.upper_bound(left));
        if(it->second < left)it++;
        auto it1 = it;
        int leftMin = left, rightMax = right;
        while((it != mm.end() ) && (it->first<=right)){
            leftMin = min(leftMin,it->first);
            rightMax = max(rightMax,it->second);
            it++;
        }
        mm.erase(it1,it);
        if(leftMin != left)mm[leftMin] = left;
        if(right != rightMax) mm[right] = rightMax;
    }
};