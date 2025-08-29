#include "Board.h"
#include "BoardMaker.h"
#include "BoardSolver.h"

// TODO: Fix recursion causing multiple congrats messages by having runGame
// just return the board and printing it the final time in the driver.

// Default constructor
Board::Board(){
    // Create the board
    board = new GridPosition*[10];
    for(int i = 0; i < 10; i++){
        board[i] = new GridPosition[10];
    }
}

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
        for(int c = 0; c < 10; c++) board[r][c].setNode(line[c]);
        r++;
    }

    file.close(); // Close the file
    
    /* // Set node numbers
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(board[r][c].getNode() == '0'){
                if(r > 0){
                    if(board[r-1][c].getNode() == '|') ++board[r][c];
                    if(board[r-1][c].getNode() == 'H') board[r][c] = board[r][c] + 2;
                }
                if(r < 9){
                    if(board[r+1][c].getNode() == '|') ++board[r][c];
                    if(board[r+1][c].getNode() == 'H') board[r][c] = board[r][c] + 2;
                }
                if(c > 0){
                    if(board[r][c-1].getNode() == '-') ++board[r][c];
                    if(board[r][c-1].getNode() == '=') board[r][c] = board[r][c] + 2;
                }
                if(c < 9){
                    if(board[r][c+1].getNode() == '-') ++board[r][c];
                    if(board[r][c+1].getNode() == '=') board[r][c] = board[r][c] + 2;
                }
            }
        }
    }

    // Remove branches
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(board[r][c].isChain()){
                board[r][c].setNode('.');
            }
        }
    } */
}

// Extra credit constructor
Board::Board(bool ec){
    // Create the board
    board = new GridPosition*[10];
    for(int i = 0; i < 10; i++){
        board[i] = new GridPosition[10];
    }

    // Set up the board
    int r = BoardMaker::randomNum(4, 5);
    int c = BoardMaker::randomNum(4, 5);
    BoardMaker::setUpBoard(r, c, board);

    // Set node numbers
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(board[r][c].getNode() == '0'){
                if(r > 0){
                    if(board[r-1][c].getNode() == '|') ++board[r][c];
                    if(board[r-1][c].getNode() == 'H') board[r][c] = board[r][c] + 2;
                }
                if(r < 9){
                    if(board[r+1][c].getNode() == '|') ++board[r][c];
                    if(board[r+1][c].getNode() == 'H') board[r][c] = board[r][c] + 2;
                }
                if(c > 0){
                    if(board[r][c-1].getNode() == '-') ++board[r][c];
                    if(board[r][c-1].getNode() == '=') board[r][c] = board[r][c] + 2;
                }
                if(c < 9){
                    if(board[r][c+1].getNode() == '-') ++board[r][c];
                    if(board[r][c+1].getNode() == '=') board[r][c] = board[r][c] + 2;
                }
            }
        }
    }

    // Remove branches
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(board[r][c].isChain()){
                board[r][c].setNode('.');
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
            if((countChains(r, c) + '0') == board[r][c].getNode()) cout << "\x1b[32m"; // color green
                cout << board[r][c].getNode() << " " << "\x1b[0m";
        }
        cout << endl;
        row++;
    }
}

// Function to count the number of chains on a node
int Board::countChains(int r, int c){
    int count = 0;
    if(r > 0){
        if(board[r-1][c].getNode() == '|') count++;
        if(board[r-1][c].getNode() == 'H') count+=2;
    }
    if(r < 9){
        if(board[r+1][c].getNode() == '|') count++;
        if(board[r+1][c].getNode() == 'H') count+=2;
    }
    if(c > 0){
        if(board[r][c-1].getNode() == '-') count++;
        if(board[r][c-1].getNode() == '=') count+=2;
    }
    if(c < 9){
        if(board[r][c+1].getNode() == '-') count++;
        if(board[r][c+1].getNode() == '=') count+=2;
    }
    return count;
}

// Function to check if the game has been won
bool Board::checkWin(){
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(isdigit(board[r][c].getNode())){
                if((countChains(r, c) + '0') != board[r][c].getNode()) return false;
            }
        }
    }
    return true;
}

// Function to check if a chain will be valid
bool Board::validChain(string input){
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
        if(board[r][c].getNode() != '.' && !isdigit(board[r][c].getNode())){
            if(board[r][c].getNode() == '|' && (dir == 'e' || dir == 'w')) return false;
            if(board[r][c].getNode() == '-' && (dir == 'n' || dir == 's')) return false;
            if(board[r][c].getNode() == 'H' && (dir == 'e' || dir == 'w')) return false;
            if(board[r][c].getNode() == '=' && (dir == 'n' || dir == 's')) return false;
        }
    }while(!isdigit(board[r][c].getNode())); // Go until you hit an node
    return true;
}

