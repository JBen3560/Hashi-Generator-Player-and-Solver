#include "Board.h"

// Default constructor
Board::Board(){
    board = new GridPosition*[10];
    for(int i = 0; i < 10; i++){
        board[i] = new GridPosition[10];
    }
}

// Destructor
Board::~Board(){
    for(int i = 0; i < 10; i++){
        delete[] board[i];
    }
    delete[] board;
}

// Function to generate a random number
int Board::randomNum(int l, int h){
    return rand() % (h - l + 1) + l;
}

// Function to print the board
void Board::printBoard(){
    char row = 'A';
    cout << "\n    K L M N O P Q R S T" << endl;
    cout << "  ---------------------" << endl;
    for (int r = 0; r < 10; r++){
        cout << row << " | ";
        for (int c = 0; c < 10; c++){
            if((countBranches(r, c) + '0') == board[r][c].getIsland()) cout << "\x1b[32m"; // color green
            cout << board[r][c].getIsland() << " " << "\x1b[0m";
        }
        cout << endl;
        row++;
    }
}

// Function to count the number of branches
int Board::countBranches(int r, int c){
    int count = 0;
    if(r > 0){
        if(board[r-1][c].getIsland() == '|') count++;
        if(board[r-1][c].getIsland() == 'H') count+=2;
    }
    if(r < 9){
        if(board[r+1][c].getIsland() == '|') count++;
        if(board[r+1][c].getIsland() == 'H') count+=2;
    }
    if(c > 0){
        if(board[r][c-1].getIsland() == '-') count++;
        if(board[r][c-1].getIsland() == '=') count+=2;
    }
    if(c < 9){
        if(board[r][c+1].getIsland() == '-') count++;
        if(board[r][c+1].getIsland() == '=') count+=2;
    }
    return count;
}

// Function to check if the game has been won
bool Board::checkWin(){
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(isdigit(board[r][c].getIsland())){
                if((countBranches(r, c) + '0') != board[r][c].getIsland()) return false;
            }
        }
    }
    return true;
}

// Function to check if a branch is valid
bool Board::validBranch(int dist, char dir, int r, int c){
    // Make sure dist doesn't go off edge or have neighbors at end
    if(dir == 'n' && (r-dist < 0 || !noNeighbors(r-dist, c))) return false;
    if(dir == 'e' && (c+dist > 9 || !noNeighbors(r, c+dist))) return false;
    if(dir == 's' && (r+dist > 9 || !noNeighbors(r+dist, c))) return false;
    if(dir == 'w' && (c-dist < 0 || !noNeighbors(r, c-dist))) return false;

    // Make sure branch path is empty
    for(int i = 1; i <= dist; i++){
        if(dir == 'n' && board[r-i][c].getIsland() != '.') return false;
        if(dir == 'e' && board[r][c+i].getIsland() != '.') return false;
        if(dir == 's' && board[r+i][c].getIsland() != '.') return false;
        if(dir == 'w' && board[r][c-i].getIsland() != '.') return false;
    }
    return true;
}

// Function to check if an island has no neighbors
bool Board::noNeighbors(int r, int c){
    if(r > 0 && board[r-1][c].getIsland() != '.') return false;
    if(r < 9 && board[r+1][c].getIsland() != '.') return false;
    if(c > 0 && board[r][c-1].getIsland() != '.') return false;
    if(c < 9 && board[r][c+1].getIsland() != '.') return false;
    return true;
}

// Function to check if a bridge will be valid
bool Board::validBridge(string input){
    int r = input[0] - 'A';
    int c = input[1] - 'K';
    char dir = input[3];
    do{
        // Move in direction
        if(dir == 'n') r--;
        else if(dir == 'e') c++;
        else if(dir == 's') r++;
        else c--;

        // Check if off board
        if(r < 0 || r > 9 || c < 0 || c > 9) return false;
        
        // Check if path is blocked
        if(board[r][c].getIsland() != '.' && !isdigit(board[r][c].getIsland())){
            if(board[r][c].getIsland() == '|' && (dir == 'e' || dir == 'w')) return false;
            if(board[r][c].getIsland() == '-' && (dir == 'n' || dir == 's')) return false;
            if(board[r][c].getIsland() == 'H' && (dir == 'e' || dir == 'w')) return false;
            if(board[r][c].getIsland() == '=' && (dir == 'n' || dir == 's')) return false;
        }
    }while(!isdigit(board[r][c].getIsland()));
    return true;
}

// Recursive function to create the game board branches
void Board::createBranch(int r, int c){
    // Place island
    board[r][c].setIsland('0');
    
    // Make up to four new branches
    char dirs[4] = {'n','e','s','w'};
    for(int i = 0; i < 4; i++){
        // Randomly determine the length of the branch
        int dist = randomNum(2,5);
        
        // If branching and branch is valid, make it
        if(randomNum(1,2) && validBranch(dist, dirs[i], r, c)){
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
            if(dirs[i] == 'n') createBranch(r-dist, c);
            if(dirs[i] == 'e') createBranch(r, c+dist);
            if(dirs[i] == 's') createBranch(r+dist, c);
            if(dirs[i] == 'w') createBranch(r, c-dist);
        }
    }
}

