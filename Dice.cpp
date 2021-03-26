
// CSCI 4478 - Dr Alice Fischer
// Purpose of program is to roll a number of dice, and write the results to file.
// Created by Ben Placzek on 1/31/2021. Revised 2/24/2021

#include "Dice.hpp"

Dice::Dice(int n) {
    nDice = n;
    randArray = new int[n]; // Allocate space for n items, but vec1 is still empty.
    //Initialize the random number generator
    srand(time(nullptr));

};

// assign random values to dynamically allocated array
const int *
Dice::roll() {
    cout << "Rolling " << nDice << " dice." << endl;

    //fill dice value array with nDice random values
    for (int j = 0; j < nDice; j++)
        randArray[j] = rand() % 6 + 1;

    //return array of dice values as a const int*
    return randArray;
}

// Prints dice rolls for nDice elements
ostream &
Dice::print(ostream &os) const {
    for(int j=0; j < nDice; j++)
        os << randArray[j] << ' ';

    return os << endl;
}


