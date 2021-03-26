
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
    c.init();
    Player* p1 = new Player("Ben", blue);
    c.addItem(p1);
    Player* p2 = new Player("Ben", blue);
    c.addItem(p2);

    cout << c << endl;

    delete p1;
    delete p2;
}