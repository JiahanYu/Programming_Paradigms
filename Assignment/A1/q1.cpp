
#include <iostream>
#include "random.h"
#include "q1.h"
using namespace std;

void Q1() {
    int total = 0;        //the total flipping number
    int hCCount = 0;      //the number of times headers shown in consecutive way, which has maximum 3
    while  (hCCount < 3) {
        if (randomChance(0.5)) {
            cout << "Heads" << endl;
            hCCount++;
        } else {
            cout << "Tails" << endl;
            hCCount = 0;  //As Tail emerges, the consecutive flipping of headers breaks down so that the value of hCCount go back to 0
        }
        total++;
    }
    cout << "It took " << total << " flips to get 3 consecutive heads." << endl; //print out the result
}
