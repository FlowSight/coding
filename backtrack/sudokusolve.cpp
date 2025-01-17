class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        isValidSudokuHelper(board,0,0);
    }

    bool isValidSudokuHelper(vector<vector<char>>& board, int x, int y) {
        if(x == 9)return true;
        if(board[x][y] == '.'){
            for(auto k=1;k<=9;k++){
                if(!isRowValid(board,x,y,k)) continue;
                if(!isColValid(board,x,y,k)) continue;
                if(!isBoxValid(board,x,y,k)) continue;
                board[x][y] = '0'+k;
                if(isValidSudokuHelper(board,x+(y==8),(y+1)%9))return true;
                board[x][y] = '.';
            }
        } else {
            return isValidSudokuHelper(board,x+(y==8),(y+1)%9);
        }
        return false;
    }

    bool isRowValid(vector<vector<char>>& board, int x, int y, int k){
        for(auto i=0;i<9;i++){
            if(board[x][i] == '0'+k)return false;
        }
        return true;
    }
    bool isColValid(vector<vector<char>>& board, int x, int y, int k){
        for(auto i=0;i<9;i++){
            if(board[i][y] == '0'+k)return false;
        }
        return true;
    }
    bool isBoxValid(vector<vector<char>>& board, int x, int y, int k){
        int r_start = x/3*3, r_end = r_start+2, c_start = y/3*3, c_end = c_start+2;
        for(auto i=r_start;i<=r_end;i++){
            for(auto j=c_start;j<=c_end;j++){
                if(board[i][j] == '0'+k)return false;
            }
        }
        return true;
    }
};