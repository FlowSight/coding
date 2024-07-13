typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<int> vi;
typedef vector<vi> vvi;

struct Trie {
    public:
    Trie* children[26] = {};
    string* word;

    void add (string& word){
        Trie* node = this;
        for(auto c: word){
            int idx = c-'a';
            if(!node->children[idx])node->children[idx] = new Trie();
            node = node->children[idx];
        }
        node->word = &word;
    }
};

class Solution {
public:
    vector<string> ans;
    vvi dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    vvc board;
    int m,n;
    vector<string> findWords(vector<vector<char>>& grid, vector<string>& words) {
        board = grid;
        Trie* trienode = new Trie();
        ans = vector<string>();
        for(auto& w : words){
            trienode->add(w);
        }
        m = board.size();
        n = board[0].size();
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                auto root = trienode;
                dfs(i,j,root);
            }
        }
        return ans;
    }

    void dfs(int r, int c, Trie* node){
        if(!node || r>=m || r<0 || c<0 || c>=n || board[r][c] == '$' 
            || !node->children[board[r][c]-'a']) return;
        
        char tmp = board[r][c];
        node = node->children[tmp-'a'];
        if(node->word){
            ans.push_back(*node->word);
            node->word = nullptr;
        }
        
        board[r][c] = '$';
        dfs(r+1,c,node);
        dfs(r,c+1,node);
        dfs(r-1,c,node);
        dfs(r,c-1,node);
        board[r][c] = tmp;
    }
};