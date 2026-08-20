/// Severity: Sev0
// Date: 15Aug26
// LC: 187
// Where I failed: implementation
// Pattern: rabin karp
// Notes: additional_notes



class Solution {
public:
    long mod = 1e9+11;
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<long,vector<int>> mm;
        vector<long> exp(11,1);
        for(auto i=1;i<=10;i++){
            exp[i] = (exp[i-1]*26)%mod;
        }
        unordered_set<string>  ans;
        int n = s.size();
        long curhash = 0;
        for(auto l=0,r=0;r<n;r++){
            curhash = ((curhash * 26)%mod + (s[r]-'A'))%mod;
            if(r>=9) {
                if(r-l+1 > 10) {
                     curhash = ( curhash - (exp.back() * (s[l++]-'A'))%mod + mod)%mod;
                }
                if((mm.find(curhash) == mm.end())) {
                    mm[curhash].push_back(l);
                } else if (mm.find(curhash) != mm.end()) {
                    auto str = s.substr(l,10);
                    bool found = false;
                    for(auto it : mm[curhash]){
                        if(s.substr(it,10) == str) {
                            found = true;
                            ans.insert(str);
                            break;
                        }
                    }
                    if(!found) mm[curhash].push_back(l);
                }
            }
        }
        return vector<string>(ans.begin(),ans.end());
    }
};

// mm[hash] = [lis tof substrs start idx]