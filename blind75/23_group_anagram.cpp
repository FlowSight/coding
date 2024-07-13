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

