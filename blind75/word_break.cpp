//  30 dec 2024..
// 15 mins
//  made mistake in array index as dp array was n+1 size...
//  verdict : FAIL


class Trie {
    public:
    vector<Trie*> children;
    int eow;
    Trie(){
        eow = 0;
        children = vector<Trie*>(26,nullptr);
    }
    void addWord(string& s, int idx = 0){
        if(idx >= s.size()) {
            eow = (idx == s.size());
            return;
        }
        if(!children[s[idx]-'a']) {
            children[s[idx]-'a'] = new Trie();
        }
        children[s[idx]-'a']->addWord(s,idx+1);
    }

    bool search(string& s, int idx = 0){
        if(idx >= s.size()) return eow;
        if(!children[s[idx]-'a']) return false;
        return children[s[idx]-'a']->search(s,idx+1);
    }
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        Trie* root = new Trie();
        int n = s.size();
        vector<int> dp(n+1,0);
        dp[0] = 1;
        for(auto w : wordDict){
            reverse(w.begin(),w.end());
            root->addWord(w);
        }
        Trie* tmp = root;
        for(auto i=0;i<n;i++){
            tmp = root;
            for(auto j=i;(j>=0) && tmp;j--){
                tmp = tmp->children[s[j]-'a'];
                if(dp[j] && tmp && tmp->eow){
                    dp[i+1] = 1;
                }
            }
        }
        return dp[n];
    }
};


//6 nov 2024..11 mins..no error

class Trie {
    public:
    bool isWord;
    vector<Trie*> children;

    Trie(){
        children = vector<Trie*>(26,nullptr);
        isWord = false;
    }

    void addWord(string word, int idx){
        if(idx == word.size()){
            isWord = true;
            return;
        }
        if(!children[word[idx]-'a']){
            children[word[idx]-'a'] = new Trie();
        }
        children[word[idx]-'a']->addWord(word,idx+1);
    }
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        Trie* root = new Trie();
        int n = s.size();
        for(auto w : wordDict){
            reverse(w.begin(),w.end());
            root->addWord(w,0);
        }
        vector<int> dp(n+1,0);
        dp[0] = 1;
        for(auto i=1;i<=n;i++){
            auto node = root;
            for(auto len=1;len<=20 && i-len+1>0 && node;len++){
                auto ch = s[i-len];
                node = node->children[ch-'a'];
                if(node && node->isWord && dp[i-len]) {
                    dp[i] = 1;
                    break;
                }
            }
        }
        return dp[n];
    }
};