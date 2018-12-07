#include <iostream>
#include "q2.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

string findDNAMatch(string s1, string s2, int start = 0);

void Q2() {
    string sl = toUpperCase(getLine("Enter a long DNA sequence: ")); //here ignore the input case of alphabets
    string ss = toUpperCase(getLine("Enter a shorter DNA strand to attach: "));
    int startPos = getInteger("Enter a index position which the attachment search starts from: "); //attention: the index position starts from 0
    string matchPos = findDNAMatch(ss, sl, startPos); //return all the match positions if there is any
    //print out the result of matching
    if (matchPos == "") {
        cout << "No match found." << endl;
    } else {
        cout << "Match found at position" << matchPos << "." << endl;
    }
}

string findDNAMatch(string s1, string s2, int start) {

    //find the corresponding segment of the shorter DNA strand s1, which has the same length of s1 yet is conjugated in matching(A-T,G-C)
    //To do this, first set the initial value of s1Attached the same as s1, then use the regulation of (A-T G-C) to convert the segment
    string s1Attached = s1;
    for (int i = 0; i < s1.length(); i++) {
        switch (s1Attached.at(i)) {
            case 'A': s1Attached.at(i) = 'T';
                break;
            case 'T': s1Attached.at(i) = 'A';
                break;
            case 'G': s1Attached.at(i) = 'C';
                break;
            case 'C': s1Attached.at(i) = 'G';
                break;
            default: break;
        }
    }

    //find whether the corresponding DNA strand is the sub-sequence of the longer DNA sequence s2
    //If yes, record all the matching index positions
    string matchPos = "";
    for (int i = start; i < s2.length(); i++) {
        int tempPos = s2.find(s1Attached, start);
        if (tempPos != -1) {
            matchPos += " " + integerToString(tempPos);
            start = tempPos + 1;
        }
    }
    return matchPos;
}
