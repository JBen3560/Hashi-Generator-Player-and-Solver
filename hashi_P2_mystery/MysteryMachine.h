#ifndef MYSTERYMACHINE_H
#define MYSTERYMACHINE_H

#include "GridPosition.h"

class MysteryMachine {
public:
    static void setUpBoard(int r, int c, GridPosition** board); // Recursive function to create the game board branches
};

#endif