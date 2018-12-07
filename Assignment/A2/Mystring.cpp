
// Mystring.cpp
// Implementation file used for the Mystring class


#include <iostream>

// Header file for this class
#include "Mystring.h"

using namespace std;

// To enter debug mode, change DEBUGMODE to 1.
// Otherwise, it will not show up what you have operated with set value 0.
#define DEBUGMODE 0
#define DEBUG(s) if (DEBUGMODE) cout << s << endl;


/* Contructor */
// Default constructor.
Mystring::Mystring() {
    DEBUG("Default constructor")

    // Make _strdata an empty string
    _strdata = new char[1];
    *_strdata = '\0';
}


// Constructor called when a string is constructed with a char*.
Mystring::Mystring(const char* cstr) {
    DEBUG("Char* constructor")

    // Allocate enough space for the char*
    _strdata = new char[strlen(cstr)+1];

    // Copy the char* into the internal string data
    strcpy(_strdata, cstr);
}


// Construction of Mystring from an int
Mystring::Mystring(int i) {
    char istr[10];
    sprintf(istr,"%d",i);

    // Allocate enough space for the new string
    _strdata = new char[strlen(istr) + 1];

    // Copy the new char* data into the string data
    strcpy(_strdata, istr);
}




// Destructor that frees any heap storage allocated by the Mystring
Mystring::~Mystring() {
    DEBUG("Delete a str (" << _strdata << ")")

    delete _strdata;
}



string Mystring::toString() {
    DEBUG("Convert to a C++ string")

    return _strdata;

}

// Return a integer of the length
int Mystring::length() const {
    DEBUG("Find length")

    if (NULL == _strdata) return 0;   //judge if the string is NULL
    const char *endOfStr = _strdata;       //define a pointer
    while ( *endOfStr++ );    //equals to while (*endOfStr++ != '\0')
    int lengthInt = endOfStr - _strdata - 1;
    return lengthInt;
}


// Intercept a substr
Mystring Mystring::substr(int start, int n){
    DEBUG("Substring operator")

    //if n invalid
    if (n <= 0){
        return _strdata;
    } else if (n > length()){
        n = length();
    }

    //to intercept a substring
    char *subStr = new char[n + 1];

    for (int i = 0; i < n ; i++){
        subStr[i] = _strdata[start + i];
    }
    subStr[n] = 0;
    Mystring _strdata(subStr);
    delete[] subStr;
    return _strdata;
}


// Concatenation of two strings
Mystring Mystring::operator+(const Mystring& mstr) {
    DEBUG("String + operator")

    // Temp string to old the original data
    Mystring tmp;

    // Allocate enough space for both string
    tmp._strdata = new char[mstr.length() + this->length() + 1];

    // Copy and concat the strings
    strcpy(tmp._strdata, _strdata);
    strcat(tmp._strdata, mstr._strdata);

    // Return the temporary string
    return tmp;
}


// Send the string to an output string.
ostream& operator<<(ostream& s, const Mystring& mstr) {
    return s << mstr._strdata;
}


// Return the character at a given position
char& Mystring::operator[](int pos) {
    if (pos >= length())
    {
        //call error if the index is outside the bounds of the string
        cout << "Tried to access invalid string index\n";
        exit(1);
    }
    return _strdata[pos];
}




// Return if a string is equal to this string in alphanumeric order
int Mystring::operator==(const Mystring& mstr) {
    DEBUG("Calling ==");
    return (strcmp(_strdata, mstr._strdata) == 0);
}



// Return if a string is not equal to this string in alphanumeric order
int Mystring::operator!=(const Mystring& mstr) {
    DEBUG("Calling !=");
    return (strcmp(_strdata, mstr._strdata) != 0);
}



// Return if a string is after this string in alphanumeric order
int Mystring::operator<(const Mystring& mstr) {
    DEBUG("Calling <");
    return (strcmp(_strdata, mstr._strdata) < 0);
}



// Return if a string is after or equal to this string in alphanumeric order
int Mystring::operator<=(const Mystring& mstr) {
    DEBUG("Calling <=");
    return (strcmp(_strdata, mstr._strdata) <= 0);
}



// Return if a string is before this string in alphanumeric order
int Mystring::operator>(const Mystring& mstr) {
    DEBUG("Calling >");
    return (strcmp(_strdata, mstr._strdata) > 0);
}



// Return if a string is before or equal to this string in alphanumeric order
int Mystring::operator>=(const Mystring& mstr) {
    DEBUG("Calling >=");
    return (strcmp(_strdata, mstr._strdata) >= 0);
}



/* Assignment Operator */
// Assignment of a char* to a Mystring
Mystring& Mystring::operator=(const char* cstr) {
    DEBUG("Char* assignment")

    // Delete the current string
    delete [] _strdata;

    // Allocate enough space for the new string
    _strdata = new char[strlen(cstr) + 1];

    // Copy the new char* data into the string data
    strcpy(_strdata, cstr);

    // Return myself
    return *this;
}


// Assignment of a Mystring into another Mystring
Mystring& Mystring::operator=(const Mystring& mstr) {
    DEBUG("Mystring assignment operator")

    if (&mstr == this)
    {
        DEBUG("Not copying myself");
        return *this;
    }
    // Delete the old string that this class was holding.
    delete [] _strdata;

    // Allocate enough space for the new string.
    _strdata = new char[mstr.length() + 1];

    // Copy the new string into myself
    strcpy(_strdata, mstr._strdata);

    // Return myself
    return *this;
}




/* Copy constructor */
Mystring::Mystring(const Mystring& mstr) {
    DEBUG("Mystring constructor")

    // Allocate enough space for the new string
    _strdata = new char[mstr.length()+1];

    // Copy the string buffer from the new string into
    // myself (I can access the private _strdata in str
    // because I am also a member of Mystring
    strcpy(_strdata, mstr._strdata);
}

