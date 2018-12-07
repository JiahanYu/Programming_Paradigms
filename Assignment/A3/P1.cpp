/*
 * File: q1.cpp
 * --------------------------
 * This program implements a simple command-driven text editor, which is
 * used to test the EditorBuffer class.
 */


#include <cctype>
#include <iostream>
#include "buffer.h"
#include "console.h"
#include "foreach.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Function prototypes */

void executeCommand(EditorBuffer & buffer, string line);
void displayBuffer(EditorBuffer & buffer);
void printHelpText();


/* Main Function */

void P1() {
    EditorBuffer buffer;
    while (true) {
        string cmd = getLine("*");
        if (cmd != "") executeCommand(buffer, cmd);
    }
}

/*
 * Function: executeCommand
 * Usage: executeCommand(buffer, line);
 * ------------------------------------
 * Executes the command specified by line on the editor buffer.
 */

void executeCommand(EditorBuffer & buffer, string line) {

    //**** notice: here only implement the repetition of copy operation as the exercise required.

    int N = 1;     //number of times for operating a certain command
    string strN;   //strN is the string representation of N
    int i = 0;

    while (isdigit(line[i])) strN += line[i++]; //Find the position of the command
    if (strN != "") N = stringToInteger(strN);  //Find the number of operations we need to carry out
    char command = line[i];      //command, which is directly corresponded to its behavior


    switch (toupper(command)) {
        case 'I':
            for (int j = 1; j < line.length(); j++) buffer.insertCharacter(line[j]);
            displayBuffer(buffer);
            break;
        case 'D': buffer.deleteCharacter(); displayBuffer(buffer); break;
        case 'F': buffer.moveCursorForward(); displayBuffer(buffer); break;
        case 'B': buffer.moveCursorBackward(); displayBuffer(buffer); break;
        case 'J': buffer.moveCursorToStart(); displayBuffer(buffer); break;
        case 'E': buffer.moveCursorToEnd(); displayBuffer(buffer); break;
        case 'C':buffer.copy(N); displayBuffer(buffer); break;
        case 'P': buffer.paste(); displayBuffer(buffer); break;
        case 'H': printHelpText(); break;
        case 'Q': exit(0);
        default:  cout << "Illegal command" << endl; break;
    }
}


/*
 * Function: displayBuffer
 * Usage: displayBuffer(buffer);
 * -----------------------------
 * Displays the state of the buffer including the position of the cursor.
 */

void displayBuffer(EditorBuffer & buffer) {
    string str = buffer.getText();
    for (int i = 0; i < str.length(); i++) {
        cout << " " << str[i];
    }
    cout << endl;
    cout << string(2 * buffer.getCursor(), ' ') << "^" << endl;
}

/*
 * Function: printHelpText
 * Usage: printHelpText();
 * -----------------------
 * Displays a message showing the legal commands.
 */

void printHelpText() {
    cout << "Editor commands:" << endl;
    cout << "  Iabc  Inserts the characters abc at the cursor position" << endl;
    cout << "  F     Moves the cursor forward one character" << endl;
    cout << "  B     Moves the cursor backward one character" << endl;
    cout << "  D     Deletes the character after the cursor" << endl;
    cout << "  J     Jumps to the beginning of the buffer" << endl;
    cout << "  E     Jumps to the end of the buffer" << endl;
    cout << "  C     Copy this message" << endl;
    cout << "  P     Paste this message here" << endl;
    cout << "  H     Prints this message" << endl;
    cout << "  Q     Exits from the editor program" << endl;
}
