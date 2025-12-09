//sev0...14/11/25
//sev0...8/12/25
// coudl not come up...sev0..sev0..sev0..

class CountIntervals {
public:
    map<int,int> mm;
    int ans;
    CountIntervals() {
        ans = 0;
        mm.clear();
    }
    
    void add(int left, int right) {
        if(mm.size() == 0) {
            mm[left] = right;
            ans += right-left+1;
            return;
        }
        auto it = mm.upper_bound(left);
        if((it != mm.begin()) && (prev(it)->second >= left)) {
            it--;
        }
        while((it != mm.end()) && (it->first <= right)) {
            left = min(left,it->first);
            right = max(right,it->second);
            ans -= (it->second - it->first +1);
            it++;
            mm.erase(prev(it));
        }
        mm[left] = right;
        ans += right-left+1;
    }
    
    int count() {
        return ans;
    }
};

