//------------------------------------------------------------
// Mystring.h
//
// This is the header file for a String class.  It is a very useful class, and it illustrates
// many principles of class library design.
//
//------------------------------------------------------------

#ifndef PROJECT_MYSTRING_H
#define PROJECT_MYSTRING_H
using namespace std;

//
// The Mystring class is a generic utility class that will
// allow the developer to use an efficient and easy-to-use
// replacement for the standard char* string.
//
class Mystring {

private:
    // The string data, held internally.  Only accessible by
    // members of this class.  A char* is used, and the original
    // string functions (strlen, strcat) provided by string.h
    // can be used, however the consumer of this class will not
    // have to worry about any of those details.
    char *_strdata;

public:

    // Default constructor.  Called in code like:
    // Mystring s;
    //
    Mystring();


    // Constructor with a char*, called on:
    // Mystring s = "Hello";
    //
    Mystring(const char *cstr);


    //
    // Construction of Mystring from an int
    //
    Mystring(int i);


    // Destructor
    ~Mystring();


    //convert a Mystring to a C++ string
    //
    string toString();


    // Return the string length
    //
    int length() const;


    //return a substring of the current string object
    //
    Mystring substr(int start, int n);


    // Allows concatenating two strings using the '+' operator.
    // returns a reference to the Mystring so that it can be
    // used on the RHS of an equation, such as:
    //
    // Mystring a, b, c;
    // a = (b = c);
    //
    Mystring operator+(const Mystring &mstr);


    // Print to an output stream.  This is a friend function,
    // so it is not a member of Mystring.
    //
    friend ostream &operator<<(ostream &s, const Mystring &mstr);


    // Return the character at a given position
    //
    char &operator[](int pos);


    // the relational operators that compare strings lexicographically.
    //
    int operator==(const Mystring &mstr);

    int operator!=(const Mystring &mstr);

    int operator<(const Mystring &mstr);

    int operator<=(const Mystring &mstr);

    int operator>(const Mystring &mstr);

    int operator>=(const Mystring &mstr);


    // Assignment of a char* to a Mystring.  Called on:
    //
    // Mystring a;
    // a = "Hello";			// Called here
    //
    Mystring &operator=(const char *cstr);


    // Assignment operator.  Called on:
    //
    // Mystring a, b;
    // b = a;				// Here
    //
    Mystring &operator=(const Mystring &mstr);


    // Copy constructor, called when constructing one string
    // from another, such as:
    //
    // Mystring a;
    // Mystring b(a);		// Called here
    //
    Mystring(const Mystring &mstr);


};

#endif //PROJECT_MYSTRING_H