
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to incorporate a circular linked list for Players
// Created by Ben Placzek on 3/27/2021. Revised 3/28/2021.


#include "CListT.hpp"

//void unitTest(CListNT<Player> c);

int main() {
    banner();
    CListT<Player*> c;
    Player* p1 = new Player("Ben", blue);
    c.addItem(p1);

//    cout << c << endl;
//    unitTest(c);

    delete p1;
    return 0;
}

// testing circular linked list function for Items
//void unitTest(CListNT<Player> c) {
//
//    // dummy player definitions
//    Player* p1 = new Player("Ben", blue);
//    c.addItem(*p1);
//    Player* p2 = new Player("Ten", orange);
//    c.addItem(*p2);
//    Player* p3 = new Player("Len", yellow);
//    c.addItem(*p3);
//    Player* p4 = new Player("Jen", green);
//    c.addItem(*p4);
//    c.init();

    // You can add Players
//    cout << "LIST:\n" << c << endl;
//
//    c.next();
//    c.next();
//    c.next();
//    c.next();
//    c.next();
//    c.next();
//
//    c.remove();
//    c.remove();
//    c.remove();
//    c.remove();
//
//    Player* p5 = new Player("Hen", blue);
//    c.addItem(p5);

//    cout << "LIST:\n" << c << endl;
//
//    bye();
//
//}