#ifndef GRIDPOSITION_H
#define GRIDPOSITION_H

#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <cstdlib>
#include <fstream>
using namespace std;

class GridPosition {
private:
    char node;

public:
    GridPosition(); // Constructor
    GridPosition(char); // Constructor
    void setNode(char); // Set node
    char getNode(); // Get node
    bool isChain(); // Check if node is a chain

    GridPosition operator+(int); // Overload + operator
    GridPosition operator-(int); // Overload - operator
    GridPosition operator++(void); // prefix
    GridPosition operator++(int); // postfix
    GridPosition operator--(void); // prefix
    GridPosition operator--(int); // postfix
};

#endif