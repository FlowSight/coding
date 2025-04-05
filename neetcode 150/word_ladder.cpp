// 26 feb 26
// 15 mins..
// mistake in reading qs..expected ans was misread..
// sev2
// need to optimize with forming graph

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordDict, seen;
        int ans = 0;
        for(auto &w : wordList) wordDict.insert(w);

        queue<string> q;
        seen.insert(beginWord);
        q.push(beginWord);

        while(!q.empty()) {
            auto sz = q.size();
            ans++;
            while(sz--){
                auto word = q.front();
                q.pop();

                if(word == endWord) return ans;

                int n = word.size();

                for(auto i=0;i<n;i++){
                    auto ch = word[i];
                    for(auto c = 'a';c<='z';c++){
                        word[i] = c;
                        if(wordDict.find(word) == wordDict.end()) continue;
                        if(seen.find(word) != seen.end()) continue;
                        seen.insert(word);
                        q.push(word);
                    }
                    word[i] = ch;
                }
            }
        }
        return 0;
    }
};
