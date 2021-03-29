
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to incorporate a circular linked list for Players
// TEMPLATE
// Created by Ben Placzek on 3/27/2021. Revised 3/28/2021.

#ifndef MAIN_CPP_CLIST_HPP
#define MAIN_CPP_CLIST_HPP

#include "tools.hpp"
#include "Player.hpp"

typedef Player* Item;


template <class T>
class CList {
private:
    class Cell {
    public: // all servant members will be private
        Item* myItem; // hold the data
        Cell* next; // form the linked list
        Cell(Item* data, Cell* reference): myItem(data), next(reference) {
            reference=nullptr;
        };
        ~Cell() { delete myItem; }
    };

    int counter; // store number of Items in the list
    Cell* headPtr;
    Cell* current; // pointer to the current item

public:
    CList() { headPtr = nullptr; }; // constructor initializes the list to empty
    ~CList();// destructor deletes all cells in list
    int count() {return counter;}; // returns # items in list
    bool empty() { // return true if 0 Items and false otherwise
        if (counter == 0) return true;
        else return false;
    }
    ostream& print(ostream& os) const;
    void addItem(T p); // insert a new Player inside new Cell into CListNT
    void init(); // set current item pointer to the first cell in the CListNT
    T next(); // move current item pointer to next cell in list
    void remove(); // removes the current Item and Cell from list delete both
};

template <class T>
inline ostream& operator<<(ostream& os, CList<T> c) {
    return c.print(os);
}


#endif //MAIN_CPP_CLIST_HPP
