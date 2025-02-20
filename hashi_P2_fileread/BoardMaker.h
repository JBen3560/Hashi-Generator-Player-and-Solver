#ifndef BOARDMAKER_H
#define BOARDMAKER_H

#include "GridPosition.h"

class BoardMaker {
public:
    static void setUpBoard(int r, int c, GridPosition** board); // Function to help build the game board
    static int randomNum(int,int); // Function to generate a random number
    static bool validBranch(int dist, char dir, int r, int c, GridPosition** board); // Function to make sure branches generate right
    static bool noNeighbors(int r, int c, GridPosition** board); // Function to make sure an island has no neighbors
};

#endif