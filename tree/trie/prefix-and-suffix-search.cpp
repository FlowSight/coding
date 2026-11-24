/// Severity: Sev0
// Date: 20Nov26
// LC: 745
// Where I failed:
// 1. Did not recognize that (suffix, prefix) can be one trie key: suffix + '{' + prefix.
// 2. This is a trie of suffixes of word + '{' + word, not a suffix tree.
// 3. The largest valid word index can be stored by inserting words in increasing index order
//    and overwriting widx at every visited node.
// 4. If a query edge is missing, return -1, not the current node's widx: the full query
//    has not matched.
// Pattern: combined-key trie + overwrite with latest/largest index
// Complexity: build O(N * W^2), query O(prefix length + suffix length), space O(N * W^2).



class Trie { 
    public:
    vector<Trie*> children;
    int widx = -1;
    Trie(){
        children = vector<Trie*>(27,nullptr);
    }
    void addWord(string& word, int idx, int wordIdx){
        widx = wordIdx;
        if(idx == word.size()) return;
        if(!children[word[idx]-'a']) children[word[idx]-'a'] = new Trie();
        children[word[idx]-'a']->addWord(word,idx+1,wordIdx);
    }
    int find(string& word, int idx,int pividx){
        if(idx == word.size()) return widx;
        if(!children[word[idx]-'a']) {
            return -1; // i confused here also on returning -1 vs widx
        }
        return  children[word[idx]-'a']->find(word,idx+1,pividx);
    }
};

class WordFilter {
public:
    Trie* root;
    WordFilter(vector<string>& words) {
        root = new Trie();
        int n = words.size();
        for(auto i=0;i<n;i++){
            string word = words[i] + "{" + words[i];
            for(auto j=0;j<words[i].size();j++){
                root->addWord(word,j,i);
            }
        }
    }
    
    int f(string pref, string suff) {
        string word = suff + "{" + pref;
        return root->find(word,0,suff.size());
    }
};
