
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to incorporate a circular linked list for Players
// TEMPLATE
// Created by Ben Placzek on 3/27/2021. Revised 3/28/2021.

#ifndef MAIN_CPP_CLIST_HPP
#define MAIN_CPP_CLIST_HPP
//template<class T>
//typedef struct

#include "tools.hpp"
#include "Player.hpp"


template<class T>class Cell;

template <class T>
class CList {
private:
    int counter; // store number of Items in the list
    Cell<T> *headPtr;
    Cell<T>* current; // pointer to the current item

public:
    CList() { headPtr = nullptr; }; // constructor initializes the list to empty
    ~CList(); // destructor deletes all cells in list
    int count() {return counter;}; // returns # items in list
    bool empty() { // return true if 0 Items and false otherwise
        if (counter == 0) return true;
        else return false;
    }
    ostream& print(ostream& os) const;
    void addItem(T p); // insert a new Player inside new Cell into CList
    void init(); // set current item pointer to the first cell in the CList
    T next(); // move current item pointer to next cell in list
    void remove(); // removes the current Item and Cell from list delete both

};

// Operator overload to call print statement for clist object
template <class T>
inline ostream& operator <<( ostream& os, CList<T>& myCList) {
    return myCList.print(os);
}

template <class T>
class Cell {
private: // all servant members will be private
    T myItem; // hold the data
    Cell* next; // form the linked list
    Cell(T data, Cell* reference): myItem(data), next(reference) {
        reference=nullptr;
    };
    ~Cell() { delete myItem; }

    friend class CList<T>; // forward declaration for CList
};


#endif //MAIN_CPP_CLIST_HPP
