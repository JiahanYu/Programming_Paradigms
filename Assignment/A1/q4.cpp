#include <iostream>
#include "stack.h"
#include "queue.h"
#include "simpio.h"

using namespace std;

void reverseQueue(Queue<string> & queue);

void Q4() {
    Queue<string> queue;
    string line = getLine("Enter a string to reverse: ");
    for (int i = 0; i < line.length(); i++) {
        queue.enqueue(line.substr(i,1));
    }
    reverseQueue(queue);

    //print out the reversed queue by using dequeue() method
    cout << "The queue by reversing a string character by character is: " << endl;
    int size = queue.size();
    for (int i = 0; i < size; i++) {
        cout << queue.dequeue() << endl;
    }
}

void reverseQueue(Queue<string> & queue) {
    int size = queue.size();
    Stack<string> stack;
    for (int i = 0; i < size; i++) {
        stack.push(queue.dequeue());
    }
    for (int i = 0; i < size; i++) {
        queue.enqueue(stack.pop());
    }
}
