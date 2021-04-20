
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to
// Created by Ben Placzek on 2/24/2021

#ifndef MAIN_CPP_BOARD_HPP
#define MAIN_CPP_BOARD_HPP

#include "Column.hpp"

class Board {
private:
    int towerCounter;        // number of towers that are in use
    int towerCols[3];        //  which columns contain towers
    Column* backBone[13];    // column pointer array
    Player* currentPlayer;
    void pickup();
public:
    Board();
    ~Board();
    ostream& print(ostream& os) const;
    void startTurn(Player* p);
    bool move(int column);
    void stop();
    void bust();

};

// Operator overload to call print statement for Board object
inline ostream& operator <<( ostream& os, Board& myBoard) {
    return myBoard.print(os);
}


#endif //MAIN_CPP_BOARD_HPP
