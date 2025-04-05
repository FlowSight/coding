// 16/2/25
// 23 mins..
// didnt get right idea + coded wrongly for 17 mins..
// got right idea after that..but still had huge logical mistake after that 
// 1 compiler error..
// 1 optimization remained undone..
// sev0

class Solution {
public:
    vector<vector<int>> dirs = {{1,0,},{0,1},{-1,0},{0,-1}};
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();

        for(auto i=0;i<m;i++) {
            dfs(board,i,0,'$',m,n);
            dfs(board,i,n-1,'$',m,n);
        }
        for(auto j=0;j<n;j++) {
            dfs(board,0,j,'$',m,n);
            dfs(board,m-1,j,'$',m,n);
        }

        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(board[i][j] == '$') board[i][j] = 'O';
                else if(board[i][j] == 'O') board[i][j] = 'X';
            }
        }
    }
    void dfs(vector<vector<char>>& board, int r, int c,char ch,int m, int n){
        if(board[r][c] != 'O') return;
        board[r][c] = ch;

        for(auto d : dirs){
            auto xx = d[0] + r , yy = d[1]+c;
            if((xx<0) || (yy <0) || (xx>=m) || (yy>=n) || (board[xx][yy] !='O')) continue;
            dfs(board,xx,yy,ch,m,n);
        }
    }
};