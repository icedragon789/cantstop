
#include "tools.hpp"

// CSCI 4478 - Dr Alice Fischer
// Purpose of program is to roll a number of dice, and write the results to file.
// Created by Ben Placzek on 1/31/2021.

#ifndef INC_1_DICE_DICE_H
#define INC_1_DICE_DICE_H


class Dice {

private:
    //Number of dice in the set
    int nDice;
    //Dynamically allocated array of nDice pseudo-random values
    int * randArray;
public:
    // Constructor and Destructor
    Dice(int n);
    ~Dice(){delete[] randArray;  };

    const int* roll();
    ostream& print(ostream& os) const;

};

// Operator overload to call print statement for dice object
inline ostream& operator <<( ostream& os, Dice& myDice) {
    return myDice.print(os);
}

#endif //INC_1_DICE_DICE_H
