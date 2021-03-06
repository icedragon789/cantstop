
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to incorporate a circular linked list for Players
// TEMPLATE
// Created by Ben Placzek on 3/27/2021. Revised 3/28/2021.

#include "CListT.hpp"

template <>
CListT<Player*>::~CListT() {
    while(headPtr != nullptr) {
        Cell* temp = headPtr->next;
        delete headPtr;
        headPtr = temp;
    }
}

template <>
ostream &CListT<Player*>::print(ostream &os) const {
    Cell *temp = headPtr;
    if (headPtr != NULL) {
        do {
            os << *temp->myItem;
            temp = temp->next;
        } while (temp != headPtr);
        os << endl;
    } else {
        os << "List empty";
    }
    return os;
}

// insert a new Player inside new Cell into CListNT
template <>
void CListT<Player*>::addItem(Item *p){
    Cell* temp = headPtr;
    Cell* myInsert = new Cell(p, temp);

    myInsert->myItem = p; // assign player data
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

// set current item pointer to the first cell in the CListNT
template <>
void CListT<Player*>::init() {
    if(headPtr != NULL) current = headPtr; // appropriate behavior for empty list
    else current = nullptr;
}

// move current item pointer to next cell in list
template <>
Item* CListT<Player*>::next() {
    if (headPtr != nullptr) {
        current = current->next; // move current to next in list
    }
    else {
        cout << "List empty";
    }
    return current->myItem;

}

// removes the current Item and Cell from list delete both
template <>
void CListT<Player*>::remove(){

    // if list empty
    if(headPtr == nullptr) return;
    // list contains one cell
    if(headPtr->next == headPtr) {
        headPtr = nullptr;
        counter--;
        return;
    }

    Cell *last = headPtr;
    Cell *d = headPtr;

    // if current is the head
    if(headPtr->myItem == current->myItem) {
        while(last->next != headPtr) last = last->next; // find last
        // point last node to next of head
        last->next = headPtr->next;
        headPtr = last->next;
        current = headPtr;
        counter--;
    }

        // any other cases
    else {
        // end of list reached or current not in list
        while (last->next != headPtr && last->next->myItem != current->myItem) {
            last = last->next;
        }

        int i = 0;
        // current found so free memory and display the new list
        while (i < counter) {
            if (d->next->myItem == current->myItem) {
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
