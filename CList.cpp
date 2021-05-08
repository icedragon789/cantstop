
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to incorporate a circular linked list for Players
// Created by Ben Placzek on 3/27/2021. Revised 5/6/2021.

#include "CList.hpp"

int CList::memCounter = 0;

// constructor initializes the list to empty
CList::CList() {
    memCounter++;
    headPtr = nullptr;
}

CList::~CList() {
    memCounter--;
    cout << "CList counter: " << memCounter << endl;

    // delete all cells in list
    while(headPtr != nullptr) {
        Cell* temp = headPtr->next;
        headPtr = nullptr;
        headPtr = temp;
    }
}

ostream &CList::print(ostream &os) const {
    Cell *temp = headPtr;
    if (headPtr != NULL) {
        do {
            os << *temp->myPlayer;
            temp = temp->next;
        } while (temp != headPtr);
    } else {
        os << "List empty";
    }
    return os;
}

// insert a new Player inside new Cell into CList
void CList::addItem(Player* p){
    Cell* temp = headPtr;
    Cell* myInsert = new Cell(p, temp);

    myInsert->myPlayer = p; // assign player data
    myInsert->next = headPtr; // circular in nature

    // create new cell
    if(headPtr != nullptr) {
        while(temp->next != headPtr)
            temp = temp->next;
        temp->next = myInsert;
    } else {
        myInsert->next = myInsert;
    }
    headPtr = myInsert;
    counter++;
}

// set current item pointer to the first cell in the CList
void CList::init() {
    if(headPtr != NULL) current = headPtr; // appropriate behavior for empty list
    else current = nullptr;
}

// move current item pointer to next cell in list
Player* CList::next() {
    if (headPtr != nullptr) {
        current = current->next; // move current to next in list
    }

    // unnecessary

//    else {
//        cout << "List empty";
//    }
    return current->myPlayer;

}

// removes the current Item and Cell from list delete both
void CList::remove(){

    // if list empty
    if(headPtr == nullptr) return;
    // list contains one cell
    if(headPtr->next == headPtr) {
        delete headPtr;
        counter--;
        return;
    }

    Cell *last = headPtr;
    Cell *d = headPtr;

    // if current is the head
    if(headPtr->myPlayer == current->myPlayer) {
        while(last->next != headPtr) last = last->next; // find last
        // point last node to next of head
        last->next = headPtr->next;
        delete headPtr;
        headPtr = last->next;
        current = headPtr;
        counter--;
    }

        // any other cases
    else {
        // end of list reached or current not in list
        while (last->next != headPtr && last->next->myPlayer != current->myPlayer) {
            last = last->next;
        }

        int i = 0;
        // current found so free memory and display the new list
        while (i < counter) {
            if (d->next->myPlayer == current->myPlayer) {
                d->next = current->next;
                delete current;
                current = d;
                counter--;
                break;
            } else {
                d = d->next;
                i++;
            }
        }
    }
}