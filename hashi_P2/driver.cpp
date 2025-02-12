#include "Board.h"

// Main function
int main() {
    // Print instructions
    cout << "\nWelcome to CPSC 1070 Hashi!" << endl;
    cout << "\nThe goal is to connect all of the islands into a single connected group" << endl;
    cout << "by creating a series of bridges between the islands. The number of bridges" << endl;
    cout << "coming off of an island must match the number on that island." << endl;
    cout << "\nEnter the coordinates of the island you would like to connect and a direction. " << endl;
    cout << "If there is already a bridge, a second bridge will be added. If there are " << endl;
    cout << "already two bridges, the bridges will be removed." << endl;

    // Set up and run game
    srand(time(0));
    Board b;
    b.setUpGame();
    b.runGame();
}