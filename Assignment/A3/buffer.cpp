/*
 * File: buffer.cpp
 * --------------------------------
 * This file implements the EditorBuffer class using an array representation.
 */


#include <iostream>
#include "buffer.h"
using namespace std;


/*
 * Implementation notes: Constructor and destructor
 * ------------------------------------------------
 * The constructor initializes the private fields.  The destructor
 * frees the heap-allocated memory, which is the dynamic array.
 */

EditorBuffer::EditorBuffer() {
    capacity = INITIAL_CAPACITY;
    array = new char[capacity];
    cpArray = new char[capacity];
    length = 0;
    cpLength = 0;
    cursor = 0;
}

EditorBuffer::~EditorBuffer() {
    delete[] array;
    delete[] cpArray;
}

/*
 * Implementation notes: moveCursor methods
 * ----------------------------------------
 * The four moveCursor methods simply adjust the value of the
 * cursor instance variable.
 */

void EditorBuffer::moveCursorForward() {
    if (cursor < length) cursor++;
}

void EditorBuffer::moveCursorBackward() {
    if (cursor > 0) cursor--;
}

void EditorBuffer::moveCursorToStart() {
    cursor = 0;
}

void EditorBuffer::moveCursorToEnd() {
    cursor = length;
}

/*
 * Implementation notes: insertCharacter and deleteCharacter
 * ---------------------------------------------------------
 * Each of the functions that inserts or deletes characters
 * must shift all subsequent characters in the array, either
 * to make room for new insertions or to close up space left
 * by deletions.
 */

void EditorBuffer::insertCharacter(char ch) {
    if (length == capacity) expandCapacity();
    for (int i = length; i > cursor; i--) {
        array[i] = array[i - 1];
    }
    array[cursor] = ch;
    length++;
    cursor++;
}

void EditorBuffer::deleteCharacter() {
    if (cursor < length) {
        for (int i = cursor+1; i < length; i++) {
            array[i - 1] = array[i];
        }
        length--;
    }
}

/* Simple getter methods: getText, getCursor */

string EditorBuffer::getText() const {
    return string(array, length);
}

int EditorBuffer::getCursor() const {
    return cursor;
}

int EditorBuffer::getLength() const {
    return length;
}

/*
 * Implementation notes: expandCapacity
 * ------------------------------------
 * This private method doubles the size of the array whenever the old one
 * runs out of space.  To do so, expandCapacity allocates a new array,
 * copies the old characters to the new array, and then frees the old array.
 */

void EditorBuffer::expandCapacity() {
    char *oldArray = array;
    capacity *= 2;
    array = new char[capacity];
    for (int i = 0; i < length; i++) {
        array[i] = oldArray[i];
    }
    delete[] oldArray;
}


void EditorBuffer::copy(int count) {
    for (cpLength = 0; cpLength < count && cursor <= length; cpLength++, cursor++) {
        cpArray[cpLength] = array[cursor];
    }
}

void EditorBuffer::paste() {
    for (int i = 0; i < cpLength; i++) {
        insertCharacter(cpArray[i]);
    }
}
