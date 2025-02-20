#ifndef BOARD_H
#define BOARD_H

#include "GridPosition.h"

class Board {
private:
    GridPosition** board; // 2D array of GridPosition objects

public:
    Board(string); // Parameterized constructor
    Board(); // Extra credit constructor
    ~Board(); // Destructor

    void runGame(); // Function to run the game
    int countBranches(int r, int c); // Function to help set island numbers
    bool checkWin(); // Function to check if the game has been won
    bool validBridge(string input); // Function to make sure a bridge builds right
    void placeBridges(string input); // Function to place bridges
    void printBoard(); // Function to print the board
};

#endif