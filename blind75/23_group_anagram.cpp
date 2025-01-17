
// 13 dec 24 ... 5 min
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> mm;
        vector<vector<string>>  ans;
        for(auto &it : strs){
            auto key = makeKey(it);
            mm[key].push_back(it);
        }
        for(auto it : mm){
            ans.push_back(it.second);
        }
        return ans;
    }

    string makeKey(string& str){
        vector<int> freq(26,0);
        string key = "";
        for(auto c : str) {
            freq[c-'a']++;
        }
        for(auto i=0;i<26;i++) {
            key.push_back(('a'+i));
            auto cnt = to_string(freq[i]);
            for(auto c : cnt) {
                key.push_back(c);
            }
        }
        return key;
    }
};


/// @before nov 24
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> mm;
        for(auto it: strs){
            mm[freqMap(it)].push_back(it);
        }
        vector<vector<string>> ans;
        for(auto &it : mm){
            ans.push_back(it.second);
        }
        return ans;
    }
    string freqMap (string& s){
        vector<int> freq(26,0);
        for(auto c:s)freq[c-'a']++;
        string res = "";
        for(auto i=0;i<26;i++){
            res+=to_string(freq[i]);
            res.push_back('$');
        }
        return res;
    }
};

