
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to create a Board that is populated with Columns
// Created by Ben Placzek on 2/24/2021. Revised 3/1/2021

#include "Board.hpp"

Board::Board(){
    // set array elements 0 and 1 to null
    backBone[0] = NULL;
    backBone[1] = NULL;
    // allocate each of the 11 columns each of proper length
    for (int j = 2; j < 13; j++) {
//        backBone[j] = new Column(j);
        Column* addedCol = new Column(j);
        backBone[j] = addedCol;

    }
}

Board::~Board() {
//    delete currentPlayer; // free Player*
    // loop to deallocate memory in backBone array
    for (int j = 2; j < 13; j++) {
        delete backBone[j];
    }


}

ostream& Board::print(ostream& os) const {
    // loops through and prints each Column object
    for (int j = 2; j < 13; j++) {
        os << *backBone[j];
    }

    return os;
}

void Board::startTurn(Player *p) {
    cout << "Start Turn" << endl;
    // store the Player*
    currentPlayer = p;
    // set tower counter and populated columns to zero
    towerCounter=0;
    for (int j = 0; j < 3; j++){
        populatedCols[j] = 0;
    }
}

bool Board::move(int column) {
    // start with a column
    Column* myCol = backBone[column];

    // return false immediately if captured
    if(myCol->state() == captured) {
        return false;
    }

    // populated columns array at the # towers placed index will hold
    // the column that has a tower
    bool towerInColumn = false;


    // initial tower placement
    for(int j =0; j<3; j++) {
        if (populatedCols[0] == 0) {
            populatedCols[0] = column;
            towerInColumn = true;
        }
        else if (populatedCols[j] == column) {
            towerInColumn = true;
            break;
        }
    }
    cout << "TOWER IN COLUMN? " << towerInColumn << endl;

    if (!towerInColumn) populatedCols[++towerCounter] = column;


    // if we are out of towers return false
    if(towerCounter >= 3 && towerInColumn == false) {
        return false;
    }

    // place a tower in nexzt available slot in the column
    if(myCol->startTower(currentPlayer)) myCol->move();

    cout << endl;

    return true;

}

void Board::stop() {
    // replace all towers by tiles of the correct color
    // use the tower array to decide which columns should be stopped
    for (int j =0; j<3; j++) {
        cout << "POPULATED COLS AT " << j << " IS: " << populatedCols[j] << endl;
        if(populatedCols[j] != 0) {
            backBone[populatedCols[j]]->stop(currentPlayer);
        }
    }
}

void Board::bust() {
    for (int j =0; j<3; j++) {
        if(populatedCols[j] != 0) {
            backBone[populatedCols[j]]->bust();
        }
    }
}