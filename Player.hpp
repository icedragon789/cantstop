
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to create players, enter player data, and allow players to WIN!
// Created by Ben Placzek on 2/8/2021. Revised 2/15/2021

#ifndef P2_PLACZEK_PLAYER_HPP
#define P2_PLACZEK_PLAYER_HPP

#include "enums.hpp"
extern const string colors[];

class Player {

private:
    static int memCounter;      // counter to trace memory leaks
    string name;
    colorEnum color; // color blue, red, green, yellow, white
    int numCols = 0 ;     // number of columns the player has captured, initially 0
    int scoreboard[3] = {0,0,0}; // scoreboard to save scores
public:
    // Constructor and Destructor
    Player(string n, colorEnum c);
    ~Player();

    colorEnum getColor()  { return color;}
    string getName()  { return name;}
    int getScore()  { return numCols; }
    // returns true if player wins 3 columns, false otherwise
    bool wonColumn (int colNum);

    ostream& print(ostream& os) const;
};

// Operator overload to call print statement for player object
inline ostream& operator <<( ostream& os, Player& myPlayer) {
    return myPlayer.print(os);
}


#endif //P2_PLACZEK_PLAYER_HPP
