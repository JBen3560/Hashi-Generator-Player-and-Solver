#include "BoardMaker.h"

// Function to generate a random number
int BoardMaker::randomNum(int l, int h){
    return rand() % (h - l + 1) + l;
}

// Function to check if an island has no neighbors
bool BoardMaker::noNeighbors(int r, int c, GridPosition** board){
    if(r > 0 && board[r-1][c].getIsland() != '.') return false;
    if(r < 9 && board[r+1][c].getIsland() != '.') return false;
    if(c > 0 && board[r][c-1].getIsland() != '.') return false;
    if(c < 9 && board[r][c+1].getIsland() != '.') return false;
    return true;
}

// Function to check if a branch is valid
bool BoardMaker::validBranch(int dist, char dir, int r, int c, GridPosition** board){
    // Make sure dist doesn't go off edge or have neighbors at end
    if(dir == 'n' && (r-dist < 0 || !noNeighbors(r-dist, c, board))) return false;
    if(dir == 'e' && (c+dist > 9 || !noNeighbors(r, c+dist, board))) return false;
    if(dir == 's' && (r+dist > 9 || !noNeighbors(r+dist, c, board))) return false;
    if(dir == 'w' && (c-dist < 0 || !noNeighbors(r, c-dist, board))) return false;

    // Make sure branch path is empty
    for(int i = 1; i <= dist; i++){
        if(dir == 'n' && board[r-i][c].getIsland() != '.') return false;
        if(dir == 'e' && board[r][c+i].getIsland() != '.') return false;
        if(dir == 's' && board[r+i][c].getIsland() != '.') return false;
        if(dir == 'w' && board[r][c-i].getIsland() != '.') return false;
    }
    return true;
}

// Recursive function to create the game board branches
void BoardMaker::setUpBoard(int r, int c, GridPosition** board){
    // Place island
    board[r][c].setIsland('0');
    
    // Make up to four new branches
    char dirs[4] = {'n','e','s','w'};
    for(int i = 0; i < 4; i++){
        // Randomly determine the length of the branch
        int dist = randomNum(2,5);
        
        // If branching and branch is valid, make it
        if(validBranch(dist, dirs[i], r, c, board)){
            // Determine whether the branch is one or two bridges
            char branchType;
            int doubleBranch = randomNum(0,1);
            if(dirs[i] == 'n' || dirs[i] == 's') branchType = (doubleBranch) ? 'H' : '|';
            if(dirs[i] == 'e' || dirs[i] == 'w') branchType = (doubleBranch) ? '=' : '-';
            
            // Place bridges in branch
            for(int j = 1; j < dist; j++){
                if(dirs[i] == 'n') board[r-j][c].setIsland(branchType);
                if(dirs[i] == 'e') board[r][c+j].setIsland(branchType);
                if(dirs[i] == 's') board[r+j][c].setIsland(branchType);
                if(dirs[i] == 'w') board[r][c-j].setIsland(branchType);
            }

            // New Island
            if(dirs[i] == 'n') setUpBoard(r-dist, c, board);
            if(dirs[i] == 'e') setUpBoard(r, c+dist, board);
            if(dirs[i] == 's') setUpBoard(r+dist, c, board);
            if(dirs[i] == 'w') setUpBoard(r, c-dist, board);
        }
    }
}