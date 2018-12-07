/*
 *  File: pqueue_list.h
 *  - - - - - - - - - - - - - - -
 *  This file exports the priorityqueue.
 */

#ifndef PROJECT_PQUEUE_LIST_H
#define PROJECT_PQUEUE_LIST_H

#include <cstddef>    // for NULL
#include <iostream>
#include <string>
#include "error.h"
using namespace std;

/*
 *  Class: priorityqueue
 *  - - - - - - - - - - - - - - -
 *  This class maintains an ordered set of values
 *  that can return pre-prioritized values
 *  using its helper functions.
 */
template <typename ValueType>
class priorityqueue {
public:

    /*
     *  Constructor: Linkedpriorityqueue
     *  - - - - - - - - - - - - - - - - - -
     *  Initializes a new Linkedpriorityqueue. Since
     *  this class uses a LinkedList to maintain order,
     *  this initializes the ListNode struct referenced
     *  by the private section's pointer.
     */
    priorityqueue();

    /*
     *  Destructor: ~Linkedpriorityqueue
     *  - - - - - - - - - - - - - - - - - -
     *  Frees any heap storage allocated by Linkedpriorityqueue,
     *  which requires the deletion of all ListNodes created
     *  to maintain the queue.
     */
    ~priorityqueue();

    /*
     *  Method: size
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the size of the priorityqueue.
     *  A Linked List requires this function to loop through
     *  all of its entries and count them, returning the
     *  counter as the size.
     */
    int size() const;

    /*
     *  Method: isEmpty
     *  - - - - - - - - - - - - - - - - - -
     *  Determines whether the priorityqueue is empty.
     *  This can be done by checking if the Head of the
     *  Linked List is linked to any other node in the chain.
     */
    bool isEmpty() const;

    /*
     *  Method: clear
     *  - - - - - - - - - - - - - - - - - -
     *  Removes all items from Linkedpriorityqueue. Since
     *  this class uses a LinkedList, this requires
     *  each ListNode created to maintain order to be
     *  deleted.
     */
    void clear();

    /*
     *  Method: enqueue
     *  Parameters: string value
     *              int priority
     *  - - - - - - - - - - - - - - - - - -
     *  Adds a user-defined item to the priorityqueue given
     *  the item's key and its corresponding priority level, which is
     *  used for retrieval. Since this queue respects order,
     *  each enqueued must loop through the entirety of the list, and
     *  if it finds its place in between two ListNodes, it must ensure
     *  to insert itself without losing the corresponding memory
     *  addresses for each side of the chain.
     */
    void enqueue(ValueType value, double priority);

    /*
     *  Method: dequeue
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  priorityqueue and also removes it from the queue.
     *  Since a LinkedList orders the items by highest priority descending,
     *  this simply needs to dequeue the item right after the
     *  LinkedList's head.
     */
    ValueType dequeue();

    /*
     *  Method: peek, peekPriority
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item and its priority in the
     *  priorityQueue without removing it.
     *  Since a LinkedList is employed, this is as simple as
     *  calling the key value from the first node after the Head.
     */
    ValueType peek() const;
    double peekPriority() const;

    /*
    * Copy constructor and assignment operator
    * ----------------------------------------
    * These methods implement deep copying for queues.
    */

    priorityqueue(const priorityqueue<ValueType> & src);
    priorityqueue<ValueType> & operator=(const priorityqueue<ValueType> & src);

private:

    /* Type for linked list cell */

    struct Cell {
        ValueType data;                   /* The data value                  */
        double priority;                  /* The priority of this value      */
        Cell *link;                       /* Link to the next cell           */
    };

    /* Instance variables */

    Cell *head;                          /* Pointer to the cell at the head */
    int count;                           /* Number of elements in the queue */

    /* Private method prototypes */

    void deepCopy(const priorityqueue<ValueType> & src);
};



template <typename ValueType>
priorityqueue<ValueType>::priorityqueue() {
    head = NULL;
    count = 0;

}

template <typename ValueType>
priorityqueue<ValueType>::~priorityqueue() {
    clear();
}

template <typename ValueType>
int priorityqueue<ValueType>::size() const {
    return count;
}

template <typename ValueType>
bool priorityqueue<ValueType>::isEmpty() const {
    return count == 0;
}

template <typename ValueType>
void priorityqueue<ValueType>::clear() {
    while (count > 0) {
        dequeue();
    }
}

template <typename ValueType>
void priorityqueue<ValueType>::enqueue(ValueType value, double priority) {
    Cell *cp = new Cell;
    cp->data = value;
    cp->priority = priority;

    if (count == 0) {
        head = cp;
        cp->link = NULL;
        count++;
        return;
    }

    count++;

    Cell *curr = head;
    Cell *prev = head;
    int time = 0;
    while (true) {
        if (priority < curr->priority) {
            cp->link = curr;
            if (time == 0){
                head = cp;
            } else {
                prev->link = cp;
            }
            return;
        }
        if (priority == curr->priority) {
            cp->link = curr->link;
            curr->link = cp;
            return;
        }
        if (curr->link == NULL) {
            curr->link = cp;
            cp->link = NULL;
            return;
        }
        prev = curr;
        curr = curr->link;
        time ++;
    }
}



template <typename ValueType>
ValueType priorityqueue<ValueType>::dequeue() {
    if (isEmpty()) error("dequeue: Attempting to dequeue an empty queue");
    Cell *cp = head;
    ValueType value = cp->data;
    head = cp->link;
    delete cp;
    count--;
    return value;
}


template <typename ValueType>
ValueType priorityqueue<ValueType>::peek() const {
    if(isEmpty()) error("peek: Attempting to peek at an empty queue");
    return head->data;
}

template <typename ValueType>
double priorityqueue<ValueType>::peekPriority() const {
    if(isEmpty()) error("peekPriority: Attempting to peek at an empty queue");
    return head->priority;
}


template <typename ValueType>
priorityqueue<ValueType>::priorityqueue(const priorityqueue<ValueType> & src) {
    deepCopy(src);
}

template <typename ValueType>
priorityqueue<ValueType> & priorityqueue<ValueType>::operator=(const priorityqueue<ValueType> & src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }
    return *this;
}

template <typename ValueType>
void priorityqueue<ValueType>::deepCopy(const priorityqueue<ValueType> & src) {
    head = NULL;
    count = 0;
    for (Cell *cp = src.head; cp != NULL; cp = cp->link) {
        enqueue(cp->data, cp->priority);
    }
}



#endif