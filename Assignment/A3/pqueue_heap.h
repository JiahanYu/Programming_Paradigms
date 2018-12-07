
#ifndef PROJECT_PQUEUE_HEAP_H
#define PROJECT_PQUEUE_HEAP_H

#include "vector.h"

template <typename ValueType>
class priorityQueue {
public:

    /*
     *  Constructor: LinkedPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Initializes a new LinkedPriorityQueue. Since
     *  this class uses a LinkedList to maintain order,
     *  this initializes the ListNode struct referenced
     *  by the private section's pointer.
     */
    priorityQueue();

    /*
     *  Destructor: ~LinkedPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Frees any heap storage allocated by LinkedPriorityQueue,
     *  which requires the deletion of all ListNodes created
     *  to maintain the queue.
     */
    ~priorityQueue();

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
    void enqueue(ValueType value, double priority);

    /*
     *  Method: dequeue
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue and also removes it from the queue.
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

    priorityQueue(const priorityQueue<ValueType> & src);
    priorityQueue<ValueType> & operator=(const priorityQueue<ValueType> & src);

private:

    /* Type uesed for each heap entry */

    struct HeapEntry {
        ValueType value;                   /* The data value                  */
        double priority;                   /* The priority of this value      */
        long sequence;                     /*            */
    };

    /* Instance variables */

    Vector<HeapEntry> heap;                /* a vector-based queue            */
    long enqueueCount;                     /* Number of enqueued element      */
    int count;                             /* Number of elements in the queue */
    int capacity;                          /* Allocated size of that queue    */

    /* Private method prototypes */

    void deepCopy(const priorityQueue<ValueType> & src);

    bool takesPriority(int i1, int i2);
    void swapHeapEntries(int i1, int i2);

};


template <typename ValueType>
void priorityQueue<ValueType>::swapHeapEntries(int i1, int i2) {
    HeapEntry entry = heap[i1];
    heap[i1] = heap[i2];
    heap[i2] = entry;
}

template <typename ValueType>
bool priorityQueue<ValueType>::takesPriority(int i1, int i2) {
    if (heap[i1].priority < heap[i2].priority) {
        return true;
    }
    if (heap[i1].priority > heap[i2].priority) {
        return false;
    }
    return (heap[i1].sequence < heap[i2].sequence);
}


template <typename ValueType>
priorityQueue<ValueType>::priorityQueue() {
    heap.clear();
    count = 0;
    enqueueCount = 0;
}

template <typename ValueType>
priorityQueue<ValueType>::~priorityQueue() {
    clear();
}

template <typename ValueType>
int priorityQueue<ValueType>::size() const {
    return count;
}

template <typename ValueType>
bool priorityQueue<ValueType>::isEmpty() const {
    return count == 0;
}

template <typename ValueType>
void priorityQueue<ValueType>::clear() {
    heap.clear();
    count = 0;
    enqueueCount = 0;
}


template <typename ValueType>
void priorityQueue<ValueType>::enqueue(ValueType value, double priority) {
    //when heap is full
    if (count == heap.size()) heap.add(HeapEntry());

    int index = count++;
    //insert a new element to the heap
    heap[index].value = value;
    heap[index].priority = priority;
    heap[index].sequence = enqueueCount++;
    //fix up the violation caused by insertion
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (takesPriority(parent, index)) break;
        swapHeapEntries(parent, index);
        index = parent;
    }
}


template <typename ValueType>
ValueType priorityQueue<ValueType>::dequeue() {
    if (isEmpty()) error("dequeue: Attempting to dequeue an empty queue");
    count--;
    ValueType value = heap[0].value;
    //since the heap root is removed, we pick up the last one to replace it
    // but this might violates heap property. Therefore, we heapify it later.
    swapHeapEntries(0, count);
    int index = 0;
    while (true) {
        //fix up once it violates heap property
        // by comparing the priority of parent and his children (left and right)
        int left = 2 * index + 1;   //left child
        int right = 2 * index + 2;  //right child
        if (left >= count) {
            break;
        }
        int child = left;
        if (right < count && takesPriority(right, left)) {
            child = right;
        }
        if (takesPriority(index, child)) {
            break;
        }
        swapHeapEntries(index, child);
        index = child;
    }
    return value;
}


template <typename ValueType>
ValueType priorityQueue<ValueType>::peek() const {
    if(isEmpty()) error("peek: Attempting to peek at an empty queue");
    return heap.get(0).value;
}

template <typename ValueType>
double priorityQueue<ValueType>::peekPriority() const {
    if (isEmpty()) error("peekPriority: Attempting to peek at an empty queue");
    return heap.get(0).priority;
}

template <typename ValueType>
priorityQueue<ValueType>::priorityQueue(const priorityQueue<ValueType> & src) {
    deepCopy(src);
}

template <typename ValueType>
priorityQueue<ValueType> & priorityQueue<ValueType>::operator=(const priorityQueue<ValueType> & src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }
    return *this;
}

template <typename ValueType>
void priorityQueue<ValueType>::deepCopy(const priorityQueue<ValueType> & src) {
    Vector<HeapEntry> cp;
    count = 0;
    for (cp.get(count) = src.heap.get(count); count != src.count; count++) {
        enqueue(cp.get(count).value, cp.get(count).priority);
    }
    enqueueCount = count;
}




#endif