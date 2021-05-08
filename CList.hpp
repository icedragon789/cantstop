
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to incorporate a circular linked list for Players
// NOT TEMPLATE
// Created by Ben Placzek on 3/27/2021. Revised 3/28/2021.

#ifndef MAIN_CPP_CLIST_HPP
#define MAIN_CPP_CLIST_HPP

#include "tools.hpp"
#include "Player.hpp"


class Cell {
private:
    Player* myPlayer;   // hold the data
    Cell* next;         // form the linked list
    Cell(Player* data, Cell* reference): myPlayer(data), next(reference) {
        next=nullptr;
    };
    ~Cell() { delete myPlayer; }

    friend class CList;     // gives friendship to CList
};


class CList {
private:
    static int memCounter;      // counter to trace memory leaks
    int counter;                // store number of Items in the list
    Cell *headPtr;
    Cell* current;              // pointer to the current item

public:
    CList();
    ~CList();                           // destructor deletes all cells in list
    int count() {return counter;};      // returns # items in list
    bool empty() {                      // return true if 0 Items and false otherwise
        if (counter == 0) return true;
        else return false;
    }
    Player* getCurr() { return current->myPlayer;} // return where we are at
    ostream& print(ostream& os) const;
    void addItem(Player* p);        // insert a new Player inside new Cell into CList
    void init();                    // set current item pointer to the first cell in the CList
    Player* next();                 // move current item pointer to next cell in list
    void remove();                  // removes the current Item and Cell from list delete both

};

// Operator overload to call print statement for clist object
inline ostream& operator <<( ostream& os, CList& myCList) {
    return myCList.print(os);
}


#endif //MAIN_CPP_CLIST_HPP
