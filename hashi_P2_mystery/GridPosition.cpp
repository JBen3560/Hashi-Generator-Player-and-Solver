#include "GridPosition.h"

// Default constructor
GridPosition::GridPosition() : island('.'){}

// Constructor
GridPosition::GridPosition(char i) : island(i){}

// Set island
void GridPosition::setIsland(char i){
    island = i;
}

// Get island
char GridPosition::getIsland(){
    return island;
}

// Check if island is a bridge
bool GridPosition::isBridge(){
    return (island == '-' || island == '|' || island == '=' || island == 'H');
}

// Overload + operator
GridPosition GridPosition::operator+(int value){
    if (isdigit(island)) {
        island = (island - '0' + value) % 10 + '0';
    }
    return *this;
}

// Overload - operator
GridPosition GridPosition::operator-(int value){
    if (isdigit(island)) {
        island = (island - '0' - value + 10) % 10 + '0';
    }
    return *this;
}

// Prefix increment
GridPosition GridPosition::operator++() {
    if (isdigit(island)) {
        island = (island - '0' + 1) % 10 + '0';
    }
    return *this;
}

// Postfix increment
GridPosition GridPosition::operator++(int) {
    GridPosition temp = *this;
    if (isdigit(island)) {
        island = (island - '0' + 1) % 10 + '0';
    }
    return temp;
}

// Prefix decrement
GridPosition GridPosition::operator--() {
    if (isdigit(island)) {
        island = (island - '0' - 1 + 10) % 10 + '0';
    }
    return *this;
}

// Postfix decrement
GridPosition GridPosition::operator--(int) {
    GridPosition temp = *this;
    if (isdigit(island)) {
        island = (island - '0' - 1 + 10) % 10 + '0';
    }
    return temp;
}