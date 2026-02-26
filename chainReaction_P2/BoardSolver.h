#ifndef BOARDSOLVER_H
#define BOARDSOLVER_H

#include "Board.h"
#include <vector>
using namespace std;

class BoardSolver {
private:
    static GridPosition** wboard; // Working board
    static vector<int> getNodeAdjChains(int r, int c); // Get list of adjacent chains
    static vector<int> getNodeNeighbors(int r, int c, vector<int> adjChains); // Get list of functional neighbor values
    static vector<int> getNodeValues(int r, int c); // Get list of neighbor values
    static int findNeighborValue(int r, int c, char dir); // Find neighbor value in a specific direction
    static void placeChains(int r, int c, char dir); // Place chains on board

public:
    static pair<GridPosition**,bool> solve(GridPosition** board); // Solve the board and return the solution
};

#endif