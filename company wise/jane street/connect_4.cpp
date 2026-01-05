// Implement a Connect Four variant where when a player inserts a disc into a column, 
// the disc moves to the bottom cell of that column and pushes all existing discs in that column up by one. 
// If the column is already full, the disc that is pushed above the top row is ejected and removed from the board.
//  Design the board representation and APIs to: (

// initialize with R rows and C columns (default 6x 7), (
// drop a disc for a given player into a column, (
// detect a win (four in a row horizontally, vertically, or diagonally) after each move, and (
// support undo and redo of moves. Specify time and space complexities, data structures used, and how you handle edge cases such as ejected discs, invalid columns, alternating turns, and draw detection. Provide code for the core operations.

// darjeeling

// 17-21 is good weather 
// 17,18,19 nights
// vande bharat while going cc 
// bagdogra flight return 
// hotels : https://book.summithotels.in/booking/roomlisting-summithotelsandresorts-summitoakdeneresortspadarjeeling-en?_glCID=604665662.1767124804#
    // Udaan Hotels : walk a lot..
    // https://book.hotelcanopy.com/ : mall road, 2 rooms with view, 2days room1, 1 day room2
// todo
//     - toy train
//     - ropeway
//     - batasia loop 
//     - glenary
//     - 

#include<iostream>

using namespace std;

class DLL  {
    public:
    int val;
    DLL* prev;
    DLL* next;
    DLL(int _val){
        val = _val;
        prev = nullptr;
        next = nullptr;
    }
};
class Connect4 {
    public:
    int row, col;
    //vector<DLL*> cols;
    unordered_map<int,DLL*> start, last;
    Connect4(int r, int c){
        row = r, col = c;
        //cols = vector<DLL*>(c,new DLL(0));
        for(auto i=0;i<c;i++){
            start[i] = last[i] = new DLL(0);
            auto prev = start[i];
            for(auto j=0;j<r-1;j++){
                auto next = new DLL(0);
                prev->next = next;
                next->prev = prev;
                prev = prev->next;
            }
            last[i] = prev;
        }
    }

    void makeMove(int player, int c){
        auto newNode = new DLL(player);
         if(row == 1) {
             start[c] = last[c] = newNode;
             return;
         }
        auto startNode = start[c];
        auto lastNode = last[c];
        auto prevLastNode = lastNode->prev;
       

        newNode->next = startNode;
        startNode->prev = newNode;
        prevLastNode->next = nullptr;
        lastNode->prev = nullptr;

        start[c] = newNode;
        last[c] = prevLastNode;
    }
    int checkCol(int c){
        auto startNode = start[c];
        int val = -1, len = 0;
        while(startNode){
            if(val == startNode->val) len++;
            else {
                val = startNode->val;
                len = val ? 1 : 0; 
            }
            if(len == 4) return startNode->val;
            startNode = startNode->next;
        }
        return 0;
    }

    int checkRow(int c){
        vector<DLL*> nodes;
        for(auto c=0;c<col;c++) {
            nodes.push_back(start[c]);
        }
        for(auto r = 0;r<row;r++) {
            int val = -1, len = 0;
            for(auto it : nodes){
                if(it->val == val) len++;
                else {
                    val = it->val;
                    len = val ? 1 : 0;
                }
                if(len == 4) return val;
            }
            for(auto &it : nodes) it = it->next;
        }
        return 0;
    }

    int checkDiag(int c){
        int startIdx = max(0,c-3), endIdx = min(col-1,c+3);
        //vector<DLL*> nodes;
        for(auto i=startIdx;i<=c;i++){
            int val = -1, len = 0;
            for(auto k=0,j=i;(j<col) && (j<i+4);j++,k++){
                auto node = start[j];
                for(auto x=0;x<k;x++) node = node->next;
                if(node && (node->val == val)) {
                    val = node->val;
                    len++;
                } else {
                    val = node->val;
                    len = 1;
                }
                if(len == 4) return val;
            }
        }
        for(auto i=endIdx;i>=c;i--){
            int val = -1, len = 0;
            for(auto k=0,j=i;(j>=0) && (j>i-4);j--,k++){
                auto node = start[j];
                for(auto x=0;x<k;x++) node = node->next;
                if(node && (node->val == val)) {
                    val = node->val;
                    len++;
                } else {
                    val = node->val;
                    len = 1;
                }
                if(len == 4) return val;
            }
        }
        return 0;
    }

    int move(int player, int c){
        if((c>=col) || (c<0) || (player <1) || (player >2)) return -1; // invalid move;
        makeMove(player,c);
        int val = 0;
        if(val = checkCol(c))return val;
        if(val = checkRow(c)) return val;
        return checkDiag(c);
    }
};

class Solution {
    public:
    static void testUtil() {
        Connect4 con4(5,5);
        cout<<con4.move(1,0)<<endl;
        for(auto i=0;i<2;i++)   cout<<con4.move(1,1)<<endl;
        for(auto i=0;i<3;i++)   cout<<con4.move(1,2)<<endl;
        cout<<con4.move(1,3)<<endl;
        for(auto i=0;i<3;i++)   cout<<con4.move(2,3)<<endl;
        
    }
};

int main () {
    Solution::testUtil();
    return 0;
}

// dll to keep cols 
// keep head of col dlls to unordered_map
// if we push to col c, 
//     make move O(r)
//     start validating:O(4*16) = O(1)
//         check for diagonal case 
//          start checking from max(c-3,0) column idx for bl-tr diag 
//          start checking from max(c-3,0) column idx for tl-br diag
//          check the col 
//          check the row
// user a:1, b :2 can we assume?
// if c== 0, ??
// if c is invalid??



