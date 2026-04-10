// LC : 631

class Excel {
public:
    unordered_map<string,int> valmap;
    int height, width;
    unordered_map<string,unordered_set<string>> dependenton;
    unordered_map<string,unordered_map<string,int>> influencing;
    Excel(int _height, char _width) {
        height = _height, width = (_width - 'A'+1);
    }
    
    void set(int row, char column, int val) {
        string key = getkey(row, column);
        cleanup(key);
        int diff = val - (valmap.find(key) == valmap.end() ? 0 :  valmap[key]);
        valmap[key] = val;
        updatehelper(key,diff);
    }
    
    int get(int row, char column) {
        string key = getkey(row, column);
        if(valmap.find(key) == valmap.end()) return 0;
        return valmap[key];
    }
    
    int sum(int row, char column, vector<string> numbers) {
        string key = getkey(row,column);
        cleanup(key);
        int orig = get(row,column);
        for(auto it : numbers){
            if(iscell(it)){
                    dependenton[key].insert(it);
                    influencing[it][key]++;
                    valmap[key] += valmap[it];
            } else {
                auto cells = getcells(it);
                for(auto it1 : cells){
                    dependenton[key].insert(it1);
                    influencing[it1][key]++;
                    valmap[key] += valmap[it1];
                }
            }

        }
        updatehelper(key,valmap[key]);
        return valmap[key];
    }

    string getkey(int row, char column){
        string ans(1,column);
        ans += to_string(row);
        return ans;
    }
    void cleanup(string key){
        if(dependenton.find(key) != dependenton.end()) {
            for(auto& v : dependenton[key]){
                influencing[v].erase(key);
            }
            dependenton.erase(key);
        }
        if(valmap.find(key) == valmap.end()) return;
        updatehelper(key,-valmap[key]);
        valmap[key] = 0;
        
    }
    bool iscell(string cell){
        return (cell.find(':') == string::npos);
    }

    vector<string> getcells(string range){
        vector<string> ans;
        auto idx = range.find(':');
        string start = range.substr(0,idx), end = range.substr(idx+1);
        char stCol = start[0], endCol = end[0];
        int strow = stoi(start.substr(1)), endrow = stoi(end.substr(1));
        for(auto r=strow;r<=endrow;r++){
            for(auto c = stCol;c<=endCol;c++){
                ans.push_back(getkey(r,c));
            }
        }
        return ans;
    }

    void updatehelper(string key, int diff){
        for(auto it : influencing[key]){
            string v = it.first;
            int cnt = it.second;
            int newval = valmap[v] + cnt*diff;
            valmap[v] = newval;
            updatehelper(v,cnt*diff);
        }
    }
};

// ]
// key= col,row. hash
// set : map
// get: map lookup 
// sum : g[key]->cell
//  3B :    7F, 2C, 7F, 
//     7F : { {3B:2}  }
//     dfs
//     3B -> {7F,2C}
// 3B : 9A 10B

// O(n) time
// O(n) space