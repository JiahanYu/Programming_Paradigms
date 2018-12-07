//This cpp file is used for testing Mystring class in Mystring.cpp

#include <iostream>
#include "stdio.h"
#include "Mystring.h"
using namespace std;


void Q5() {
    Mystring str;			// Default constructor
    cout << "Str is " << str << endl;

    str = "Hello";			// Assignment from char*
    cout << "Str is " << str << endl;

    Mystring str2 = "My";	// Constructor from char*
    cout << "Str2 is " << str2 << endl;

    Mystring str3(str2);	// Constructor from Mystring&
    cout << "Str3 is " << str3 << endl;

    str3 = str;				// Assignment from Mystring&
    cout << "Str3 is " << str3 << endl;

    Mystring str4;
    str4 = str + str2 + str3;	// + operator and the
    // = operator
    cout << "Str4 is " << str4 << endl;

    cout << str + str2 + str3 << endl;	// + operator, with a
    // temporary string
    // constructed in place

    cout << str.substr(1,3) << endl;
    cout << "Here c++ string: !!!" << str.toString() << endl;

    // These are constructors called to create temporary Mystrings
    cout << Mystring("Hello ") + Mystring("There!") << endl;


    cout << str3 + "Goodbye" << endl;	// Here the compiler is
    // smart enough to convert
    // the char* into a Mystring
    // and then call the + operator

    str3 = str3;			// Assignment to self
    str3[4] = 'X';			// Change a character
    cout << "Str3: " << str3 << endl;


    cout << "Str: " << str << endl;
    cout << "Str2: " << str2 << endl;

    cout << (str == str2) << endl;
    cout << (str != str2) << endl;
    cout << (str < str2) << endl;
    cout << (str <= str2) << endl;
    cout << (str > str2) << endl;
    cout << (str >= str2) << endl;



    Mystring str5 = 100;
    cout << "Str5: " << str5 << endl;

    str5 = Mystring(200) + "+" + 300 + "==" + (200+300);
    cout << "Str5: " << str5 << endl;

    str5 = 300 + 400;			// Build a string "700"
    cout << "Str5: " << str5 << endl;
}