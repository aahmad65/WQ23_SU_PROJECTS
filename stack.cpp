#include "stack.h"
#include <iostream>

using namespace std;

// Desc: Default constructor for objects
// Pre: None
// Post: Sets top to -1
Stack::Stack() {
    top = -1;
}
// Desc: Copy constructor for objects
// Pre: Receives stack
// Post: Creates independent copy of the received stack
Stack::Stack(Stack const &other) {
    for (int i = 0; i <= other.top; i++) {
        my_stack[i] = other.my_stack[i];
    }
    top = other.top;
}
// Desc: Default deconstructor for objects
// Pre: None
// Post: None
Stack::~Stack() {
}
// Desc: Assignment operator that sets stack equal to received stack
// Pre: Receives stack
// Post: Assigns independent copy of the received stack
void Stack::operator=(Stack const &other) {
    for (int i = 0; i <= other.top; i++) {
        my_stack[i] = other.my_stack[i];
    }
    top = other.top;
}
// Desc: Pushes the value received to the top of the stack
// Pre: Receives value
// Post: None
void Stack::push(int value) {
    if (top <= (MAX - 1)) {
        my_stack[++top] = value;
    } else {
        cout << "Stack overflow" << endl;
    }
}
// Desc: Pops the value at the top of the stack
// Pre: None
// Post: Returns removed value
int Stack::pop() {
    if (top < 0) {
        cout << "Stack underflow" << endl;
        return 0;
    } else {
        int item = my_stack[top--];
        return item;
    }
}
// Desc: Gets the top value of the stack
// Pre: None
// Post: Returns top value of stack
int Stack::get_top() {
    return my_stack[top];
}