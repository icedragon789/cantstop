
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to start a game and create game flow
// Created by Ben Placzek on 2/24/2021.  Revised 4/5/2021

#include "Game.hpp"

Game::Game() {

    // create dice to be used
    myDie = new CantStopDice(); // using normal cantstop dice
//    myDie = new FakeDice(); // using fakedice from a file

    myBoard = new Board();

    myPlayer = getNewPlayer(); // user input a player to use

}

Game::~Game() {
    delete myDie;
    delete myPlayer;
    delete myBoard;
}

// function takes console input and returns a player
Player* Game::getNewPlayer() {

    string myColor;
    string myName;
    cout << "Enter your name." << endl;
    cin >> myName;
    // variable for error checking...
    colorEnum mySelection;
    for( ; ; ){
        cout << "Enter your color (orange, yellow, green, blue)" << endl;
        cin >> myColor;
        switch (tolower(myColor[0])) {
            case 'o': mySelection = orange; break;
            case 'y': mySelection = yellow; break;
            case 'g': mySelection = green; break;
            case 'b': mySelection = blue; break;
            default: {
                cout << "Invalid input, try again." << endl; colorEnum mySelection = ERR; continue;
            }
        }
        break;  // leave loop
    }

    // return dynamically allocated player
    Player* myPlayer = new Player(myName, mySelection);
    return myPlayer;
}

int Game::oneTurn (Player *pp) {

    // start the players turn on the board
    myBoard->startTurn(pp);
    cout << "----------------------------------------------------------\n" <<
         "Beginning of Turn for " << colors[pp->getColor()] << " player." <<
         "\n----------------------------------------------------------\n";
    for ( ; ; ) {
        cout << *myBoard << endl;

    // player won
        if(pp->score() == 3) {
            cout << " Player " << colors[pp->getColor()] << " Won!" << endl;
            return 1;
        }

        cout << "----------------------------------------------------------\n" <<
             "Player " << colors[pp->getColor()] << ", make a selection." <<
             "\n----------------------------------------------------------\n";
        cout << "1 - Roll\n";
        cout << "2 - Stop\n";
        cout << "3 - Resign\n";

        int myAction;
        cin >> myAction;

        const int* diceList;

        switch (myAction) {
            case 1: { // roll
                    // roll dice to generate random values
                    diceList = myDie->roll(); // assign the result const int*  result to an array

                    if (diceList[0] == 0)  {
                        myBoard->stop();
                        return 0;
                    }

                    // bust if cannot move here
                    if (!myBoard->move(diceList[0])) {
                        cout << "BUST ! ! ! " << endl;
                        myBoard->bust();
                        return 0; // hand it back to any other players
                    }
                    // bust if cannot move here
                    myBoard->move(diceList[1]);
                    break;
            }

            case 2: // stop

                myBoard->stop();
                return 0; // hand it back to any other players
            case 3: // TODO: resign
                bye();
                return 1;
            default:
                cout << "Invalid input, try again." << endl;
                continue;
        }
    }
}

void Game::runGame() {
    for(;;) {
        if(oneTurn(myPlayer)) break;
    }
}

