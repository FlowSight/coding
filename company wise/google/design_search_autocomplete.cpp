.// Severity: Sev2
// Date: 13Feb26
// 
// Where I failed: implementation..stuck in comparison..then moved to set..then set comparator fail..
//then basic logic fail silly mistake
// Pattern: trie

struct cmp{
    bool operator() (const pair<int,string>p1, const pair<int,string> p2) const {
        return p1.first == p2.first? p1.second < p2.second : p1.first>p2.first;
    }
};

class Trie{
    public:
    unordered_map<char,Trie*> children;
    set<pair<int,string>,cmp> ss;
    Trie(){
        children.clear();
    }

    void addWord(string& str, int idx, int cnt){
        reorder(str,cnt);
        if(idx == str.size()){
            return;
        }
        if(children.find(str[idx]) == children.end()) children[str[idx]] = new Trie();
        children[str[idx]]->addWord(str,idx+1,cnt);
    }
    void reorder(string& str, int cnt){
        auto it = ss.find({cnt-1,str});
        if(it != ss.end()) ss.erase({cnt-1,str});
        ss.insert({cnt,str});
        if(ss.size()>3)ss.erase(prev(ss.end()));
    }
};
class AutocompleteSystem {
public:
    Trie* root;
    Trie* curRoot;
    int n;
    string sen ;
    unordered_map<string,int> mm;
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new Trie();
        n = times.size();
        curRoot = root;
        for(auto i=0;i<n;i++){
            root->addWord(sentences[i],0,times[i]);
            mm[sentences[i]] = times[i];
        }
        sen = "";
    }
    
    vector<string> input(char c) {
        vector<string> ans;
        if(c == '#'){
            mm[sen]++;
            root->addWord(sen,0,mm[sen]);
            sen = "";
            curRoot = root;
            return ans;
        }
        sen.push_back(c);
        if(!curRoot || (curRoot->children.find(c) == curRoot->children.end())) {
            curRoot = nullptr;
            return ans;
        }
        curRoot = curRoot->children[c];
        for(auto it: curRoot->ss) ans.push_back(it.second);
        return ans;
    }
};