// 20 feb 25
// coming off as TLE..although code is correct
// Issue : 2-3 compiler errror in first version of code..
// sev2

class Trie {
    public:
        vector<Trie*> children;
        int eow;
        Trie() {
            children = vector<Trie*>(26,nullptr);
            eow = 0;
        }
        void addWord(string& word, int idx){
            if(idx == word.size()){
                eow = 1;
                return;
            }
            int cIdx = word[idx]-'a';
            if(!children[cIdx]) {
                children[cIdx] = new Trie();
            }
            children[cIdx]->addWord(word,idx+1);
        }

};


class Solution {
public:
    vector<string> ans;
    vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie* trie = new Trie();
        for(auto &it : words){
            trie->addWord(it,0);
        }
        int m = board.size(), n = board[0].size();
        string word = "";
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                word = "";
                helper(board,i,j,trie,word,m,n);
            }
        }
        return ans;
    }

    void helper(vector<vector<char>>& board, int r, int c, Trie* root, string& cur, int& m , int& n){
        if((r<0) ||  (c<0) || (r>=m) || (c>=n) || (board[r][c] == '#')) return;
        auto cIdx = board[r][c]-'a';

        if(!root->children[cIdx]) return;
        root = root->children[cIdx];

        cur.push_back(board[r][c]);
        board[r][c] = '#';

        if(root->eow){
            root->eow = false;
            ans.push_back(cur);
        }

        for(auto d: dirs){
            auto xx = d[0] + r, yy = d[1]+c;
            if((xx<0) ||  (yy<0) || (xx>=m) || (yy>=n) || (board[xx][yy] == '#')) continue;
            helper(board,xx,yy,root,cur,m,n);
        }

        board[r][c] = 'a'+cIdx;
        cur.pop_back();
    }
};