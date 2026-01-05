//sev2 : didnt realize that we have to putinreverse words in trie

class Trie {
    public:
    vector<Trie*> children;
    bool eow;
    Trie(bool _eow = false) {
        eow = _eow;
        children = vector<Trie*>(26,nullptr);
    }

    void add(string& word, int idx){
        if(idx == -1) {
            eow = true;
            return;
        }
        if(!children[word[idx]-'a']) children[word[idx] - 'a'] = new Trie();
        children[word[idx] - 'a']->add(word,idx-1);
    }

    bool find(string& word, int idx, int& len, int& maxLen) {
        if((idx == -1) || eow || (len == maxLen)) {
            return eow;
        }
        len++;
        return children[word[idx] - 'a'] ?  children[word[idx] - 'a']->find(word,idx-1,len,maxLen) : false;
    }
};
class StreamChecker {
public:
    Trie* root;
    string str;
    int maxSize;
    StreamChecker(vector<string>& words) {
        root = new Trie();
        str = "";
        maxSize = 0;
        for(auto it : words) {
            root->add(it,it.size()-1);
            maxSize = max(maxSize,(int)it.size());
        }
    }
    
    bool query(char letter) {
        str.push_back(letter);
        int n = str.size();
        return root->find(str,n-1,0,maxSize);
    }
};

// only chars? yes
// which chars? a-z 
// words is static? yes
// len of words arr: any

// approach
// 1. make trie from words
// 2. append incoing letter to string
// 2. query from end of string in trie O(len)
// trie make = O(len*n + len)