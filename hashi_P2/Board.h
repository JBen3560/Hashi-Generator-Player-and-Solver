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
    void createBranch(int r, int c); // Function to help build the game board
    bool validBranch(int dist, char dir, int r, int c); // Function to make sure branches generate right
    bool noNeighbors(int r, int c); // Function to make sure an island has no neighbors
    int countBranches(int r, int c); // Function to help set island numbers

    // Game play
    void runGame(); // Function to run the game
    bool checkWin(); // Function to check if the game has been won
    bool validBridge(string input); // Function to make sure a bridge builds right
    void printBoard(); // Function to print the board
};

#endif