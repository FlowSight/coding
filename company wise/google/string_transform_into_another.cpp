/// Severity: Sev0
// Date: 17Feb26
// 
// How much solved: Fully
// Where I failed: algo..tmp case could not think of
// Pattern: greedy



class Solution {
public:
    bool canConvert(string str1, string str2) {
        int n = str1.size();
        if(str1 == str2) return true;
        unordered_set<char> ss1;
        unordered_map<char,char> mm;
        for(auto i=0;i<n;i++){
            ss1.insert(str2[i]);
            if((mm.find(str1[i]) != mm.end()) && (mm[str1[i]] != str2[i])) return false;
            mm[str1[i]] = str2[i];
        }
        return ss1.size()<26;
    }
};