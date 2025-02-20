#include "Board.h"
#include "BoardMaker.h"

// Parameterized constructor
Board::Board(string filename){
    // Open the file
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        exit(1);
    }

    // Create the board
    board = new GridPosition*[10];
    for(int i = 0; i < 10; i++){
        board[i] = new GridPosition[10];
    }

    // Read the file
    string line;
    int r = 0;
    while (getline(file, line)) {
        for(int c = 0; c < 10; c++) board[r][c].setIsland(line[c]);
        r++;
    }

    file.close(); // Close the file
    
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

// Extra credit constructor
Board::Board(){
    // Create the board
    board = new GridPosition*[10];
    for(int i = 0; i < 10; i++){
        board[i] = new GridPosition[10];
    }

    // Set up the board
    int r = BoardMaker::randomNum(4, 5);
    int c = BoardMaker::randomNum(4, 5);
    BoardMaker::setUpBoard(r, c, board);

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

// Destructor
Board::~Board(){
    for(int i = 0; i < 10; i++){
        delete[] board[i];
    }
    delete[] board;
}

// Function to print the board
void Board::printBoard(){
    char row = 'A';
    cout << "\n    K L M N O P Q R S T" << endl;
    cout << "  ---------------------" << endl;
    for (int r = 0; r < 10; r++){
        cout << row << " | ";
        for (int c = 0; c < 10; c++){
            cout << board[r][c].getIsland() << " ";
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
    }while(!isdigit(board[r][c].getIsland())); // Go until you hit an island
    return true;
}

// Place bridges
void Board::placeBridges(string input){
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

            // Get new input and validate
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
        placeBridges(input);

    }while(!checkWin());
    
    printBoard();
    cout << "\nCongratulations! You have connected all the islands!" << endl;
    cout << endl;
}