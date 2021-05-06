
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to start a game and create game flow
// Created by Ben Placzek on 2/24/2021.  Revised 4/21/2021

#include "Game.hpp"
#include "BadPlayer.hpp"

bool Game::checkData(string n, int c) {
    // validates a single player's input data
    // name unique

    myPlayers->init();

    for(int j=0; j<myPlayers->count(); j++) {
        if ((n == myPlayers->getCurr()->getName() && myPlayers->getCurr()->getName() != "") &&
            (c == myPlayers->getCurr()->getColor() && myPlayers->getCurr()->getColor() != 0)) {
            throw BadPlayer(n,c);
        }
        else if(n == myPlayers->getCurr()->getName() && myPlayers->getCurr()->getName() != "") {
            throw BadName(n, c);

        }
        else if(c == myPlayers->getCurr()->getColor() && myPlayers->getCurr()->getColor() != 0) {
            throw BadColor(n, c);
        }
        myPlayers->next();
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

    int j = 0; // keep track of players in list

    char input = 'y'; // input for user to enter another player or not
    do {
        // add up to 4 players in circular linked list
        if(j < 4) {
            myPlayers->addItem(getNewPlayer()); // add item to players
            cout << "Enter another player? (Y/N)" << endl;
            cin >> input;
            if(j == 3) cout << "Too bad. Starting game. . . " << endl;
            j++; // incr players in list

        }
            // if there is four players do not read another one
        else {
            input = 'n';
        }

    } while (tolower(input) == 'y');

}


Game::Game() {
    myPlayers = new CList();
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

        } // check our inputs

    }catch(BadPlayer & bp){bp.print();}
    catch (...) {
        cerr << "General exception caught" << endl;
        fatal("Fatal");
    }



    // return dynamically allocated player
    return myPlayer;
}

int Game::oneTurn (Player* pp) {
    // start the players turn on the board
    myBoard->startTurn(pp);

    cout << "----------------------------------------------------------\n" <<
         "Beginning of Turn for " << colors[pp->getColor()] << " player." <<
         "\n----------------------------------------------------------\n";
    for ( ; ; ) {
        cout << *myBoard << endl;

        cout << "----------------------------------------------------------\n" <<
             "Player " << colors[pp->getColor()] << ", make a selection." <<
             "\n----------------------------------------------------------\n";
        cout << "1 - Roll\n";
        cout << "2 - Stop\n";
        cout << "3 - Resign\n";

        int myAction;
        bool stopResult;
        cin >> myAction;

        // exception for actions
        try {
            checkAction(myAction);
        }catch(BadChoice & bc) {
            cin.clear(); // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore some input before continuing
            bc.print();
        }
        catch (...) {
            cin.clear(); // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore some input before continuing
            cerr << "General exception caught" << endl;
        }
        const int *diceList;
        switch (myAction) {
            case 1: { // roll
                diceList = myDie->roll(); // assign the result const int*  result to an array

                if (diceList[0] == 0) { // stop
                    stopResult = myBoard->stop();
                    return stopResult;
                }
                else if (diceList[0] == -1) { //resign
                    return resign();
                }

                if (!myBoard->move(diceList[0])) { // bust if cannot move here
                    cout << "BUST ! ! ! " << endl;
                    myBoard->bust();
                    return 0; // hand it back to any other players
                }
                // bust if cannot move here
                myBoard->move(diceList[1]);
                break;
            }
            case 2: // stop
                stopResult = myBoard->stop();
                return stopResult;
            case 3:
                return resign();

        }
    }

}


bool Game::resign() {
    // stop before resigning
    myBoard->stop();

    // hacky programming here, it announces before it is actually done
    cout << "Player " << colors[myPlayers->getCurr()->getColor()] << " has resigned!" << endl;
    myPlayers->remove(); // removes this current player


    // grammatically correct outputs
    if(myPlayers->count() == 1) cout << myPlayers->count() << " Player remains." << endl;
    else cout << myPlayers->count() << " Players remain." << endl;

    if(myPlayers->empty()) {
        cout << "Thanks for playing!" << endl;
        bye();
        return 1;
    }
    else return 0; // there remain players
}

int Game::play() {
    // players entered via console inputs
    getPlayers();

    // preloaded players
//    Player* p1 = new Player("Ben", blue);
//    myPlayers->addItem(p1);
//    Player* p2 = new Player("Ten", orange);
//    myPlayers->addItem(p2);
//    Player* p3 = new Player("Len", yellow);
//    myPlayers->addItem(p3);
    myPlayers->init();

    for (;;) {
        // prints players
        cout << "----------------------------------------------------------\n"
        << "PLAYER ROSTER\n"
             << "----------------------------------------------------------\n";

        cout << *myPlayers;
        if(oneTurn(myPlayers->getCurr()) == true) {
            return 0;
        }
        myPlayers->next();
    }
}
