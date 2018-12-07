#ifndef PPriorityQueue_LIST_H
#define PPriorityQueue_LIST_H

#include "error.h"
#include <iostream>
using namespace std;

template <typename valueType>
class PriorityQueue{
public:

    /*
     *  Constructor: PriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Initializes a new LinkedPriorityQueue. Since
     *  this class uses a LinkedList to maintain order,
     *  this initializes the ListNode struct referenced
     *  by the private section's pointer.
     */
    PriorityQueue();



    /*
     *  Destructor: ~PriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Frees any heap storage allocated by LinkedPriorityQueue,
     *  which requires the deletion of all ListNodes created
     *  to maintain the queue.
     */
    ~PriorityQueue();


    /*
     *  Method: size
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the size of the PriorityQueue.
     *  A Linked List requires this function to loop through
     *  all of its entries and count them, returning the
     *  counter as the size.
     */
    int size() const;



    /*
     *  Method: isEmpty
     *  - - - - - - - - - - - - - - - - - -
     *  Determines whether the PriorityQueue is empty.
     *  This can be done by checking if the Head of the
     *  Linked List is linked to any other node in the chain.
     */
    bool isEmpty() const;





    /*
     *  Method: clear
     *  - - - - - - - - - - - - - - - - - -
     *  Removes all items from LinkedPriorityQueue. Since
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
     *  Adds a user-defined item to the PriorityQueue given
     *  the item's key and its corresponding priority level, which is
     *  used for retrieval. Since this queue respects order,
     *  each enqueued must loop through the entirety of the list, and
     *  if it finds its place in between two ListNodes, it must ensure
     *  to insert itself without losing the corresponding memory
     *  addresses for each side of the chain.
     */
    void enQueue(valueType value, double priority);



    /*
     *  Method: dequeue
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue and also removes it from the queue.
     *  Since a LinkedList orders the items by highest priority descending,
     *  this simply needs to dequeue the item right after the
     *  LinkedList's head.
     */
    valueType deQueue();





    /*
     *  Method: peek
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue without removing it.
     *  Since a LinkedList is employed, this is as simple as
     *  calling the key value from the first node after the Head.
     */
    valueType peek();


    /*
     *  Method: peek_priority
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the priority of the highest priority item.
     */
    double peek_priority();


    /*
     * Copy constructor
     */
    PriorityQueue(const PriorityQueue<valueType> &src);


    /*
     * Assignment operator
     */
    PriorityQueue<valueType> &operator=(const PriorityQueue<valueType> &src);


private:

    /*
     * construct the model of Cell
     */
    struct Cell{
        valueType data;
        double priority;
        Cell *link;
    };

    int count; // size of the PriorityQueue

    Cell *head; //a pointer that point to the head of the PriorityQueue

    /*
     * private method prototype
     */

    void deepCopy(const PriorityQueue<valueType> &src);

};


template <typename valueType>
PriorityQueue<valueType>::PriorityQueue(){
    count = 0;
    head = NULL;
}


template <typename valueType>
PriorityQueue<valueType>::~PriorityQueue(){
    clear();
}


template <typename valueType>
bool PriorityQueue<valueType>::isEmpty() const {
    return count == 0;
}


template <typename valueType>
int PriorityQueue<valueType>::size() const {
    return count;
}


template <typename valueType>
void PriorityQueue<valueType>::clear() {
    while (count > 0) {
        deQueue();
    }
}


template <typename valueType>
void PriorityQueue<valueType>::enQueue(valueType value, double priority) {
    Cell *nc = new Cell;
    nc->data = value;
    nc->priority = priority;
    if (count == 0) {
        head = nc;
        nc->link = NULL;
        count++;
        return;
    }
    count++;
    Cell *check_c = head;
    Cell *old_c = head;
    int time = 0;
    while (true) {
        if (nc->priority < check_c->priority) {
            nc->link = check_c;
            if (time == 0){
                head = nc;
            } else {
                old_c->link = nc;
            }
            return;
        }
        if (nc->priority == check_c->priority) {
            nc->link = check_c->link;
            check_c->link = nc;
            return;
        }
        if (check_c->link == NULL) {
            check_c->link = nc;
            nc->link = NULL;
            return;
        }
        old_c = check_c;
        check_c = check_c->link;
        time ++;
    }

}


template <typename valueType>
valueType PriorityQueue<valueType>::deQueue() {
    if (count == 0) error("the PriorityQueue is empty.");
    Cell *nc = head;
    valueType result = nc->data;
    head = nc->link;
    delete nc;
    count --;
    return result;
}


template <typename valueType>
valueType PriorityQueue<valueType>::peek(){
    if (count == 0) error("the PriorityQueue is empty.");
    return head->data;
}


template <typename valueType>
double PriorityQueue<valueType>::peek_priority() {
    if (count == 0) error("the PriorityQueue is empty.");
    return head->priority;
}


template <typename valueType>
PriorityQueue<valueType>::PriorityQueue(const PriorityQueue<valueType> &src) {
    deepCopy(src);
}


template <typename valueType>
PriorityQueue<valueType>& PriorityQueue<valueType>::operator=(const PriorityQueue<valueType> &src) {
    if (this != &src){
        clear();
        deepCopy(src);
    }
    return *this;
}


template <typename valueType>
void PriorityQueue<valueType>::deepCopy(const PriorityQueue<valueType> &src) {
    count = 0;
    if (src.isEmpty()) return;
    Cell *nc = src.head;
    while (nc != NULL){
        enQueue(nc->data, nc->priority);
        nc = nc->link;
    }

}


#endif // PPriorityQueue_LIST_H
