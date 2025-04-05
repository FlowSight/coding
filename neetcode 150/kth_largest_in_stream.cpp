
// 4 feb 2025..
// 5 mins..
// verdict : PASS 

class KthLargest {
public:
    int k;
    multiset<int> ss;
    KthLargest(int _k, vector<int>& nums) {
        ss.clear();
        k = _k;
        for(auto &it : nums){
            if(ss.size() < k) ss.insert(it);
            else if(*(ss.begin()) < it)  {
                ss.erase(ss.begin());
                ss.insert(it);
            }
        }
    }
    
    int add(int val) {
        if(ss.size() < k) ss.insert(val);
        else if(*(ss.begin()) < val)  {
            ss.erase(ss.begin());
            ss.insert(val);
        }
        return *(ss.begin());
    }
};