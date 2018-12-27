//
//  playMove.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <tic-tac-toe/playMove.h>

using namespace std;

void playMove(int board[3][3], int row, int col, bool& turn, bool& validMove, bool& gameOver, int& winCode) {

    // If the game is over, do nothing
    if (gameOver) return;

    // Insert your code here
    
    else{
        //Place X or O in the empty Board Cell and Checks if move is valid
        if(board[row][col] == Empty){
            validMove = true;
            gameOver = false;
            if (turn)
                board[row][col] = X;
            else
                board[row][col] = O;
        }
        else{
            validMove = false;    
            gameOver = false;  
        }
        
        //Switch Turns between X and O 
        if(turn == true && validMove == true)
            turn = false;
        else if(turn == false && validMove == true)
            turn = true;
        
        //Checks every winning combination and assigns a number to winCode respectively
            if((board[0][0] == X && board[0][1] == X && board[0][2] == X) || (board[0][0] == O && board[0][1] == O && board[0][2] == O)){
                winCode = 1;
                gameOver = true;
            }else if((board[1][0] == X && board[1][1] == X && board[1][2] == X) || (board[1][0] == O && board[1][1] == O && board[1][2] == O)){
                winCode = 2;
                gameOver = true;
            }else if((board[2][0] == X && board[2][1] == X && board[2][2] == X) || (board[2][0] == O && board[2][1] == O && board[2][2] == O)){
                winCode = 3;
                gameOver = true;
            }else if((board[0][0] == X && board[1][0] == X && board[2][0] == X) || (board[0][0] == O && board[1][0] == O && board[2][0] == O)){
                winCode = 4;
                gameOver = true;
            }else if((board[0][1] == X && board[1][1] == X && board[2][1] == X) || (board[0][1] == O && board[1][1] == O && board[2][1] == O)){
                winCode = 5;
                gameOver = true;
            }else if((board[0][2] == X && board[1][2] == X && board[2][2] == X) || (board[0][2] == O && board[1][2] == O && board[2][2] == O)){
                winCode = 6;
                gameOver = true;
            }else if((board[0][0] == X && board[1][1] == X && board[2][2] == X) || (board[0][0] == O && board[1][1] == O && board[2][2] == O)){
                winCode = 7;
                gameOver = true;
            }else if((board[0][2] == X && board[1][1] == X && board[2][0] == X) || (board[0][2] == O && board[1][1] == O && board[2][0] == O)){
                winCode = 8;
                gameOver = true;
            }else if((board[0][0] != Empty) && (board[0][1] != Empty) && (board[0][2] != Empty) && (board[1][0] != Empty) && (board[1][1] != Empty) && (board[1][2] != Empty) && (board[2][0] != Empty) && (board[2][1] != Empty) && (board[2][2] != Empty)){
                winCode = 0;
                gameOver = true;
            }
    }   
    
    //The function must always print the output specified in the handout before it exits
    // Use the standard output (i.e., cout) to print the output

    // Insert code to print the output below
    //Print out contents of board
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
        cout << board[i][j] << " ";    
        }
    }
    
    //print out row, column, turn, if move was valid and the wining code
    cout << row << " " << col << " " << turn << " " << validMove << " " << gameOver << " " << winCode << " "<< endl;
    
 
}

