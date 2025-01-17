// 22 dec 2024..8 min.. no mistake
// Verdict : PASS

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_map<int,unordered_map<char,int>> rowMap, colMap, boxMap;
        for(auto i=0;i<9;i++) {
            for(auto j=0;j<9;j++){
                if(board[i][j] == '.') continue;
                rowMap[i][board[i][j]]++;
                colMap[j][board[i][j]]++;
                int boxIdx = (i/3)*3+(j/3);
                boxMap[boxIdx][board[i][j]]++;
                if((rowMap[i][board[i][j]] > 1)  || (colMap[j][board[i][j]] > 1) || (boxMap[boxIdx][board[i][j]] >1)) return false;
            }
        }
        return true;
    }
};