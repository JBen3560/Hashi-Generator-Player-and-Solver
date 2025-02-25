#include "Board.h"

// Main function
int main() {
    // Print instructions
    cout << "\nWelcome to CPSC 1070 Chain Reaction!" << endl;
    cout << "\nThe goal is to connect all of the nodes into a single connected group" << endl;
    cout << "by creating a series of chains between the nodes. The number of chains" << endl;
    cout << "coming off of an node must match the number on that node." << endl;
    cout << "\nEnter the coordinates of the node you would like to connect and a direction. " << endl;
    cout << "If there is already a chain, a second chain will be added. If there are " << endl;
    cout << "already two chains, the chains will be removed." << endl;

    // EXTRA CREDIT - uncomment this and comment all below or something
    /* srand(time(0));
    Board b(true);
    b.runGame(); */

    // Get filename
    cout << "\nPlease enter the name of the file you would like to use: ";
    string filename;
    getline(cin, filename);

    // Run game
    Board b(filename);
    b.runGame();
}