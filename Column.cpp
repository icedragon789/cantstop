
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to set up column behavior
// Created by Ben Placzek on 2/16/2021

#include "Column.hpp"

const int Column::colLengths[13] = {0,0,3,5,7,9,11,13,11,9,7,5,3};

Column::Column(int cn): colNum(cn) { isPending = colLengths[colNum]; };

ostream& Column::print(ostream& os) const {

    os << "Column: " << colNum <<
       "\tState: " << colStates[myState] << "\t| ";
    // iterate up until the length of the column
    for (int j = 1; j <= colLengths[colNum]; j++) {
        // iterate through each type of marker for a square
        for (int k = 0; k < 5; k++) {
            if (colPositions[k] == 0) {
                os << "-";
                continue;
            }
            if (colPositions[k]==j) os << toygb[k];
            // to handle empty slots add a dash
            else os << "-";
        }
        os << " | ";
    }
    os << "\n";
    return os;
}

// placing a new tower and moving it one square forward
bool Column::startTower(Player* p) {

//     return false if tower place is illegal
    if (myState == captured || myState == pending) return false;

    // player has no tower in column
    if (colPositions[p->getColor()] == 0 && colPositions[0] == 0) {
        colPositions[0] = 0;
        return true;
    }
    else {
        colPositions[0] = colPositions[p->getColor()]; // place tower square after colored tile
    }


// return true if successfully places a tower
    return true;
}

//advance the tower one square in the column
bool Column::move() {
    // move forward one
    colPositions[0]+=1;
    if (colPositions[0] == isPending) myState = pending;

    // illegal move
    if(colPositions[0] > colLengths[colNum]) {
        return false;
    }
    return true;
}

// a player decides to end turn
void Column::stop(Player* p) {
    // set our necessary color to wherever the tower was able to get to
    // this gets set as long as there was a tower this turn
    if(colPositions[0] != 0) colPositions[p->getColor()]  = colPositions[0];
    // set the tower back to the beginning
    colPositions[0] = 0;

    // set pending to captured
    if(myState == pending) {
        p->wonColumn(colPositions[p->getColor()]); // win this column
        myState = captured;
    }
}

void Column::bust() {
    colPositions[0] = 0;
}