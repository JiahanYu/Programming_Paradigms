
#ifndef PROJECT_BUFFER_H
#define PROJECT_BUFFER_H



class EditorBuffer {


public:

    /*
     * Constructor: EditorBuffer
     * -------------------------
     * Creates an empty editor buffer.
     */

    EditorBuffer();

    /*
     * Destructor: ~EditorBuffer
     * -------------------------
     * Frees any storage associated with this buffer.
     */

    ~EditorBuffer();

    /*
     * Methods: moveCursorForward, moveCursorBackward
     * Usage: buffer.moveCursorForward();
     *        buffer.moveCursorBackward();
     * -----------------------------------
     * These functions move the cursor forward or backward one
     * character, respectively.  If you call moveCursorForward
     * at the end of the buffer or moveCursorBackward at the
     * beginning, the function call has no effect.
     */

    void moveCursorForward();
    void moveCursorBackward();

    /*
     * Methods: moveCursorToStart, moveCursorToEnd
     * Usage: buffer.moveCursorToStart();
     *        buffer.moveCursorToEnd();
     * --------------------------------
     * These functions move the cursor to the start or the end of this
     * buffer, respectively.
     */

    void moveCursorToStart();
    void moveCursorToEnd();

    /*
     * Method: insertCharacter
     * Usage: buffer.insertCharacter(ch);
     * ----------------------------------
     * This function inserts the single character ch into this
     * buffer at the current cursor position.  The cursor is
     * positioned after the inserted character, which allows
     * for consecutive insertions.
     */

    void insertCharacter(char ch);

    /*
     * Method: deleteCharacter
     * Usage: buffer.deleteCharacter();
     * --------------------------------
     * This function deletes the character immediately after
     * the cursor.  If the cursor is at the end of the buffer,
     * this function has no effect.
     */

    void deleteCharacter();


    /*
     * Method: getText
     * Usage: string str = buffer.getText();
     * -------------------------------------
     * Returns the contents of the buffer as a string.
     */

    std::string getText() const;


    /*
     * Method: getCursor
     * Usage: int cursor = buffer.getCursor();
     * ---------------------------------------
     * Returns the index of the cursor.
     */

    int getCursor() const;


    /*
     * Method: getLength
     * Usage: int length = buffer.getLength();
     * ---------------------------------------
     * Returns the length of the buffer.
     */

    int getLength() const;


    /*
     * Method: copy
     * Usage: buffer.copy(count);
     * ---------------------------------------
     * copy the message
     */

    void copy(int count);


    /*
     * Method: paste
     * Usage: buffer.paste();
     * ---------------------------------------
     * paste the copied message
     */

    void paste();



private:

    /*
     * Implementation notes: Buffer data structure
     * -------------------------------------------
     * In the array-based implementation of the buffer, the characters in the
     * buffer are stored in a dynamic array.  In addition to the array, the
     * structure keeps track of the capacity of the buffer, the length of the
     * buffer, and the cursor position.  The cursor position is the index of
     * the character that follows where the cursor would appear on the screen.
     */

    /* Constants */

    static const int INITIAL_CAPACITY = 10;

    /* Instance variables */

    char *array;          /* Dynamic array of characters        */
    char *cpArray;        /* Dynamic copy array of characters   */
    int capacity;         /* Allocated size of that array       */
    int length;           /* Number of character in buffer      */
    int cpLength;         /* Number of character in copy buffer */
    int cursor;           /* Index of character after cursor    */


    /* Private method prototype */

    void expandCapacity();

};


#endif //PROJECT_BUFFER_H
