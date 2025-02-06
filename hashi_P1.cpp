#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <cstdlib>
using namespace std;

// Function to generate a random number
int randomNum(int l, int h){
    return rand() % (h - l + 1) + l;
}

// Function to print the board
void printBoard(char board[10][10]){
    char row = 'A';
    cout << "\n    K L M N O P Q R S T" << endl;
    cout << "  ---------------------" << endl;
    for (int i = 0; i < 10; i++){
        cout << row << " | ";
        for (int j = 0; j < 10; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
        row++;
    }
}

bool noNeighbors(int r, int c, char (&board)[10][10]){
    if(r > 0 && board[r-1][c] != '.') return false;
    if(r < 9 && board[r+1][c] != '.') return false;
    if(c > 0 && board[r][c-1] != '.') return false;
    if(c < 9 && board[r][c+1] != '.') return false;
    return true;
}

int countBranches(int r, int c, char (&board)[10][10]){
    int count = 0;
    if(r > 0){
        if(board[r-1][c] == '|') count++;
        if(board[r-1][c] == 'H') count += 2;
    }
    if(r < 9){
        if(board[r+1][c] == '|') count++;
        if(board[r+1][c] == 'H') count += 2;
    }
    if(c > 0){
        if(board[r][c-1] == '-') count++;
        if(board[r][c-1] == '=') count += 2;
    }
    if(c < 9){
        if(board[r][c+1] == '-') count++;
        if(board[r][c+1] == '=') count += 2;
    }
    return count;
}

bool validBranch(int dist, char dir, int r, int c, char (&board)[10][10]){
    // Make sure dist doesn't go off edge or have neighbors at end
    if(dir == 'n' && (r-dist < 0 || !noNeighbors(r-dist, c, board))) return false;
    if(dir == 'e' && (c+dist > 9 || !noNeighbors(r, c+dist, board))) return false;
    if(dir == 's' && (r+dist > 9 || !noNeighbors(r+dist, c, board))) return false;
    if(dir == 'w' && (c-dist < 0 || !noNeighbors(r, c-dist, board))) return false;

    // Make sure branch path is empty
    for(int i = 1; i <= dist; i++){
        if(dir == 'n' && board[r-i][c] != '.') return false;
        if(dir == 'e' && board[r][c+i] != '.') return false;
        if(dir == 's' && board[r+i][c] != '.') return false;
        if(dir == 'w' && board[r][c-i] != '.') return false;
    }
    return true;
}

void setUpBoard(int r, int c, char (&board)[10][10], int &isles){
    // Place island
    board[r][c] = '0';
    isles++;
    
    // Make new branches
    char dirs[4] = {'n','e','s','w'};
    for(int i = 0; i < 4; i++){
        int branching = randomNum(0,1);
        int dist = randomNum(2,4);
        
        // If branching and branch is valid, make it
        if(branching && validBranch(dist, dirs[i], r, c, board)){
            // Determine whether the branch is double
            char branchType;
            int doubleBranch = randomNum(0,1);
            if(dirs[i] == 'n' || dirs[i] == 's') branchType = (doubleBranch) ? 'H' : '|';
            if(dirs[i] == 'e' || dirs[i] == 'w') branchType = (doubleBranch) ? '=' : '-';
            
            // Place branch
            for(int j = 1; j < dist; j++){
                if(dirs[i] == 'n') board[r-j][c] = branchType;
                if(dirs[i] == 'e') board[r][c+j] = branchType;
                if(dirs[i] == 's') board[r+j][c] = branchType;
                if(dirs[i] == 'w') board[r][c-j] = branchType;
            }

            // New Island
            if(dirs[i] == 'n'){
                setUpBoard(r-dist, c, board, isles);
            }
            if(dirs[i] == 'e'){
                setUpBoard(r, c+dist, board, isles);
            }
            if(dirs[i] == 's'){
                setUpBoard(r+dist, c, board, isles);
            }
            if(dirs[i] == 'w'){
                setUpBoard(r, c-dist, board, isles);
            }
        }
    }
}

bool checkWin(char (&board)[10][10]){
    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(board[r][c] >= '1' && board[r][c] <= '8'){
                int count = countBranches(r, c, board);
                if(count + '0' != board[r][c]){
                    return false;
                }
            }
        }
    }
    return true;
}

string getInput(char (&board)[10][10]){
    // Get input
    string input;
    getline(cin, input);
    for(int i = 0; i < 2; i++) if(isalpha(input[i])) input[i] = toupper(input[i]);

    // Validate input
    while(input.length() != 2 || (input[0] < 'A' || input[0] > 'J') || (input[1] < 'K' || input[1] > 'T') || !(board[input[0] - 'A'][input[1] - 'K'] >= '1' && board[input[0] - 'A'][input[1] - 'K'] <= '8')){
        // Wrong length
        if(input.length() != 2){
            cout << "Invalid input. Enter two characters: ";
        }
        // Wrong characters
        else if((input[0] < 'A' || input[0] > 'J') || (input[1] < 'K' || input[1] > 'T')){
            cout << "Invalid input. Enter a letter from A to J and a letter from K to T: ";
        }
        // No island at input
        else if(!(board[input[0] - 'A'][input[1] - 'K'] >= '1' && board[input[0] - 'A'][input[1] - 'K'] <= '8')){
            cout << "Invalid input. There is no island at " << input << ". Enter a new coordinate: ";
        }

        // Get new input
        getline(cin, input);
        for(int i = 0; i < 2; i++) if(isalpha(input[i])) input[i] = toupper(input[i]);
    }
    return input;
}

