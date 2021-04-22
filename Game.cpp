
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to start a game and create game flow
// Created by Ben Placzek on 2/24/2021.  Revised 4/21/2021

#include "Game.hpp"
#include "BadPlayer.hpp"

typedef Player* Item;

bool Game::checkData(string n, int c) {
    // validates a single player's input data
    // name unique
    for(int j=0; j<myPlayers.size(); j++) {
        if ((n == myPlayers[j]->getName() && myPlayers[j]->getName() != "") &&
            (c == myPlayers[j]->getColor() && myPlayers[j]->getColor() != 0)) {
            throw BadPlayer(n,c);
        }
        else if(n == myPlayers[j]->getName() && myPlayers[j]->getName() != "") {
            throw BadName(n, c);

        }
        else if(c == myPlayers[j]->getColor() && myPlayers[j]->getColor() != 0) {
            throw BadColor(n, c);
        }
    }

    return true;

}

bool Game::checkAction(int c) {
    // validates a user input of their choice (oneTurn)
    if ( c > 0 && c < 4) {
        return true;
    }
    else if (c < 1 || c > 3) {
        throw BadChoice(c,0,0); // int, char, char passed
    }
    else {
        throw BadChoice(c,0,0); // int, char, char passed
    }
}


// circular implementation being debugged
void Game::getPlayers() {

//    myPlayers.init();

    char input = 'y'; // input for user to enter another player or not
    do {
//        myPlayers.addItem(getNewPlayer());
        getNewPlayer();

        // add up to 4 players in circular linked list
//        if(myPlayers.count() < 4) {
        if(myPlayers.size() < 4) {
            cout << "Enter another player? (Y/N)" << endl;
            cin >> input;
        }
            // if there is four players do not read another one
        else {
            input = 'n';
        }

    } while (tolower(input) == 'y');

}


Game::Game() {

    myDie = new CantStopDice(); // using normal cantstop dice
//    myDie = new FakeDice(); // using fakedice from a file
    myBoard = new Board();


}

Game::~Game() {
    delete myDie;
    delete myBoard;
}

// function takes console input and returns a player
Player* Game::getNewPlayer() {

    string myColor;
    string myName;
    colorEnum mySelection;
    Player* myPlayer;

    try {
        cout << "Enter your name." << endl;
        cin >> myName;
        // variable for error checking...
        for (;;) {
            cout << "Enter your color (orange, yellow, green, blue)" << endl;
            cin >> myColor;
            switch (tolower(myColor[0])) {
                case 'o':
                    mySelection = orange;
                    break;
                case 'y':
                    mySelection = yellow;
                    break;
                case 'g':
                    mySelection = green;
                    break;
                case 'b':
                    mySelection = blue;
                    break;
                default: {
                    cout << "Invalid input, try again." << endl;
                    colorEnum mySelection = ERR;
                    continue;
                }
            }
            break;  // leave loop
        }

        if(checkData(myName, mySelection)) {
            // create a player object
            myPlayer = new Player(myName, mySelection);
            myPlayers.push_back(myPlayer);
        } // check our inputs

    }catch(BadPlayer & bp){bp.print();}
    catch (...) {
        cerr << "General exception caught" << endl;
        fatal("Fatal");
    }



    // return dynamically allocated player
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
        if (pp->score() == 3) {
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

        // exception for actions
        try {
            checkAction(myAction);

        }catch(BadChoice & bc) {
            bc.print();
        }
        catch (...) {
            cerr << "General exception caught" << endl;
        }

        const int *diceList;

        switch (myAction) {
            case 1: { // roll
                // roll dice to generate random values
                diceList = myDie->roll(); // assign the result const int*  result to an array

                if (diceList[0] == 0) {
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
                return 1;
        }
    }
}

int Game::runGame() {
    getPlayers();

    // prints players
    cout << "PLAYERS: " << endl;
    for (int j = 0; j < myPlayers.size(); j++) {
        cout << *myPlayers[j] << " ";
    }

    for (;;) {

            if (oneTurn(myPlayers[0]) == true)
                return 0;
        }
}