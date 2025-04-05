// 19/2/25
// 2 complier error..probably because i was having headache..
// sev2

class Trie {
public:
    vector<Trie*> children;
    int eow;
    Trie() {
        children = vector<Trie*>(26,nullptr);
        eow = 0;
    }
    
    void insert(string word, int idx = 0) {
        if(word.size() == idx) {
            eow = 1;
            return;
        }
        auto cIdx = word[idx] - 'a';
        if (!children[cIdx]) {
            children[cIdx] = new Trie();
        }
        children[cIdx]->insert(word,idx+1);
    }
    
    bool search(string word, int idx = 0) {
        if(word.size() == idx) {
            return eow;
        }
        auto cIdx = word[idx] - 'a';
        if (!children[cIdx]) {
            return false;
        }
        return children[cIdx]->search(word,idx+1);
    }
    
    bool startsWith(string word, int idx = 0) {
        if(word.size() == idx) {
            for(auto i=0;i<26;i++){
                if(children[i]) return true;
            }
            return eow;
        }
        auto cIdx = word[idx] - 'a';
        if (!children[cIdx]) return false;
        return children[cIdx]->startsWith(word,idx+1);
    }
};
