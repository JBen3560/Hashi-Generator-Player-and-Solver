#include "GridPosition.h"

// Default constructor
GridPosition::GridPosition() : node('.'){}

// Constructor
GridPosition::GridPosition(char i) : node(i){}

// Set node
void GridPosition::setNode(char i){
    node = i;
}

// Get node
char GridPosition::getNode(){
    return node;
}

// Check if node is a bridge
bool GridPosition::isChain(){
    return (node == '-' || node == '|' || node == '=' || node == 'H');
}

// Overload + operator
GridPosition GridPosition::operator+(int value){
    GridPosition newIsle = *this;
    if (isdigit(node)) {
        newIsle.node = (node - '0' + value) % 10 + '0';
    }
    return newIsle;
}

// Overload - operator
GridPosition GridPosition::operator-(int value){
    GridPosition newIsle = *this;
    if (isdigit(node)) {
        newIsle.node = (node - '0' - value + 10) % 10 + '0';
    }
    return newIsle;
}

// Prefix increment
GridPosition GridPosition::operator++() {
    if (isdigit(node)) {
        node = (node - '0' + 1) % 10 + '0';
    }
    return *this;
}

// Postfix increment
GridPosition GridPosition::operator++(int) {
    GridPosition temp = *this;
    if (isdigit(node)) {
        node = (node - '0' + 1) % 10 + '0';
    }
    return temp;
}

// Prefix decrement
GridPosition GridPosition::operator--() {
    if (isdigit(node)) {
        node = (node - '0' - 1 + 10) % 10 + '0';
    }
    return *this;
}

// Postfix decrement
GridPosition GridPosition::operator--(int) {
    GridPosition temp = *this;
    if (isdigit(node)) {
        node = (node - '0' - 1 + 10) % 10 + '0';
    }
    return temp;
}