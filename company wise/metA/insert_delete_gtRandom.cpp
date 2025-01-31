// 26 jan 2025..
// 14 min..
// 1 compiler errror..
// 1 logical error : caught after running
// 1 logical error : major, didnt catch, only got after long time using chatgpt...
// verdict : FAIL

class RandomizedSet {
public:
    vector<int> arr;
    int idx, sz;
    unordered_map<int,int> mm; // number to index map
    RandomizedSet() {
        arr = vector<int>();
        idx = 0;
        sz = 0;
        mm.clear();
    }
    
    bool insert(int val) {
        if(mm.find(val) != mm.end()) return false;
        arr.push_back(val);
        mm[val] = sz++;
        return true;
    }
    
    bool remove(int val) {
        if(mm.find(val) == mm.end()) return false;
        idx = mm[val];
        int toSwap = arr.back();

        mm.erase(val);
        arr[idx] = toSwap;
        arr.pop_back();
        sz--;

        if(arr.size()>0) {
            mm[toSwap] = idx;
        }
        return true;
    }
    
    int getRandom() {
        idx = rand()%(sz);
        return arr[idx];
    }
};
