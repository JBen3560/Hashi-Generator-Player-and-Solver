#ifndef BOARD_H
#define BOARD_H

#include "GridPosition.h"

class Board {
private:
    GridPosition** board; // 2D array of GridPosition objects

public:
    Board(); // Default credit constructor
    Board(string); // Parameterized constructor
    Board(bool ec); // Extra credit constructor
    ~Board(); // Destructor

    void runGame(); // Function to run the game
    int countChains(int r, int c); // Function to count chains on a node
    bool checkWin(); // Function to check if the game has been won
    bool validChain(string input); // Function to input validate a chain
    void placeChains(string input); // Function to place chains
    void printBoard(); // Function to print the board
};

#endif