// Function to set up the game
void Board::setUpGame(){
    // Initialize board
    createBranch(randomNum(4,5), randomNum(4,5));
    
    // Set island numbers
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(board[r][c].getIsland() == '0'){
                if(r > 0){
                    if(board[r-1][c].getIsland() == '|') ++board[r][c];
                    if(board[r-1][c].getIsland() == 'H') board[r][c] = board[r][c] + 2;
                }
                if(r < 9){
                    if(board[r+1][c].getIsland() == '|') ++board[r][c];
                    if(board[r+1][c].getIsland() == 'H') board[r][c] = board[r][c] + 2;
                }
                if(c > 0){
                    if(board[r][c-1].getIsland() == '-') ++board[r][c];
                    if(board[r][c-1].getIsland() == '=') board[r][c] = board[r][c] + 2;
                }
                if(c < 9){
                    if(board[r][c+1].getIsland() == '-') ++board[r][c];
                    if(board[r][c+1].getIsland() == '=') board[r][c] = board[r][c] + 2;
                }
            }
        }
    }

    // Remove branches
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(board[r][c].isBridge()){
                board[r][c].setIsland('.');
            }
        }
    }
}

// Function to run the game
void Board::runGame(){
    do{
        // Print board
        printBoard();
        
        // Input variables
        string input = "";

        // Input
        cout << "\nEnter a row, a column, a space, and a cardinal direction (e.g. AK n): ";
        getline(cin, input);
        for(int i = 0; i < 2; i++) if(isalpha(input[i])) input[i] = toupper(input[i]);

        // Validate input
        bool wrongLength = input.length() != 4;
        bool wrongPos = (input[0] < 'A' || input[0] > 'J') || (input[1] < 'K' || input[1] > 'T');
        bool wrongDir = (input[2] != ' ') || (input[3] != 'n' && input[3] != 'e' && input[3] != 's' && input[3] != 'w');
        bool noIsland = wrongLength || wrongPos || !(isdigit(board[input[0] - 'A'][input[1] - 'K'].getIsland()));
        bool bridgeIsInvalid = wrongLength || wrongPos || wrongDir || !validBridge(input);
        while(wrongLength || wrongPos || wrongDir || noIsland || bridgeIsInvalid){
            if(wrongLength) cout << "\nInvalid input. Too many or too few characters." << endl;
            else if(wrongPos) cout << "\nInvalid input. Row must be A-J and column must be K-T." << endl;
            else if(wrongDir) cout << "\nInvalid input. Direction must be n, e, s, or w and there must be a space between the column and direction." << endl;
            else if(noIsland) cout << "\nInvalid input. There is no island at that location." << endl;
            else if(bridgeIsInvalid) cout << "\nInvalid input. That path is blocked or goes off the board." << endl;
            else cout << "\nInvalid input." << endl;

            // Get new input
            cout << "Enter a row, a column, a space, and a cardinal direction (e.g. AK n): ";
            getline(cin, input);
            for(int i = 0; i < 2; i++) if(isalpha(input[i])) input[i] = toupper(input[i]);
            wrongLength = input.length() != 4;
            wrongPos = (input[0] < 'A' || input[0] > 'J') || (input[1] < 'K' || input[1] > 'T');
            wrongDir = (input[2] != ' ') || (input[3] != 'n' && input[3] != 'e' && input[3] != 's' && input[3] != 'w');
            noIsland = wrongLength || wrongPos || !(isdigit(board[input[0] - 'A'][input[1] - 'K'].getIsland()));
            bridgeIsInvalid = wrongLength || wrongPos || wrongDir || !validBridge(input);
        }

        // Place bridges
        int r = input[0] - 'A';
        int c = input[1] - 'K';
        char dir = input[3];
        do{
            // Move in direction
            if(dir == 'n') r--;
            else if(dir == 'e') c++;
            else if(dir == 's') r++;
            else c--;

            // Place bridge
            if(!isdigit(board[r][c].getIsland())){
                if(dir == 'n' || dir == 's'){
                    if(board[r][c].getIsland() == '.') board[r][c].setIsland('|');
                    else if(board[r][c].getIsland() == '|') board[r][c].setIsland('H');
                    else board[r][c].setIsland('.');
                }
                else{
                    if(board[r][c].getIsland() == '.') board[r][c].setIsland('-');
                    else if(board[r][c].getIsland() == '-') board[r][c].setIsland('=');
                    else board[r][c].setIsland('.');
                }
            }
        }while(!isdigit(board[r][c].getIsland()));        
    }while(!checkWin());
    
    printBoard();
    cout << "\nCongratulations! You have connected all the islands!" << endl;
    cout << endl;
}