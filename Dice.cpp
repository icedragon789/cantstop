
// CSCI 4478 - Dr Alice Fischer
// Purpose of program is to roll a number of dice, and write the results to file.
// Created by Ben Placzek on 1/31/2021. Revised 4/21/2021

#include "Dice.hpp"

bool Dice::checkDie(char c1, char c2) {
    // start with duplicate choices
    if (c1 == c2) {
        throw DuplicateSlot(0,c1,c2);
    }
    // check if between allowable A and D
    if (toupper(c1) < 65 || toupper(c1) > 68) throw BadSlot(0,c1,c2);
    if (toupper(c2) < 65 || toupper(c2) > 68) throw BadSlot(0,c1,c2);

    return true;
}

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

// assign random values to dynamically allocated array
const int *
CantStopDice::roll() {
    // for user input selecting dice
    char firstInput;
    char secondInput;

    bool usedDice[4] = {false}; // bit array to track chosen dice
    diceTot[0] = 0;
    diceTot[1] = 0;

    // show the human player the dice rolls

    cout << "Rolling " << nDice << " dice." << endl;

    //fill dice value array with nDice random values
    for (int j = 0; j < nDice; j++)
        randArray[j] = rand() % 6 + 1;

// print out options with letter assignments
    for (int j = 0; j < nDice; j++) {
        cout << letters[j] << "\t" << randArray[j] << " " << endl;
    }

    // loop for entering dice selections
    for (;;) {
        try {
            cout << "Enter two letters, each of which correspond to a dice." << endl;
            cin >> firstInput >> secondInput;
            if(checkDie(firstInput, secondInput)) break;
        }catch(BadChoice & bc) {
            bc.print();
        }
        catch (...) {
            cerr << "General exception caught" << endl;
        }
    }

    firstInput = toupper(firstInput);
    secondInput = toupper(secondInput);


    // assign bit array values that were selected by user
    usedDice[firstInput - 65] = true;
    usedDice[secondInput - 65] = true;

    // first sum gets the dice rolls that the user chose
    diceTot[0] = randArray[firstInput - 65] + randArray[secondInput - 65];
    // find the leftovers for the second sum
    for (int j = 0; j < 4; j++) {
        if (!usedDice[j]) {
            diceTot[1] += randArray[j]; // increment sum by leftover dice roll
        }
    }
    cout << "You rolled sums of " << diceTot[0] <<" and " << diceTot[1] << endl;

    return diceTot;
}


const int *
FakeDice::roll() {

    // read four dice values from the file instead of random

    int generatedDice[4];

    char instruction;

    myStream >> instruction;

    if(instruction == 'R') { // roll

        myStream >> generatedDice[0] >> generatedDice[1] >> generatedDice[2] >> generatedDice[3];


        diceTot[0] = generatedDice[0] + generatedDice[1];
        diceTot[1] = generatedDice[2] + generatedDice[3];

    }
    else { // this case is a S in the file
        diceTot[0] = 0; // assign array all zeros
        diceTot[1] = 0;
    }

    // return pointer to pair array
    return diceTot;
}


