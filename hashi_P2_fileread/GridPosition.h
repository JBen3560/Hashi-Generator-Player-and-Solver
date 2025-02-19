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
    char island;

public:
    GridPosition(); // Constructor
    GridPosition(char); // Constructor
    void setIsland(char); // Set island
    char getIsland(); // Get island
    bool isBridge(); // Check if island is a bridge

    GridPosition operator+(int); // Overload + operator
    GridPosition operator-(int); // Overload - operator
    GridPosition operator++(void); // prefix
    GridPosition operator++(int); // postfix
    GridPosition operator--(void); // prefix
    GridPosition operator--(int); // postfix
};

#endif