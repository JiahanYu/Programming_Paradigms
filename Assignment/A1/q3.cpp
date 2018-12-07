#include <iostream>
#include <fstream>
#include "filelib.h"
using namespace std;

void replaceTabs(ifstream &inFile, ofstream &outFile);

void Q3() {
    ifstream infile;
    ofstream outfile;
    promptUserForFile(infile, "Input file: ");  //actually here you are required to input q3file.txt to invoke that file in cmake-build-debug file folder
    promptUserForFile(outfile, "Output file: ");
    replaceTabs(infile, outfile);
    infile.close();
    outfile.close();
}

void replaceTabs(ifstream &infile, ofstream &outfile) {
    char ch;             //because we are going to read the input file character by character
    int tabPeriod = 8;   //because tab stops are usually set at every eight columns
    int cursor = 0;      //refers to the distance the cursor has moved in a certain line (exception: when encountering '\n')
    int convertSize = 0; //the number of spaces which the tab character is replaced by

    while (infile.get(ch)) {
        //Before staring a new line, we have to make sure the cursor is 0 before reading the 1st character of the new line.
        //So we assign -1 to cursor while encountering the '\n'.
        //In this way, after we put '\n' into our output file, the cursor becomes 0 due to the code: cursor++
        if (ch == '\n') cursor = -1;

        if (ch == '\t') {
            convertSize = tabPeriod - (cursor % tabPeriod);
            for (int i = 0; i < convertSize; i++) {
                outfile.put(' ');  //print out the spaces so that the use can see the tabs are replaced by proper spaces
                cout << ' ';
            }
            cursor += convertSize;
        } else {
            outfile.put(ch);
            cout << ch;  //print out the character so that the user can see what has been put into the outfile
            cursor++;
        }
    }
}