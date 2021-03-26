
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to start a game and create game flow
// Created by Ben Placzek on 2/24/2021. Revised 3/16/2021.

#include "Game.hpp"

Game::Game() {

    // create dice to be used
    myDie = new Dice(4);

    myBoard = new Board();

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

    cout << "Begin One Turn" << endl;
    // start the players turn on the board
    myBoard->startTurn(pp);
    for ( ; ; ) {

    cout << *myBoard << endl;

    // player won
        if(pp->score() == 3) {
            cout << pp->getColor() << " Player Won!" << endl;
            return 1;
        }

        cout << "----------------------------------------------------------\n" <<
             "Beginning of Turn for " << colors[pp->getColor()] << " player." <<
             "\n----------------------------------------------------------\n";
        cout << "1 - Roll\n";
        cout << "2 - Stop\n";
        cout << "3 - Resign\n";

        int myAction;
        cin >> myAction;

        const int* diceList;
        bool usedDice[4] = {false}; // bit array to track chosen dice
        char firstInput;
        char secondInput;
        int firstSum = 0; // sum of the dice first chosen by the user
        int secondSum = 0; // sum of the dice not chosen by the user


        switch (myAction) {
            case 1: { // roll
                    cout << *myBoard << endl;
                    // roll dice to generate random values
                    diceList = myDie->roll(); // assign the result const int*  result to an array

                    // print out options with letter assignments
                    for (int j = 0; j < 4; j++) {
                        cout << letters[j] << "\t" << diceList[j] << " " << endl;
                    }

                    // loop for entering dice selections
                    for (;;) {
                        cout << "Enter two letters, each of which correspond to a dice." << endl;
                        cin >> firstInput >> secondInput;
                        firstInput = toupper(firstInput);
                        secondInput = toupper(secondInput);

                        // implicit ASCII conversion for input validation
                        if (firstInput == secondInput) {
                            cout << "Your inputs cannot be the same, try again. " << endl;
                            continue;
                        }
                        //error handling
                        if ((firstInput > 64 && firstInput < 69) && (secondInput > 64 && secondInput < 69)) {
                            break;
                        } else {
                            cout << "Invalid input, try again. " << endl;
                            continue;
                        }
                    }

                    // assign bit array values that were selected by user
                    usedDice[firstInput - 65] = true;
                    usedDice[secondInput - 65] = true;

                    // first sum gets the dice rolls that the user chose
                    firstSum = diceList[firstInput - 65] + diceList[secondInput - 65];
                    // find the leftovers for the second sum
                    for (int j = 0; j < 4; j++) {
                        if (!usedDice[j]) {
                            secondSum += diceList[j]; // increment sum by leftover dice roll
                        }
                    }

                    cout << "You rolled sums of " << firstSum <<" and " << secondSum << endl;


                    // bust if cannot move here
                    if (!myBoard->move(firstSum)) {
                        cout << "BUST ! ! ! " << endl;
                        myBoard->bust();
                        break;
                    }
                    // bust if cannot move here
                    myBoard->move(secondSum);
                    break;
            }

            case 2: // stop

                myBoard->stop();
                continue;
            case 3: // TODO: resign
                bye();
                return 0;
            default:
                cout << "Invalid input, try again." << endl;
                continue;
        }
//    break;

    }

//    return 0;

}

