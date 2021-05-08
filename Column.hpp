
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to set up column behavior
// Created by Ben Placzek on 2/16/2021. Revised 3/24/2021

#ifndef MAIN_CPP_COLUMN_HPP
#define MAIN_CPP_COLUMN_HPP

#include "Player.hpp"
extern const string colStates[];

/* With respect to colPositions:
 array slot significance:
 idx 0: white/tower
 idx 1: orange
 idx 2: yellow
 idx 3: green
 idx 4: blue
 */

class Column {

private:
    // store list of actual column lengths
    const static int colLengths[13];
    // array to hold letters
    const char toygb[5] = {'T', 'O', 'Y', 'G', 'B'};
    // column number 2-12
    int colNum;
    //available, pending, captured
    columnEnum myState = available;
    // array to store position of tower in column
    int colPositions[5] = {0,0,0,0,0};
    // variable to store whether a tower is set to pending
    int isPending;

public:
    // constructor and destructor
    Column(int cn);
    ~Column()=default;
    columnEnum state() { return myState; } //state accessor
    ostream& print(ostream& os) const;
    bool startTower(Player* p); // placing a new tower and moving it one square forward
    bool move(); //advance the tower one square in the column
    void stop(Player* p); // a player decides to end turn
    int getColPos(int pos) { return colPositions[pos]; } // returns the spot of a colored tile in a column
    void bust();

};

// Operator overload to call print statement for column object
inline ostream& operator <<( ostream& os, Column& myColumn) {
    return myColumn.print(os);
}


#endif //MAIN_CPP_COLUMN_HPP
