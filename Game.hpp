
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to start a game and create game flow
// Created by Ben Placzek on 2/24/2021. Revised 3/14/2021.

#ifndef MAIN_CPP_GAME_HPP
#define MAIN_CPP_GAME_HPP

#include "tools.hpp"
#include "Dice.hpp"
#include "Player.hpp"
#include "Column.hpp"
#include "Board.hpp"
#include "CList.hpp"


extern const char letters[];

class Game {

private:
    Dice* myDie; // dice to point at a set of 4 dice

    Board* myBoard; // board with an array of 11 cols

    CList* myPlayers; // circular linked list implementation

    void getPlayers(); // gets all players and places them in CList
    // ----------------------------------------------------- validate player inputs
    bool checkData(string n, int c);
    bool checkAction(int c); // validate player inputs

public:
    Game();  // Two Players, Dice set, Two Columns ready to go
    ~Game(); // free memory
    Player* getNewPlayer(); // input player data from keyboard
    int oneTurn (Player* pp);
    bool resign();
    int play();


};


#endif //MAIN_CPP_GAME_HPP