bool validBridge(string input1, string input2, char (&board)[10][10]){
    // Get coordinates
    int highRow = (input1[0] > input2[0]) ? input1[0] - 'A' : input2[0] - 'A';
    int lowRow = (input1[0] < input2[0]) ? input1[0] - 'A' : input2[0] - 'A';
    int highCol = (input1[1] > input2[1]) ? input1[1] - 'K' : input2[1] - 'K';
    int lowCol = (input1[1] < input2[1]) ? input1[1] - 'K' : input2[1] - 'K';
    
    // Make sure path is clear
    if(highRow == lowRow){
        for(int c = lowCol+1; c < highCol; c++){
            if(board[lowRow][c] != '.' && board[lowRow][c] != '-' && board[lowRow][c] != '=') return false;
        }
    }
    else if(highCol == lowCol){
        for(int r = lowRow+1; r < highRow; r++){
            if(board[r][lowCol] != '.' && board[r][lowCol] != '|' && board[r][lowCol] != 'H') return false;
        }
    }
    return true;
}

void placeBridges(string input1, string input2, char (&board)[10][10]){
    // Get coordinates
    int highRow = (input1[0] > input2[0]) ? input1[0] - 'A' : input2[0] - 'A';
    int lowRow = (input1[0] < input2[0]) ? input1[0] - 'A' : input2[0] - 'A';
    int highCol = (input1[1] > input2[1]) ? input1[1] - 'K' : input2[1] - 'K';
    int lowCol = (input1[1] < input2[1]) ? input1[1] - 'K' : input2[1] - 'K';
    
    // Place bridges
    if(highRow == lowRow){
        for(int c = lowCol+1; c < highCol; c++){
            if(board[lowRow][c] == '.') board[lowRow][c] = '-';
            else if(board[lowRow][c] == '-') board[lowRow][c] = '=';
            else board[lowRow][c] = '.';
        }
    }
    else if(highCol == lowCol){
        for(int r = lowRow+1; r < highRow; r++){
            if(board[r][lowCol] == '.') board[r][lowCol] = '|';
            else if(board[r][lowCol] == '|') board[r][lowCol] = 'H';
            else board[r][lowCol] = '.';
        }
    }
}

void runGame(){
    // --------------------------- Setup ---------------------------
    // Initialize
    char board[10][10];
    int islandNum;
    do{
        islandNum = 0;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                board[i][j] = '.';
            }
        }
        setUpBoard(randomNum(4,5), randomNum(4,5), board, islandNum);
    }while(islandNum < 10);

    // Set island numbers
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(board[i][j] == '0'){
                board[i][j] = countBranches(i, j, board) + '0';
            }
        }
    }

    // Remove branches
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(board[i][j] < '1' || board[i][j] > '8'){
                board[i][j] = '.';
            }
        }
    }

    // --------------------------- Play ---------------------------
    // Print instructions
    cout << "\nWelcome to CPSC 1070 Hashi!" << endl;
    cout << "\nThe goal is to connect all of the islands into a single connected group" << endl;
    cout << "by creating a series of bridges between the islands. The number of bridges" << endl;
    cout << "coming off of an island must match the number on that island.\n" << endl;
    cout << "Enter the coordinates of the islands you would like to connect. If there is" << endl;
    cout << "already a bridge, a second bridge will be added. If there are already two" << endl;
    cout << "bridges, the bridges will be removed." << endl;

    // Play game
    do{
        // Print board
        printBoard(board);
        
        // Get input
        string input1 = "";
        string input2 = "";
        cout << "\n---------- Enter Two Islands ----------" << endl;
        cout << "Enter the row and column of the first island you want to connect (e.g. AK): ";
        input1 = getInput(board);
        cout << "\nEnter the row and column of the second island you want to connect (e.g. AT): ";
        input2 = getInput(board);
        
        // Validate input
        while((input1[0] != input2[0] && input1[1] != input2[1]) || (input1[0] == input2[0] && input1[1] == input2[1]) || !validBridge(input1, input2, board)){
            cout << "\n---------- Enter Two Islands ----------" << endl;

            // Same island
            if(input1[0] == input2[0] && input1[1] == input2[1]){
                cout << "You entered the same island twice. Try again.";
            }
            // Not in same row or column
            else if(input1[0] != input2[0] && input1[1] != input2[1]){
                cout << "You entered two islands that are not in the same row or column. Try again.";
            }
            // Path not clear
            else if(!validBridge(input1, input2, board)){
                cout << "The path between the two islands is not empty. Try again.";
            }
            
            // Get new input
            cout << "\nEnter the row and column of the first island you want to connect without a space: ";
            input1 = getInput(board);
            cout << "\nEnter the row and column of the second island you want to connect without a space: ";
            input2 = getInput(board);
        }

        // Place bridges
        placeBridges(input1, input2, board);
    }while(!checkWin(board));

    cout << "\nCongratulations! You have connected all the islands!" << endl;
    printBoard(board);
    cout << endl;
}

// Main function
int main() {
    srand(time(0));
    runGame();
}