class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;
        if((words.size() == 0) || (s.size() == 0)) return ans;
        unordered_map<string,int> wordMap, seen;
        for(auto it : words) wordMap[it]++;
        int len = words.size(), wl = words[0].size(), n = s.size();

        for(auto i=0,idx = 0,cnt = 0; i < wl ; i++,idx = i,cnt = 0){
            seen.clear();
            int start = i;

            while(idx+wl-1 < n) {
                auto word = s.substr(idx,wl);
                if(wordMap.find(word) == wordMap.end()) {
                    seen.clear();
                    cnt = 0;
                    idx += wl;
                    start = idx;
                } else {
                    seen[word]++;
                    while(seen[word] > wordMap[word]) {
                        auto wordRemove = s.substr(start,wl);
                        seen[wordRemove]--;
                        start += wl;
                        cnt--;
                    }
                    cnt++;
                    idx += wl;
                }
                if(cnt == len){
                    ans.push_back(start);
                    auto wordRemove = s.substr(start,wl);
                    seen[wordRemove]--;
                    cnt--;
                    start += wl;
                }
            }

        }
        return ans;
    }
};

// trick is : O(word len) iteration at top level..and word level 2 pointer
// if we do for (i<wordlen), tC = O(wl * N )
// if we do for(i<n) tc = O(n * wl*len) from high level..but actually O(1+2+..len*wl)*2 = O(n^2)
//     if len*wl == n/2 then..1,2,..wl*len/2,wl*len/2,..suboptimal..