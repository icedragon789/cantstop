//
// Created by BPlaz on 3/25/2021.
//

#ifndef MAIN_CPP_CLIST_HPP
#define MAIN_CPP_CLIST_HPP
//template<class T>
//typedef struct

#include "tools.hpp"
#include "Player.hpp"


class CList; // forward declaration of it here
//template <class Item> class CList;


//template <class Item>
class Cell {
private: // all servant members will be private
    Player* myItem; // hold the data
    Cell* next; // form the linked list
    Cell(Player* data, Cell* reference) {reference=nullptr;};

    friend class CList; // gives friendship to CList
};

class CList {
private:
    int counter; // store number of Items in the list
    Cell *headPtr;
    Player* current; // pointer to the current item

public:
    CList() { headPtr = nullptr; }; // constructor initializes the list to empty
    ~CList() { delete headPtr; }; // destructor deletes all cells in list
    int count() {return counter;}; // returns # items in list
    bool empty() { // return true if 0 Items and false otherwise
        if (counter == 0) return true;
        else return false;
    }
    ostream& print(ostream& os) const;
    void addItem(Player* p); // insert a new Player inside new Cell into CList
    void init(); // set current item pointer to the first cell in the CList
    Player* next(); // move current item pointer to next cell in list
    void remove(); // removes the current Item and Cell from list delete both



};

// Operator overload to call print statement for clist object
inline ostream& operator <<( ostream& os, CList& myCList) {
    return myCList.print(os);
}


#endif //MAIN_CPP_CLIST_HPP
