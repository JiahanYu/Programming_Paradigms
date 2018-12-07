/*
* file name - q1.cpp
* Used for testing the Label Generator
* ----------------------------
* This program tests the labelgen abstraction by using it to generate a sequence of labels.
* its header file refers to q1.h
*/

#include <iostream>
#include "labelgen.h" //label-generator class
using namespace std;

/* Main program */
int Q1() {
    labelGenerator figureNumbers("Figure ", 1);
    labelGenerator pointNumbers("P", 0);
    cout << "Figure numbers: ";
    for (int i = 0; i < 3; i++) {
        if (i > 0) cout <<  ", ";
        cout << figureNumbers.nextLabel();
    }
    cout << endl <<  "Point numbers:  ";
    for (int i = 0; i < 5; i++) {
        if (i > 0) cout << ", ";
        cout << pointNumbers.nextLabel();
    }
    cout << endl << "More figures:   ";
    for (int i = 0; i < 3; i++) {
        if (i > 0) cout << ", ";
        cout << figureNumbers.nextLabel();
    }
    cout << endl;
    return 0;
}