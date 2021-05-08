
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to create a Board that is populated with Columns
// Created by Ben Placzek on 2/24/2021.  Revised 4/5/2021

#include "Board.hpp"

int Board::memCounter = 0;

Board::Board(){

    memCounter++;
    // set array elements 0 and 1 to null
    backBone[0] = NULL;
    backBone[1] = NULL;
    // allocate each of the 11 columns each of proper length
    for (int j = 2; j < 13; j++) {
        Column* addedCol = new Column(j);
        backBone[j] = addedCol;

    }
}

Board::~Board() {

    memCounter--;
    cout << "Board counter: " << memCounter << endl;

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
    // store the Player*
    currentPlayer = p;
    // set tower counter and populated columns to zero
    towerCounter=0;
    for (int j = 0; j < 3; j++){
        towerCols[j] = 0;
    }
    pickup(); // function to resume progress of board
}

// private function called by move to pickup a players progress
void Board::pickup() {
    // places a "tower" where our colored pieces are placed
    for (int j =2; j<13; j++) {
        if(backBone[j]->getColPos(currentPlayer->getColor()) != 0) {
            towerCols[towerCounter] = j;
            towerCounter+=1;
        }
    }
}

bool Board::move(const int column) {
    // start with a column
    Column* myCol = backBone[column];


    // return false immediately if captured or pending
    if(myCol->state() == captured || myCol->state() == pending) {
        backBone[column]->stop(currentPlayer); // stop in order to place colored tiles
        return false;
    }

    // populated columns array at the # towers placed index will hold
    // the column that has a tower
    bool towerInColumn = false;

    // if there isnt a tower placed already
    if (towerCols[0] == 0) {
        towerCols[0] = column;
        towerInColumn = true;
    }
        // if there is already a tower placed
    else {
        // initial tower placement
        for (int j = 0; j < 3; j++) {
            if (towerCols[j] == column) { // column for tower to be placed in already has tower
                towerInColumn = true;
                break;
            }
        }
    }

    if (!towerInColumn) towerCols[++towerCounter] = column;

    // if we are out of towers return false
    if(towerCounter >= 3 && !towerInColumn) {
        return false;
    }

    // place a tower in next available slot in the column
    if(myCol->startTower(currentPlayer)) {
        myCol->move();
    }

    return true;

}

// returns 1 to end the game 0 otherwise
bool Board::stop() {

    cout << "Ending turn for Player " << colors[currentPlayer->getColor()] << endl;
    // replace all towers by tiles of the correct color
    // use the tower array to decide which columns should be stopped
    for (int j =0; j<3; j++) {
        if(towerCols[j] != 0) {
            backBone[towerCols[j]]->stop(currentPlayer);
        }
    }

    // player won
    if (currentPlayer->getScore() == 3) {
        cout << " Player " << colors[currentPlayer->getColor()] << " Won!" << endl;
        cout << "Thanks for playing!" << endl;
        bye();
        return 1;
    }
    return 0;
}

void Board::bust() {
    for (int j =0; j<3; j++) {
        if(towerCols[j] != 0) {
            backBone[towerCols[j]]->bust();
        }
    }
}