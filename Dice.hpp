
// CSCI 4478 - Dr Alice Fischer
// Purpose of program is to set up CantStop Dice and FakeDice.
// Created by Ben Placzek on 1/31/2021.  Revised 4/21/2021

#include "tools.hpp"
#include "BadPlayer.hpp"

// please uncomment for each test
#define myTestFile "../test1.txt"
//#define myTestFile "../test2.txt"
//#define myTestFile "../test3.txt"

extern const char letters[];

#ifndef INC_1_DICE_DICE_H
#define INC_1_DICE_DICE_H


class Dice {
protected:
    bool checkDie(char c1, char c2);
    //Number of dice in the set
    int nDice;
    //Dynamically allocated array of nDice pseudo-random values
    int * randArray;
public:
    // Constructor and Destructor
    Dice(int n);
    virtual ~Dice(){ delete[] randArray;  };

    virtual const int* roll();
    ostream& print(ostream& os) const;

};

// Operator overload to call print statement for dice object
inline ostream& operator <<( ostream& os, Dice& myDice) {
    return myDice.print(os);
}

// Derived class
class CantStopDice: public Dice {

protected:
    int diceTot[2]; // stores totals of dice pairs
public:
    CantStopDice(): Dice(4) {}; // creates 4 six sided dice
    ~CantStopDice()=default;
    virtual const int* roll(); // derived from Dice

};

// Derived from CantStopDice
class FakeDice: public CantStopDice {
private:
    ifstream myStream;
public:
    FakeDice() { myStream.open (myTestFile, ifstream::in); }; // open stream
    ~FakeDice()=default; // close stream
    const int* roll(); // derived from CantStopDice
};

#endif //INC_1_DICE_DICE_H
