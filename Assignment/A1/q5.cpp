#include <iostream>
#include "stack.h"
#include "simpio.h"
#include "map.h"
using namespace std;

bool isMatched(string expr);

void Q5() {
    string s = getLine("Enter a string to check: ");
    if (isMatched(s)) {
        cout << s << ": Correctly Bracketed." << endl;
    } else {
        cout << s << ": Incorrectly Bracketed." << endl;
    }
}

bool isMatched(string expr) {
    //create a matching map of brackets where the lefty is the key while the righty is the value
    Map<char,char> map;
    map['('] = ')';
    map['['] = ']';
    map['{'] = '}';
    //create a stack to store the lefty signs such as (, [, { and then use the FILO property to determine matching
    Stack<char> stack;
    for (int i = 0; i < expr.length() ; i++) {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
            stack.push(expr[i]);
        }else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
            if (stack.isEmpty()) {
                return false;
            }
            if (expr[i] != map[stack.pop()]) {
                return false;
            }
        }
    }
    return stack.isEmpty();
}