// 9feb2026..sev0..
// could not imeplement in one go..many bugs..


class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& words) {
        int n = words.size(), final = 1;
        unordered_map<string,vector<int>> mm;
        for(auto i=0;i<n;i++){
            auto abbr = words[i].size() <=3 ? words[i] 
                : string(1,words[i][0]) + to_string(words[i].size()-2) + string(1,words[i].back());
            mm[abbr].push_back(i);
            if(mm[abbr].size()>1) final = 0;
        }
        vector<string> ans(n,"");
        while(mm.size()) {
            auto it = *(mm.begin());
            int sz = it.second.size();
            auto abbr = it.first;
            mm.erase(abbr);
            if(sz == 1) {
                int idx = it.second.back();
                ans[idx] = abbr;
                continue;
            }
            while(it.second.size()){
                auto idx = it.second.back();
                it.second.pop_back();
                auto word = words[idx];
                string newAbbr = abbr, lenTaken = "";
                int len = newAbbr.size(), prefLen = 0;
                for(auto i=len-2;i;i--){
                    if(isDigit(newAbbr[i])) lenTaken.push_back(newAbbr[i]);
                    else break;
                }
                reverse(lenTaken.begin(),lenTaken.end());
                len = stoi(lenTaken)-1;
                prefLen = words[idx].size()-1-len;
                newAbbr = words[idx].substr(0,prefLen) + to_string(len)+string(1,words[idx].back());
                if(newAbbr.size() >= words[idx].size()) newAbbr = words[idx];
                mm[newAbbr].push_back(idx);
            }
            
        }
        return ans;
    }

    bool isDigit(char& c){
        return (c>='0') && (c<='9');
    }
};