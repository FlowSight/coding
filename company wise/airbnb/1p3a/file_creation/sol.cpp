#include<bits/stdc++.h>

using namespace std;
using callback = function<void(void)>;

class Trie {
    public:
    vector<Trie*> children;
    int val =-1;
    callback cb;
    Trie(){
        val = -1;
        children = vector<Trie*>(26,nullptr);
    }
    void add(vector<char>& arr, int idx, int _val){
        if(idx == arr.size()){
            val = _val;
            return;
        }
        if(!children[arr[idx]-'a']){
            children[arr[idx]-'a'] = new Trie();
        }
        children[arr[idx]-'a']->add(arr,idx+1,_val);
    }
    int find(vector<char>& arr, int idx){
        if(idx == arr.size()){
            return val;
        }
        if(!children[arr[idx]-'a']) return -1;
        return children[arr[idx]-'a']->find(arr,idx+1);
    }
};
class TrieManager {
    public:
    Trie* root;
    TrieManager(){
        root = new Trie();
    }
    int get(string path){
        vector<char> parts;
        stringstream ss(path);
        string cur = "";
        while (getline(ss,cur,'/'))
        {
            if(cur.size() == 0)continue;
         parts.push_back(cur[0]);  
        }
        return root->find(parts,0);
    }
    void create(string path, int val){
        vector<char> parts;
        stringstream ss(path);
        string cur = "";
        while (getline(ss,cur,'/'))
        {
            if(cur.size() == 0)continue;
         parts.push_back(cur[0]);  
        }
        root->add(parts,0,val);
    }
};



int main(){
        TrieManager tm;
    tm.create("/a", 1);
    cout<<tm.get("/a")<<endl;
    tm.create("/a/b", 2);
    cout<<tm.get("/a/b")<<endl;
    tm.create("/c/d", 1); //t exist
    cout<<tm.get("/c")<<endl;
}