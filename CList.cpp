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
    cout << "CURRENT INITIALIZED TO " << *headPtr->myItem << endl;
    if(headPtr != NULL) current = headPtr; // appropriate behavior for empty list
    else current = nullptr;
}

// move current item pointer to next cell in list
Player* CList::next() {
    if (headPtr != nullptr) {
        current = current->next; // move current to next in list
    }
    else {
        cout << "List empty";
    }
    return current->myItem;

}

// removes the current Item and Cell from list delete both
void CList::remove(){
    // if list empty
    if(headPtr == nullptr) return;
    // list contains one cell
    if(headPtr->next == headPtr) {
        headPtr = nullptr;
        return;
    }
    Cell *last = headPtr;
    Cell *d = headPtr;

    cout << "CURRENT IS " << *current->myItem << endl;

    // if current is the head
    if(headPtr->myItem == current->myItem) {
        cout << "REMOVING HEAD " << endl;
        while(last->next != headPtr) last = last->next; // find last

        // point last node to next of head
        last = headPtr->next;
        delete headPtr;
        headPtr = last;
        counter--;
    }

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