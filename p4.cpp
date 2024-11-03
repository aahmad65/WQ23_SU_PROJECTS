// Author: Aidan Ahmad
// Desc: Make a todo list editor

#include "list.h"
#include <iostream>

using namespace std;

// Desc: Emulate a todo list editor
// Post: Frees all memory
int main() {
    char     choice;
    TodoList list;
    string   input;
    bool     running = true;
    cout << endl;
    while (running == true) {
        list.show();
        cout << endl;
        cout << "Input command: ";
        cin >> choice;
        if (choice == 'Q') {
            running = false;
            cout << endl;
        } else if (choice == '+') {
            getline(cin, input);
            if (input.empty()) {
                cout << "No text inputted. Please try again"; // Checking if input exists
            } else {
                list.add_entry(input);
            }
        } else if (choice == '-') {
            getline(cin, input);
            if (input.empty()) {
                cout << "No text inputted. Please try again"; // Checking if input exists
            } else {
                list.remove_entry(input);
            }
        } else if (choice == '<') {
            getline(cin, input);
            if (input.empty()) {
                cout << "No text inputted. Please try again"; // Checking if input exists
            } else {
                list.uncheck(input);
            }
        } else if (choice == '>') {
            getline(cin, input);
            if (input.empty()) {
                cout << "No text inputted. Please try again"; // Checking if input exists
            } else {
                list.check(input);
            }
        } else if (choice == '^') {
            getline(cin, input);
            if (input.empty()) {
                cout << "No text inputted. Please try again"; // Checking if input exists
            } else {
                list.raise(input);
            }
        } else {
            cout << "No command recognized. Please try again" << endl;
        }
    }

    cout << "Have a good day!";

    cout << endl;
    return 0;
}