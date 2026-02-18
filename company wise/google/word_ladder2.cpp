// 13feb26
// thought of layerd bfs..but still timeout..need bfs+dfs..test case issue.

// 22 jan.26..failed.sev0.
// could not think of layer by layer bfs..clear visited at each layer
// another way is do bfs with only nodes, not vector, then do dfs to construct path..
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> ans;
        unordered_set<string> valid, visited;
        for(auto it : wordList)valid.insert(it);
        if(valid.find(endWord) == valid.end()) return ans;
        if(beginWord == endWord) {
            ans.push_back({endWord});
            return ans;
        }
        int len = beginWord.size();

        deque<vector<string>> q;
        q.push_back({beginWord});
        int minLen = wordList.size()+1, level = 0;

        while(!q.empty()){
            auto sz = q.size();
            level++;
            for(auto& it : visited) valid.erase(it);
            visited.clear();
            while(sz--){
                auto curList = q.front();
                q.pop_front();
                if(level > minLen) continue;
                auto word = curList.back();
                if(word == endWord) {
                    ans.push_back(curList);
                    minLen = level;
                    continue;
                }
                for(auto i=0;i<len;i++) {
                    auto tmp = word[i];
                    for(auto c='a';c<='z';c++){
                        word[i] = c;
                        if(valid.find(word) == valid.end()) continue;
                        curList.push_back(word);
                        q.push_back(curList);
                        curList.pop_back();
                        visited.insert(word);
                    }
                    word[i] = tmp;
                }
            }
        }
        return ans;
    }
};
