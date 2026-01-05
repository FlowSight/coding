//sev0..failed in implementation..sev0

class Trie {
    public:
    vector<Trie*> children;
    bool isPrefixPalin, eow;
    vector<int> indices, eowIndices;
    Trie(){
        children  = vector<Trie*>(26,nullptr);
        isPrefixPalin = eow = false;
    }
    void addWord(string& w, int idx, int& wordIdx){
        if(idx <0){
            eow = true;
            eowIndices.push_back(wordIdx);
            return;
        }
        if(!children[w[idx]-'a']) children[w[idx]-'a'] = new Trie();
        if(isPalin(w,0,idx)) {
            //cout<<w<<" "<<idx<<endl;
            isPrefixPalin = true;
            indices.push_back(wordIdx);
        }
        children[w[idx]-'a']->addWord(w,idx-1,wordIdx);
    }
    bool isPalin(string& s, int l, int r){
        //if(l>r) return  false;
        while(l<r){
            if(s[l++] != s[r--]) return false;
        }
        return true;
    }
};

bool isPalin(string& s, int l, int r){
    //if(l>r) return  false;
    while(l<r){
        if(s[l++] != s[r--]) return false;
    }
    return true;
}
class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        Trie* root = new Trie();
        vector<vector<int>> ans;
        int n = words.size(), len = 0;
        for(auto i=0;i<n;i++){
            len = words[i].size();
            root->addWord(words[i],len-1,i);
        }
        auto tmp = root;
        for(auto i=0;i<n;i++){
            vector<int> res;
            tmp = root;
            //cout<<words[i]<<endl;
            if(words[i].size() == 0){
                for(auto idx : tmp->indices){
                    if(i == idx) continue;
                    ans.push_back({i,idx});
                    ans.push_back({idx,i});
                }
                continue;
            }
            for(auto j=0;j<words[i].size();j++) {
                tmp = tmp->children[words[i][j] -'a'];
                if(!tmp) break;
                if(j== words[i].size() -1) {
                    for(auto idx : tmp->indices){
                        if(i == idx) continue;
                        ans.push_back({i,idx});
                    }
                    for(auto idx : tmp->eowIndices){
                         if(i == idx) continue;
                        ans.push_back({i,idx});
                    }
                } else if(isPalin(words[i],j+1,words[i].size()-1)) {
                    for(auto idx : tmp->eowIndices){
                         if(i == idx) continue;
                        ans.push_back({i,idx});
                    }
                }
            }
        }
        return ans;
    }
};
