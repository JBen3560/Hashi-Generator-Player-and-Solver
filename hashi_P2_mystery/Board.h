#ifndef BOARD_H
#define BOARD_H

#include "GridPosition.h"

class Board {
private:
    GridPosition** board; // 2D array of GridPosition objects

public:
    Board(); // Constructor
    ~Board(); // Destructor

    // Game setup
    void setUpGame(); // Function to set up the game
    int randomNum(int,int); // Function to generate a random number
    int countBranches(int r, int c); // Function to count the branches of an island

    // Game play
    void runGame(); // Function to run the game
    bool checkWin(); // Function to check if the game has been won
    bool validBridge(string input); // Function to make sure a bridge builds right
    void printBoard(); // Function to print the board
};

#endif