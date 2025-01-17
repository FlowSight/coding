
// 26 dec 2024..45 mins..kind of humiliated..just because i didnt know map lower bound and upper bound..
// but the idea was easy
// verdict : FAIL


class TimeMap {
public:
    unordered_map<string,map<int,string>> mm;
    TimeMap() {
        mm.clear();
    }
    
    void set(string key, string value, int timestamp) {
        mm[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        // auto it = mm[key].upper_bound(timestamp);
        // return it == mm[key].begin() ? "" : prev(it)->second;

        if(mm.find(key) == mm.end()) return "";
        auto& vals = mm[key];
        auto it = vals.lower_bound(timestamp);

        if((it == vals.end()) || (it->first > timestamp)) it--;
        if(it->first <= timestamp) return it->second;
        return "";
    }
};