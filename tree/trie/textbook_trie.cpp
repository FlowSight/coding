#include <vector>

using namespace std;


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
    }
};
//  trie is tricky...
//  mark eow ONLY on idx == s.size()