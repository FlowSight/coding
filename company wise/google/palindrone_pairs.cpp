//sev0..failed in implementation..sev0
// didnt think of below:
// 1. "" case, 
// 2. palindrome word case..
// 28jan 2026 : sev0, really struggled in non trie approach..missed revSuf case..

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


// non trie:

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        int n = words.size();
        unordered_map<string,vector<int>> mm;
        unordered_set<string> visited;
        vector<vector<int>> ans;
        for(auto i=0;i<n;i++){
            mm[words[i]].push_back(i);
        }
        for(auto it : mm){
            string word = it.first, cur = "", curRev = "";
            if(word == "") continue;
            int len = word.size();
            for(auto i=0;i<len;i++){
                cur.push_back(word[i]);
                curRev.push_back(word[len-1-i]);
                auto revWord = cur, revSuf = curRev;
                reverse(revWord.begin(),revWord.end());
                //reverse(revSuf.begin(),revSuf.end());

                if((i==len-1) && (visited.find(revWord) != visited.end())) continue;
                if(mm.find(revWord) != mm.end()) {
                    if(isPalin(word,i+1,len-1)){
                        for(auto it1 : it.second){
                            for(auto it2: mm[revWord]){
                                if((i==len-1) && (revWord == word) && (it1 == it2)) continue;
                                ans.push_back({it1,it2});
                            }
                        }
                    }
                }
                if(mm.find(revSuf) != mm.end()) { 
                    if(isPalin(word,0,len-2-i)){
                        for(auto it1 : it.second){
                            for(auto it2: mm[revSuf]){
                                if((i==len-1) && (revSuf == word) && (it1 == it2)) continue;
                                ans.push_back({it2,it1});
                            }
                        }
                    }
                }
                visited.insert(word);
            }
            if(isPalin(word,0,len-1)){
                for(auto it1 : mm[""]){
                    for(auto it2 : it.second){
                        ans.push_back({it1,it2});
                        ans.push_back({it2,it1});
                    }
                }
            }
        }
        return ans;
    }
    
    bool isPalin(string& word, int l, int r){
        if(l>=r) return true;
        while(l<r){
            if(word[l++] != word[r--]) return false;
        }
        return true;
    }
};

