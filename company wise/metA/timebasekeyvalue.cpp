//28 jan 2025..
// 14 mins..
// dry ran..logic fine..used array instead of map..i forgot lower bound upper bound
// 1 compiler error..
// verdict : FAIL

class TimeMap {
public:
    unordered_map<string,vector<pair<int,string>>> dict;
    TimeMap() {
        dict.clear();
    }
    
    void set(string key, string value, int timestamp) {
        dict[key].push_back({timestamp,value});
    }
    
    string get(string key, int timestamp) {
        if(dict.find(key) == dict.end()) return "";
        auto& vals = dict[key];
        int l = 0, r = vals.size()-1, mid = 0;
        while(l<r){
            if(l+1 == r){
                if(vals[r].first <= timestamp) return vals[r].second;
                return vals[l].first>timestamp ? "" : vals[l].second;
            }
            mid = (l+r)/2;
            if(vals[mid].first == timestamp) return vals[mid].second;
            if(vals[mid].first > timestamp) r = mid-1;
            else l = mid;
        }
        return vals[l].first>timestamp ? "" : vals[l].second;
    }
};



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