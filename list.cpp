#include "list.h"
#include <iostream>

using namespace std;

// Desc: Creates new list
// Post: Head either always pointing to nullptr or other entrynode
TodoList::TodoList() {
    head = nullptr;
}
// Desc: Creates new list matching the input
// Post: Independent list is created
TodoList::TodoList(TodoList const &other) {
    head = nullptr;
    head = other.head;
}
// Desc: Deconstructs list
// Post: Frees all memory
TodoList::~TodoList() {
    while (head != nullptr) {
        EntryNode *temp = head;
        head            = head->next; // Preventing memory loss
        delete temp;
    }
}
// Desc: Adds entry to list
// Pre: Receives text for entry
// Post: List has new node
void TodoList::add_entry(string text) {
    EntryNode *temp = new EntryNode;
    temp->next      = head;
    temp->text      = text; // Setting new node up
    head            = temp;
}
// Desc: Removes entry from list
// Pre: Receives text for removal
// Post: List has one less node
void TodoList::remove_entry(string text) {
    if (head != nullptr) {
        EntryNode *curr_node = head;
        if (head->text == text) {
            head = head->next;
            delete curr_node;
        } else {
            EntryNode *prev_node = nullptr;
            while (curr_node != nullptr && curr_node->text != text) { // Checking if item is in the list
                prev_node = curr_node;
                curr_node = curr_node->next;
            }
            if (curr_node != nullptr) {
                prev_node->next = curr_node->next; // If item is in list, remove
                delete curr_node;
            }
        }
    }
}
// Desc: Raises the entry by one in the list
// Pre: Receives text for raising
// Post: Node with text as name is moved up once
void TodoList::raise(string text) {
    if (head != nullptr) {
        EntryNode *curr_node = head;
        EntryNode *save     = nullptr;
        if (head->text == text) {
            cout << "Item is at the top of the list." << endl;
        } else {
            EntryNode *prev_node = nullptr;
            while (curr_node != nullptr && curr_node->text != text) {
                prev_node = curr_node; // Checking if item is in the list
                curr_node = curr_node->next;
            }
            if (curr_node != nullptr) {
                save            = prev_node->next;
                save->next      = curr_node->next;
                prev_node->next = curr_node; // Raising item
                curr_node->next = save;
            }
        }
    }
}
// Desc: Checks the node on the list
// Pre: Receives text to check
// Post: Node with text as name is checked
void TodoList::check(string text) {
    for (EntryNode *iter = head; iter != nullptr; iter = iter->next) {
        if (iter->text == text) {
            iter->checked = true; // Finding item
        }
    }
}
// Desc: Unchecks the node on the list
// Pre: Receives text to uncheck
// Post: Node with text as name is unchecked
void TodoList::uncheck(string text) {
    for (EntryNode *iter = head; iter != nullptr; iter = iter->next) {
        if (iter->text == text) {
            iter->checked = false; // Finding item
        }
    }
}
// Desc: Shows the list
void TodoList::show() {
    char check = ' ';
    for (EntryNode *iter = head; iter != nullptr; iter = iter->next) {
        if (iter->checked == true) {
            check = 'X';
        } else { // Getting checked state
            check = ' ';
        }
        cout << "[" << check << "]" << iter->text << endl;
    }
}