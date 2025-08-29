#include "Board.h"

// Main function
int main() {
    // Print instructions
    cout << "\nWelcome to CPSC 1070 Chain Reaction!" << endl;
    cout << "\nThe goal is to connect all of the nodes into a single connected group" << endl;
    cout << "by creating a series of chains between the nodes. The number of chains" << endl;
    cout << "coming off of a node must match the number on that node." << endl;
    cout << "\nEnter the coordinates of the node you would like to connect and a direction. " << endl;
    cout << "If there is already a chain, a second chain will be added. If there are " << endl;
    cout << "already two chains, the chains will be removed." << endl;

    cout << "\nGenerate board randomly or from a file? (r/f): ";
    string input = "";
    do{
        getline(cin, input);
        input[0] = tolower(input[0]);
        if(input[0] != 'r' && input[0] != 'f') cout << "Invalid input. Enter 'r' or 'f': ";
    }while(input[0] != 'r' && input[0] != 'f');

    // Create a random board
    if(input[0] == 'r'){
        srand(time(0));
        Board b(true);
        b.runGame(); 
        
    // Read in a board
    }else{
        cout << "\nPlease enter the name of the file you would like to use: ";
        string filename;
        getline(cin, filename);
        Board b(filename);
        b.runGame(); 
    }
}