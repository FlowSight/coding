// Task Description
// Design a 2D board simulator with two types of pieces.

// Tasks
// Class Design: Design a class to represent the board and implement the functionality to add pieces.
// Pieces are added from the bottom of the board.
// Adding a piece causes all existing pieces in that column to shift upwards.
// Column Check: After adding a piece, check if there's any column filled entirely with the same type of piece.
// Row Check: After adding a piece, check if there's any row filled entirely with the same type of piece.
// Constraints & Assumptions
// Board size is m x n.
// Two types of pieces (e.g., 'X' and 'O', or 0 and 1).
// Deliverables
// Board class implementation.
// Example code demonstrating initialization and basic operations (adding pieces, checking win conditions).


// board size given : yes, m x n
// 0, 1
// only row and col check : yes

// solution :
// 1. use dll 


#include <iostream>
#include <unordered_map>

using namespace std;

struct DLL {
    int val;
    DLL* prev;
    DLL* next;
    DLL(int _val){
        val = _val;
    }
};

class GridGame{
    public:
    int row, col;
    vector<DLL*> cols;
    unordered_map<int,DLL*> first, last;
    vector<int> colSum, rowSum;

    GridGame(int m, int n){
        if(!m || !n) throw runtime_error("invalid dimension");
        row = m, col = n;
        cols = vector<DLL*>(col,new DLL(0));
        colSum = vector<int>(col,0);
        rowSum  = vector<int>(row,0);
        for(auto c=0;c<col;c++){
            auto node = new DLL(0);
            first[c] = node;
            for(auto r=0;r<row-1;r++){
                auto newNode = new DLL(0);
                node->next = newNode;
                newNode->prev = node;
                node = node->next;
            }
            last[c] = node;
        }
    }

    int move(int player,int colVal){
        if(colVal >= col) throw runtime_error("invalid move");
        auto startNode = first[colVal];
        auto endNode = last[colVal];
        auto node = new DLL(player);

        if(col >1 ){
            auto prev = endNode->prev;
            prev->next = nullptr;
            endNode->prev = nullptr;
            last[colVal] = prev;
            colSum[colVal] -= endNode->val;
        } else {
            colSum[colVal] -= endNode->val;
            last[colVal] = node;
            startNode = nullptr;
        }

        node->next = startNode;
        if(startNode) startNode->prev = node;
        first[colVal] = node;
        colSum[colVal] += node->val;

        if(colSum[colVal] == row * player) return player;
        for(auto r = 0;r<row;r++){
            rowSum[r] += node->val;
            auto next = node->next;
            if(next) rowSum[r] -= next->val;
            if((rowSum[r] == player*col)) return player;
            node = next;
        }
        rowSum[row-1] -= endNode->val;
        if(rowSum[row-1] == player*col) return player;
        return 0;
    }
};

void testGame(){
    GridGame gg(3,3);
    for(auto i=0;i<2;i++) cout<<gg.move(1,1)<<endl;
    for(auto i=0;i<3;i++) cout<<gg.move(-1,i)<<endl;
}

int main(){
    testGame();
    return 0;
}

//  0 0
// 0 1 0
// 0 1 0
 // -1