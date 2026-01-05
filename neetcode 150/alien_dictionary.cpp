// 29 march 2025
// its so easy..but i missed 2-3 corner cases..
// sev1
// didnt realize that abc->ab => invalid case..

class Solution {
    public:
        typedef vector<int> vi;
        typedef vector<vi> vvi;
         vvi g;
         vi ind;
        string alienOrder(vector<string>& words) {
            vector<unordered_set<int>> g(26, unordered_set<int>());
            unordered_map<int,int> ind;
            string ans = "";
            int n = words.size();
            for(auto w : words){
                for(auto c : w){
                    ind[c-'a'] = 0;
                }
            }
            for(auto i=1;i<n;i++){
                for(auto j=0;j<min(words[i].size(),words[i-1].size());j++) {
                    if(words[i][j] == words[i-1][j]){
                        if(j == min(words[i].size(),words[i-1].size())-1){
                            if(words[i-1].size() > words[i].size()) return ans;
                        }
                        continue;
                    }
                    auto u = words[i-1][j]-'a', v = words[i][j]-'a';
                    if(g[u].find(v) == g[u].end()){
                        g[u].insert(v);
                        ind[v]++;
                    }
                    break;
                }
            }
            queue<int> q;
            for(auto it : ind){
                if(it.second == 0) q.push(it.first);
            }
    
    
            while(!q.empty()) {
                auto sz = q.size();
                while(sz--){
                    auto cur = q.front();
                    q.pop();
                    ans.push_back(cur+'a');
                    for(auto v: g[cur]) {
                        ind[v]--;
                        if(ind[v] == 0)q.push(v);
                    }
                }
            }
            return ans.size() == ind.size() ? ans : "";
        }
    };