// 11 MAR 2025
// tried linkedist approach..
// failed badly..although I came up with the idea correctly..didnt dry run and look at the code deeply
// sev1

class MyListNode{
    public:
    int key,val;
    MyListNode* next;
    MyListNode* prev;
    MyListNode(int _key = -1,int _val = -1){
        key = _key;
        val = _val;
        next = nullptr;
        prev = nullptr;
    }
};

class LRUCache {
public:
    int sz;
    MyListNode* head;
    MyListNode* last;
    unordered_map<int,MyListNode*> mm;
    LRUCache(int capacity) {
        sz = capacity;
        head = new MyListNode();
        last = head;
        mm.clear();
    }
    
    int get(int key) {
        auto it = mm.find(key);
        if(it == mm.end()) return -1;
        calcRecency(it->second);
        return it->second->val;
    }
    
    void put(int key, int value) {
        auto it = mm.find(key);
        if(it != mm.end()) { // present
            it->second->val = value;
            calcRecency(it->second);

        } else {
            // find to evict
            auto node = new MyListNode(key,value);
            auto evict = head->next;
            if(evict && (mm.size() == sz)){
                
                head->next = evict->next;
                if(evict->next) evict->next->prev = head;
                if(last == evict) last = evict->prev;

                mm.erase(evict->key);
            }
            calcRecency(node);

            mm[key] = node;
        }
    }

    void calcRecency(MyListNode* node){
        if(last->key == node->key) return;
        // delete from cur pos
        auto prev = node->prev;
        auto next = node->next;
        if(prev) prev->next = next;
        if(next)next->prev = prev;

        // append to end
        last->next = node;
        node->next = nullptr;
        node->prev = last;
        last = last->next;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// dumm->1->2


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