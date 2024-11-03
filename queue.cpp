#include "queue.h"
#include <iostream>

using namespace std;

// Desc: Default constructor for objects
// Pre: None
// Post: Sets front and rear to -1
Queue::Queue() {
    front = -1;
    rear  = -1;
}
// Desc: Copy constructor for objects
// Pre: Receives queue
// Post: Copy is completely independent from other
Queue::Queue(Queue const &other) {
    front = other.front;
    rear  = other.rear;
    for (int i = other.front; i <= other.rear; i++) {
        my_queue[i] = other.my_queue[i];
    }
}
// Desc: Default deconstructor for objects
// Pre: None
// Post: None
Queue::~Queue() {
}
// Desc: Assignment operator that sets the queue equal to the queue received
// Pre: Receives queue
// Post: Queue is independent from queue received
void Queue::operator=(Queue const &other) {
    front = other.front;
    rear  = other.rear;
    for (int i = other.front; i <= other.rear; i++) {
        my_queue[i] = other.my_queue[i];
    }
}
// Desc: Moves value received to the back of the queue
// Pre: Receives value
// Post: Value is placed in the rear
void Queue::enqueue(int value) {
    if (rear == MAX - 1) {
        cout << "Queue overflow!" << endl;
    } else {
        if (front == -1) {
            front = 0;
        }
        rear++;
        my_queue[rear] = value;
    }
}
// Desc: Last value is removed and returned
// Pre: None
// Post: Returns removed value
int Queue::dequeue() {
    int value;
    if (rear == -1) {
        cout << "Queue underflow!" << endl;
        return -1;
    } else {
        value = my_queue[front];
        if (front >= rear) {
            front = -1;
            rear  = -1;
        } else {
            front++;
        }
    }
    return value;
}
// Desc: Displays queue
// Pre: None
// Post: None
void Queue::display() {
    if (front == rear) {
        cout << "Queue underflow!" << endl;
    } else {
        for (int i = 0; i <= rear; i++) {
            cout << my_queue[i] << endl;
        }
    }
}