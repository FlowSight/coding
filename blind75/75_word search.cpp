//14 dec 2024...my code was correct though..its a cpp and input issue..verdict : FAIL


    typedef vector<char> vc;
    typedef vector<vc> vvc;
    typedef vector<int> vi;
    typedef vector<vi> vvi;

class Solution {
public:

    vvi dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    bool exist(vector<vector<char>>& board, string word) {
        if(word.size() == 0)return false;
        int m = board.size(), n = board[0].size();
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(word[0] == board[i][j]){
                    bitset<36> bs(0);
                    if(dfs(word,0,i,j,board, bs))return true;
                }
            }
        }
        return false;
    }

    bool dfs(string& s, int idx, int r, int c, vvc& board, bitset<36>& bs){
        if(idx == s.size())return true;
        if(r>=board.size() || r<0 || c>=board[0].size() || c<0 || (board[r][c]!=s[idx]))return false;
        board[r][c] = '@';
        for(auto d: dirs){
            if(dfs(s,idx+1,d[0]+r,d[1]+c,board,bs))return true;
        }
        board[r][c]  = s[idx];
        return false;
    }
};
