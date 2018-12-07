
#include "grid.h"
#include <iostream>
#include <string>
#include "simpio.h"
#include "strlib.h"
#include "console.h"
using namespace std;

//Construct a board with pegs settled defaultly as required:
void boardConstructor(Grid<char> & board){
    for (int r = 0; r < board.numRows(); r++){  //rows
        for (int c = 0; c < board.numCols(); c++){  //columns
            board[r][c] = 'x';   // first set pegs on all positions
        }
    }
    board[3][3] = 'o';  // set center as a hole
    int blanks[4] = {0,1,5,6}; //Row or column index of blank corner positions
    for (int bR = 0; bR < 4; bR++){  //bR - Row index of blank corner
        for (int bC = 0; bC < 4; bC++){  // bC - Column index of blank corner
            board[blanks[bR]][blanks[bC]] = ' '; //Blanks of the 4 corners
        }
    }

}


void printBoard(Grid<char> & board){ // print out the pegsolitaire board
    for (int r = 0; r < 7; r++){
        for (int c = 0; c < 7; c++){
            cout << board[r][c];
        }
        cout << endl; // start a new line/row
    }
}


bool legalJump(Grid<char> & board, int r, int c, char dir){ // note the dir refers to the direction from jumping peg to the hole
    if (dir == 'N'){    //jump north
        return r-2 >= 0 && board[r-2][c] == 'o' && board[r-1][c] == 'x';
    }
    if (dir == 'E'){    //jump east
        return c+2 <= 6 && board[r][c+2] == 'o' && board[r][c+1] == 'x';
    }
    if (dir == 'S'){    //jump south
        return r+2 <= 6 && board[r+2][c] == 'o' && board[r+1][c] == 'x';
    }
    if (dir == 'W'){    //jump west
        return c-2 >= 0 && board[r][c-2] == 'o' && board[r][c-1] == 'x';
    }
    return false;
}


void markJump(Grid<char> & board, int r, int c, int & rGoal, int & cGoal, char dir, char hole, char peg){
    //jump the peg on the board according to the rules
    if (dir == 'N'){
        board[r][c] = hole;
        board[r-1][c] = hole;
        board[r-2][c] = peg;
        rGoal = r-2;
    }
    if (dir == 'E'){
        board[r][c] = hole;
        board[r][c+1] = hole;
        board[r][c+2] = peg;
        cGoal = c+2;
    }
    if (dir == 'S'){
        board[r][c] = hole;
        board[r+1][c] = hole;
        board[r+2][c] = peg;
        rGoal = r+2;
    }
    if (dir == 'W'){
        board[r][c] = hole;
        board[r][c-1] = hole;
        board[r][c-2] = peg;
        cGoal = c-2;
    }
}


//Store the steps in accordance with the graph provided by the question:
string formalizeJump(int r, int c, int rGoal, int cGoal){
    string columns[7] = {"a","b","c","d","e","f","g"};
    string rows[7] = {"1","2","3","4","5","6","7"};
    string jump = columns[c] + rows[r] + "->" + columns[cGoal] + rows[rGoal];
    return jump;
}


void Jump(Grid<char> & board, Vector<string> & jumpReceipt, int r, int c, char dir){
    int rGoal = r, cGoal = c;
    string jump;
    //jump the peg on the board according to the rules
    markJump(board,r,c,rGoal,cGoal,dir,'o','x');
    //record the jump operation:
    jump = formalizeJump(r,c,rGoal,cGoal);
    jumpReceipt.add(jump);
}


void unJump(Grid<char> & board, Vector<string> & jumpReceipt, int r, int c, char dir){
    int rGoal = r, cGoal = c;
    string jump;
    //undo the jump operation on the board
    markJump(board,r,c,rGoal,cGoal,dir,'x','o');
    //delete the recorded jump operation:
    jumpReceipt.remove(jumpReceipt.size()-1);
}


bool PegSolitaire(Grid<char> & board, Vector<string> & jumpReceipt, int nPegs){
    //Only one peg left on the board
    if (nPegs == 1) return (board[3][3] == 'x'); //If the peg is at the center, solution found; The peg isn't at the center, no solution found
    for (int r = 0; r < 7; r++){                    //for each row
        for (int c = 0; c < 7; c++){                //for each column
            if (board[r][c] == 'x'){                //if a peg, try jumping to 4 directions legally
                for (char dir: {'N','E','S','W'}){
                    if  (legalJump(board,r,c,dir)){
                        Jump(board,jumpReceipt,r,c,dir);
                        if (PegSolitaire(board,jumpReceipt,nPegs-1)){return true;} //try the sub-problem after the jump. if sub-problem is solved, the pegSolitaire is solved
                        unJump(board,jumpReceipt,r,c,dir);  //if the sub-problem has no solution, undo the jump operation. then try other directions
                    }
                }
            }
        }
    }
    return false;  //if all directions fail, no solution found
}


void Q2(){
    //construct a board
    Grid<char> board(7,7); // 7 × 7 board
    Vector<string> jumpReceipt;
    boardConstructor(board);

    //print out the original board
    cout << "Original board:" << endl;
    printBoard(board);
    cout << endl;


    if (PegSolitaire(board,jumpReceipt,32)){

        //print out the operations during the variations of the board
        cout << "The operations:" << endl;
        for (string s: jumpReceipt){
            cout << s << endl;
        }
        cout << endl;

        //print out the final board
        cout << "Final board:" << endl;
        printBoard(board);
        
    }else{
        cout << "No solution found exists" << endl;
        return;
    }

}
