#include "BoardSolver.h"

GridPosition** BoardSolver::wboard = nullptr;

// Function to generate a random number
pair<GridPosition**,bool> BoardSolver::solve(GridPosition** board){
    wboard = board;
    bool solved;
    int count = 0;

    // Loop until the puzzle is solved
    do{
        solved = true;
        count++;
        
        // At each node, make all determinable connections
        for(int r = 0; r < 10; r++){
            for(int c = 0; c < 10; c++){
                if(isdigit(board[r][c].getNode())){
                    // Node setup
                    int currNode = wboard[r][c].getNode() - '0';
                    int nodeChains = 0;
                    int neighborSum = 0;
                    vector<int> adjChains = getNodeAdjChains(r,c);
                    vector<int> neighbors = getNodeNeighbors(r,c,adjChains);
                    for(int i = 0; i < 4; i++) nodeChains += adjChains[i];
                    for(int i = 0; i < 4; i++) if(neighbors[i] > 0) neighborSum += neighbors[i];

                    // Check if the node is solved
                    if(!(currNode == nodeChains)){
                        // Puzzle not solved this loop
                        solved = false;

                        // Finish a node if it has one possible solution
                        if((currNode - nodeChains) == neighborSum){
                            for(int i = 0; i < 4; i++){
                                for(int j = 0; j < neighbors[i]; j++){
                                    switch(i){
                                        case 0: placeChains(r,c,'n'); break;
                                        case 1: placeChains(r,c,'e'); break;
                                        case 2: placeChains(r,c,'s'); break;
                                        case 3: placeChains(r,c,'w');
                                    }
                                }
                            }

                        // Make the forced chains that are in every solve permutation
                        }else{
                            for(int i = 0; i < 4; i++){
                                if((neighbors[i] > 0) && ((currNode - nodeChains) > (neighborSum - neighbors[i]))){
                                    switch(i){
                                        case 0: placeChains(r,c,'n'); break;
                                        case 1: placeChains(r,c,'e'); break;
                                        case 2: placeChains(r,c,'s'); break;
                                        case 3: placeChains(r,c,'w');
                                    }
                                }
                            }
                        }

                        /* cout << "\nNode: " << wboard[r][c].getNode();
                        cout << "\nNode Sum: " << nodeChains;
                        for(int i = 0; i < 4; i++) cout << "\nChain " << i+1 << ": " << adjChains[i];
                        cout << "\nNeighbor Sum: " << neighborSum;
                        for(int i = 0; i < 4; i++) cout << "\nNeighbor " << i+1 << ": " << neighbors[i];
                        cout << endl; */
                    }
                }
            }
        }

    }while(!solved && count < 100);

    bool success;
    if(count < 100){
        success = true;
        cout << "\nSolved! Required Passes: " << count << endl;
    }
    else{
        success = false;
        cout << "\nCould not solve." << endl;
    } 
    
    return {wboard,success};
}

// Get list of adjacent chains
vector<int> BoardSolver::getNodeAdjChains(int r, int c){
    vector<int> adjChains(4, 0);

    // North
    if(r > 0){
        if(wboard[r-1][c].getNode() == '|') adjChains[0] = 1;
        if(wboard[r-1][c].getNode() == 'H') adjChains[0] = 2;
    }
    // East
    if(c < 9){
        if(wboard[r][c+1].getNode() == '-') adjChains[1] = 1;
        if(wboard[r][c+1].getNode() == '=') adjChains[1] = 2;
    }
    // South
    if(r < 9){
        if(wboard[r+1][c].getNode() == '|') adjChains[2] = 1;
        if(wboard[r+1][c].getNode() == 'H') adjChains[2] = 2;
    }
    // West
    if(c > 0){
        if(wboard[r][c-1].getNode() == '-') adjChains[3] = 1;
        if(wboard[r][c-1].getNode() == '=') adjChains[3] = 2;
    }

    return adjChains;
}

// Get list of functional neighbor values
vector<int> BoardSolver::getNodeNeighbors(int r, int c, vector<int> adjChains){
    vector<int> neighbors(4, -1);

    // North
    if(r > 0) neighbors[0] = findNeighborValue(r, c, 'n');
    // East
    if(c < 9) neighbors[1] = findNeighborValue(r, c, 'e');
    // South
    if(r < 9) neighbors[2] = findNeighborValue(r, c, 's');
    // West
    if(c > 0) neighbors[3] = findNeighborValue(r, c, 'w');

    // Account for existing chains limiting options
    for(int i = 0; i < 4; i++) if(neighbors[i] == 2) neighbors[i] -= adjChains[i];

    return neighbors;
}

// Find the neighbor value in a specific direction
int BoardSolver::findNeighborValue(int r, int c, char dir){
    do{
        // Move in direction
        if(dir == 'n') r--;
        else if(dir == 'e') c++;
        else if(dir == 's') r++;
        else c--;

        // Check if off board
        if(r < 0 || r > 9 || c < 0 || c > 9) return -1;
        
        // Check if path is blocked
        if(wboard[r][c].getNode() != '.' && !isdigit(wboard[r][c].getNode())){
            if(wboard[r][c].getNode() == '|' && (dir == 'e' || dir == 'w')) return -1;
            if(wboard[r][c].getNode() == '-' && (dir == 'n' || dir == 's')) return -1;
            if(wboard[r][c].getNode() == 'H' && (dir == 'e' || dir == 'w')) return -1;
            if(wboard[r][c].getNode() == '=' && (dir == 'n' || dir == 's')) return -1;
        }
    }while(!isdigit(wboard[r][c].getNode())); // Go until you hit an node

    // Return how many chains can be accepted in this direction
    int functionalValue = wboard[r][c].getNode() - '0';
    vector<int> adjChains = getNodeAdjChains(r, c);
    for(int i = 0; i < 4; i++) functionalValue -= adjChains[i];

    return ((functionalValue > 2) ? 2 : functionalValue);
}

// Place chains on board
void BoardSolver::placeChains(int r, int c, char dir){
    do{
        // Move in direction
        if(dir == 'n') r--;
        else if(dir == 'e') c++;
        else if(dir == 's') r++;
        else c--;

        // Place chain
        if(!isdigit(wboard[r][c].getNode())){
            if(dir == 'n' || dir == 's'){
                if(wboard[r][c].getNode() == '.') wboard[r][c].setNode('|');
                else if(wboard[r][c].getNode() == '|') wboard[r][c].setNode('H');
                else wboard[r][c].setNode('.');
            }
            else{
                if(wboard[r][c].getNode() == '.') wboard[r][c].setNode('-');
                else if(wboard[r][c].getNode() == '-') wboard[r][c].setNode('=');
                else wboard[r][c].setNode('.');
            }
        }
    }while(!isdigit(wboard[r][c].getNode())); // Place until you reach a node
}