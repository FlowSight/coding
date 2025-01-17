// 25 dec 2024..14 min basic..10 min optimize..
// need to be faster..did take time back and forth to come up ...
// came up with right ds while coding..ideally should discuss->confirm->code
// verdict : pass

class LRUCache {
public:
    int clock, limit, oldestTS;
    unordered_map<int,pair<int,int>> keyValMap;
    vector<int> tsToKey;
    LRUCache(int capacity) {
        clock = -1;
        oldestTS = 0;
        limit = capacity;
        keyValMap.clear();
        tsToKey = vector<int>();
    }
    
    int get(int key) {
        if(keyValMap.find(key) == keyValMap.end()) return -1;
        auto val = keyValMap[key];
        clock++;
        keyValMap[key] = {clock,val.second};

        //tsToKeyMap.erase(val.first);
        //tsToKeyMap[clock] = key;

        if(tsToKey.size() == clock) tsToKey.push_back(key);
        else tsToKey[clock] = key;
        tsToKey[val.first] = -1;
        while((oldestTS < tsToKey.size())&& (tsToKey[oldestTS] == -1)) oldestTS++;
        return val.second;
    }
    
    void put(int key, int value) {
        clock++;
        if(keyValMap.find(key) != keyValMap.end()) {
            auto val = keyValMap[key];
            keyValMap[key] = {clock,value};
            //tsToKeyMap.erase(val.first);

            tsToKey[val.first] = -1;
            if(tsToKey.size() == clock) tsToKey.push_back(key);
            else tsToKey[clock] = key;
        } else {
            if(keyValMap.size() == limit){
                auto keyToDelete = tsToKey[oldestTS];
                tsToKey[oldestTS] = -1;
                //tsToKeyMap.erase(tsToKeyMap.begin());
                keyValMap.erase(keyToDelete);
            } 

            keyValMap[key] = {clock,value};
            if(tsToKey.size() == clock) tsToKey.push_back(key);
            else  tsToKey[clock] = key;
            
        }
        while((oldestTS < tsToKey.size())&& (tsToKey[oldestTS] == -1)) oldestTS++;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */