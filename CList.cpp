//
// Created by BPlaz on 3/25/2021.
//

#include "CList.hpp"

ostream &CList::print(ostream &os) const {
    Cell *temp = headPtr;
    if (headPtr != NULL) {
        do {
            cout << *temp->myItem << " ";
            temp = temp->next;
        } while (temp != headPtr);
        cout << endl;
    } else {
        cout << "List empty";
    }
}

// insert a new Player inside new Cell into CList
void CList::addItem(Player* p){
    Cell* temp = headPtr;
    Cell* myInsert = new Cell(p, temp);

    myInsert->myItem = p; // assign player data
    myInsert->next = headPtr; // circular in nature

    // create new cell
    if(headPtr != NULL) {
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
    if(headPtr != NULL) current = headPtr->myItem; // appropriate behavior for empty list
    else current = nullptr;
}

// move current item pointer to next cell in list
Player* CList::next() {
    Player *x;
    Cell *temp = headPtr;
    if (headPtr != NULL) {
        temp = temp->next;
        cout << temp->myItem << " ";
    }
    else {
        cout << "List empty";
        return x;
    }
    return temp->myItem;

}

// removes the current Item and Cell from list delete both
void CList::remove(){

}