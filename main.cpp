
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to implement one turn
// Created by Ben Placzek on 2/24/2021. Revised 3/14/2021.

#include "CList.hpp"

void testList(CList c);

int main() {
    banner();
    CList c;
    testList(c);
    bye();

    return 0;
}

void testList(CList c) {
//    typedef Player* Item;
    Player* p1 = new Player("Ben", blue);
    c.addItem(p1);
    Player* p2 = new Player("Benjie", orange);
    c.addItem(p2);
    Player* p3 = new Player("Benjo", yellow);
    c.addItem(p3);
    c.init();

    cout << "LIST:\n" << c << endl;

    c.next();
    c.remove();

    cout << "LIST:\n" << c << endl;


//    delete p1;
//    delete p2;
    delete p3;
}