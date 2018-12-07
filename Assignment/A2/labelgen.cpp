
#include "labelgen.h"
#include "strlib.h"

using namespace std;

labelGenerator::labelGenerator(){
}

labelGenerator::labelGenerator(string str, int num) {
    label = str;
    number = num;
}

string labelGenerator::toString() {
    string str = label;
    str += integerToString(number);
    return str;
}

string labelGenerator::nextLabel() {
    string str = label;
    str += integerToString(number);
    number += 1;
    return str;
}