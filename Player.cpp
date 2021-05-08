
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to create players, enter player data, and allow players to WIN!
// Created by Ben Placzek on 2/8/2021. Revised 2/15/2021

#include "Player.hpp"


int Player::memCounter = 0;

// takes console input for name and color
// ctor for name and color
Player::Player(string n, colorEnum c): name(n), color(c) { memCounter++; }

Player::~Player() {
    memCounter--;
    cout << "Player counter: " << memCounter << endl;
}

bool Player::wonColumn (int colNum) {
    // important error checking: CANT STOP has columns 2-12
    if(colNum < 2 || colNum > 12) {
        return false;
    }
    //variable to return true if player won false if player lost
    if(numCols == 3) {
        return true; // returns true if the player won

    }
    scoreboard[numCols++] = colNum;
    return false; // returns false if the player did not win yet
}

// Prints name and color of player
ostream &
Player::print(ostream &os) const {
    os << "| Name: " << name << " | Color: " << colors[color] <<
        " | Number of columns captured: " << numCols <<
        " | Scoreboard: [" << scoreboard[0] << ", " <<
        scoreboard[1] << ", " << scoreboard[2] << "]" << endl;

    return os;
}
