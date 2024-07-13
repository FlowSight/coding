struct Trie {
    vector<Trie*> children;
    int eow;
    Trie(){
        children = vector<Trie*>(26,nullptr);
        eow = 0;
    }
    void addWord(const string& s, int idx){
        if(idx == s.size()){
            eow = 1;
            return;
        }
        if(!children[s[idx]-'a']){
            children[s[idx]-'a'] = new Trie();
        }
        children[s[idx]-'a']->addWord(s,idx+1);
    }

    bool find(const string& s, int idx){
        if(idx == s.size()){
            return eow;
        }
        return children[s[idx]-'a'] && children[s[idx]-'a']->find(s,idx+1);
        // if(s[idx] == '.'){
        //     for(auto i=0;i<26;i++){
        //         if(children[i] && children[i]->find(s,idx+1))return true;
        //     }
        // } else {
        //     return children[s[idx]-'a'] && children[s[idx]-'a']->find(s,idx+1);
        // }
        // return false;
    }
};

class WordDictionary {
public:
    Trie* root;
    WordDictionary() {
        root = new Trie();
    }
    
    void addWord(string word) {
        root->addWord(word,0);
    }
    
    bool search(string word) {
        return root->find(word,0);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

//  trie is tricky...
//  mark eow ONLY on idx == s.size()