class Trie {
public:
    vector<Trie*> children;
    bool eow;
    Trie() {
        children = vector<Trie*>(26,nullptr);
        eow = false;
    }
    
    void insert(string word, int idx = 0) {
        if(idx == word.size()) {
            eow = true;
            return;
        }
        if(!children[word[idx]-'a']) { 
            children[word[idx]-'a'] = new Trie();
        }
        children[word[idx]-'a']->insert(word,idx+1);
    }
    
    bool search(string word, int idx = 0, bool matchWhole = true) {
        if(idx == word.size())return matchWhole ? eow : true;
        if(!children[word[idx]-'a']) return false;
        return children[word[idx]-'a']->search(word,idx+1,matchWhole);
    }
    
    bool startsWith(string prefix, int idx = 0) {
        return search(prefix,0,false);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */