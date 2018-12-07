

#ifndef PROJECT_Q3_H
#define PROJECT_Q3_H

#include <iostream>
#include "pqueue_heap.h"

using namespace std;

void P3() {
    priorityQueue<string> queue;
    //enqueue elements one by one
    queue.enqueue("A", 5);
    queue.enqueue("B", 2);
    queue.enqueue("C", 9);
    queue.enqueue("D", 2);
    queue.enqueue("E", 7);
    //dequeue elements one by one
    for (int i = 0; i < 5; i++){
        cout << queue.peek() << " " << queue.peekPriority() << endl;
        queue.dequeue();
    }
}

#endif
