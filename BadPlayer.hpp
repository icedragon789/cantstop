
// CSCI 4526 - Dr Alice Fischer
// Purpose of program is to incorporate polymorphic exceptions
// Created by Ben Placzek on 4/19/2021. Revised 4/21/2021

#ifndef MAIN_CPP_BADPLAYER_HPP
#define MAIN_CPP_BADPLAYER_HPP

#pragma once
#include "tools.hpp"

extern const string colors[];

// ---------------------------------------------- Color & name is wrong.
class BadPlayer : public exception {
public:
    string name;
    int color;
    BadPlayer(string n, int c) : name(n), color(c) {};
    virtual ~BadPlayer()=default;
    virtual void print() {
        cerr << " Both name and color are being used.\n";
        pr();
    };
    void pr() {
        cerr << "You entered Name: " << name << " and Color: "
        << colors[color] << ". Please reenter. \n";
    };

};

// ---------------------------------------------- Only the name is wrong.
class BadName: public BadPlayer {
public:
    BadName(string n, int c) : BadPlayer(n,c) {}
    virtual ~BadName() {}
    virtual void print() {
        cerr << " Enter a name that is not being used\n";
        pr();
    }
};

// ---------------------------------------------- Only the name is wrong.
class BadColor: public BadPlayer {
public:
    BadColor(string n, int c) : BadPlayer(n,c) {}
    virtual ~BadColor() {}
    virtual void print() {
        cerr << " Enter a color that is not being used\n";
        pr();
    }
};

// -------------------------------------------- Illegal choice of turn action.
class BadChoice : public exception {
public:
    int input1;
    char ch1;
    char ch2;
    BadChoice(int i1, char c1, char c2) : input1(i1), ch1(c1), ch2(c2) {};
    BadChoice() {};
    virtual ~BadChoice()=default;
    virtual void print() {
        cerr << " Bad choice.\n";
        pr(false);
    };
    void pr(bool hasChar) {
        if (!hasChar) {
            cerr << "You entered : " << input1 << ". \n"
                 << " Please reenter. \n";
        }
        else {
            cerr << "You entered : " << ch1 << ", "
                 << ch2 << ". Please reenter. \n";
        }
    };

};

// ---------------------------------------------- Duplicate slots entered.
class DuplicateSlot: public BadChoice {
public:
    DuplicateSlot(int i1, char c1, char c2) : BadChoice(i1, c1, c2) {};
    virtual ~DuplicateSlot() {}
    virtual void print() {
        cerr << " Enter two unique slot choices\n";
        pr(true);
    }
};

// ---------------------------------------------- Either slot choice is wrong.
class BadSlot: public BadChoice {
public:
    BadSlot(int i1, char c1, char c2) : BadChoice(i1, c1, c2) {};
    virtual ~BadSlot() {}
    virtual void print() {
        cerr << " Enter valid slot choices\n";
        pr(true);
    }
};


#endif //MAIN_CPP_BADPLAYER_HPP
