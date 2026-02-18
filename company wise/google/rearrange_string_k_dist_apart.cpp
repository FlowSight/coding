// 2/2/26..it was easy..but messed up 3-4 corner cases ..
// sev0..sev0

class Solution {
public:
    string rearrangeString(string s, int k) {
        if(!k) return s;
        vector<int> freq(26,0);
        set<pair<int,int>,greater<>> ss, ss1;
        int idx = 0;
        string ans = "";
        for(auto &c:s)freq[c-'a']++;
        for(auto i=0;i<26;i++) {
            if(freq[i] == 0) continue;
            ss.insert({freq[i],i});
        }
        while(!ss.empty()){
            ss1.clear();
            idx = 1;
            for(;(idx<=k) && (!ss.empty());idx++){
                auto tp = *(ss.begin());
                ss.erase(ss.begin());
                if(tp.first >1) ss1.insert({tp.first-1,tp.second});
                ans.push_back('a'+tp.second);
            }
            if(idx<=k && !ss1.empty()) return "";
            for(auto it:ss1)ss.insert(it);
        }
        return ans;
    }
};