// Place chains
void Board::placeChains(string input){
    int r = input[0] - 'A';
    int c = input[1] - 'K';
    char dir = input[3];
    do{
        // Move in direction
        if(dir == 'n') r--;
        else if(dir == 'e') c++;
        else if(dir == 's') r++;
        else c--;

        // Place chain
        if(!isdigit(board[r][c].getNode())){
            if(dir == 'n' || dir == 's'){
                if(board[r][c].getNode() == '.') board[r][c].setNode('|');
                else if(board[r][c].getNode() == '|') board[r][c].setNode('H');
                else board[r][c].setNode('.');
            }
            else{
                if(board[r][c].getNode() == '.') board[r][c].setNode('-');
                else if(board[r][c].getNode() == '-') board[r][c].setNode('=');
                else board[r][c].setNode('.');
            }
        }
    }while(!isdigit(board[r][c].getNode())); 
}

// Function to run the game
void Board::runGame(){
    // Check if playing manually or automatically
    printBoard();
    cout << "\nDo you want to play manually or automatically? (m/a): ";
    string input = "";
    do{
        getline(cin, input);
        input[0] = tolower(input[0]);
        if(input[0] != 'm' && input[0] != 'a') cout << "Invalid input. Enter 'm' or 'a': ";
    }while(input[0] != 'm' && input[0] != 'a');

    // Automatic
    if(input[0] == 'a'){
        pair<GridPosition**,bool> pair = BoardSolver::solve(board);
        board = pair.first;
        if(!pair.second) runGame();

    // Manual
    }else if(input[0] == 'm'){
        do{
            // Print board
            printBoard();

            // Input
            input = "";
            cout << "\nEnter a row, column, and cardinal direction (e.g. AK n), or 'z' to change mode: ";
            getline(cin, input);
            for(int i = 0; i < 2; i++) if(isalpha(input[i])) input[i] = toupper(input[i]);

            // Change to automatic
            if(input[0] == 'Z'){
                runGame();
                break;
            }

            // Validate input
            bool wrongLength = input.length() != 4;
            bool wrongPos = (input[0] < 'A' || input[0] > 'J') || (input[1] < 'K' || input[1] > 'T');
            bool wrongDir = (input[2] != ' ') || (input[3] != 'n' && input[3] != 'e' && input[3] != 's' && input[3] != 'w');
            bool noNode = wrongLength || wrongPos || !(isdigit(board[input[0] - 'A'][input[1] - 'K'].getNode()));
            bool chainIsInvalid = wrongLength || wrongPos || wrongDir || !validChain(input);
            while(wrongLength || wrongPos || wrongDir || noNode || chainIsInvalid){
                if(wrongLength) cout << "\nInvalid input. Too many or too few characters." << endl;
                else if(wrongPos) cout << "\nInvalid input. Row must be A-J and column must be K-T." << endl;
                else if(wrongDir) cout << "\nInvalid input. Direction must be n, e, s, or w and there must be a space between the column and direction." << endl;
                else if(noNode) cout << "\nInvalid input. There is no node at that location." << endl;
                else if(chainIsInvalid) cout << "\nInvalid input. That path is blocked or goes off the board." << endl;
                else cout << "\nInvalid input." << endl;

                // Get new input and validate
                cout << "Enter a row, a column, a space, and a cardinal direction (e.g. AK n): ";
                getline(cin, input);
                for(int i = 0; i < 2; i++) if(isalpha(input[i])) input[i] = toupper(input[i]);
                wrongLength = input.length() != 4;
                wrongPos = (input[0] < 'A' || input[0] > 'J') || (input[1] < 'K' || input[1] > 'T');
                wrongDir = (input[2] != ' ') || (input[3] != 'n' && input[3] != 'e' && input[3] != 's' && input[3] != 'w');
                noNode = wrongLength || wrongPos || !(isdigit(board[input[0] - 'A'][input[1] - 'K'].getNode()));
                chainIsInvalid = wrongLength || wrongPos || wrongDir || !validChain(input);
            }

            // Place chains
            placeChains(input);

        }while(!checkWin());

        

    // Invalid input
    }else{
        cout << "\nInvalid input. Quitting.\n" << endl;
        return;
    }

    printBoard();
    cout << "\nCongratulations! You have connected all the nodes!" << endl;
    cout << endl;
}
