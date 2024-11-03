// Author: Aidan Ahmad
// Desc: Emulate a Reverse Polish Notation Calculator

#include "queue.h"
#include "stack.h"
#include <iostream>

// OpId is an enum (short for enumeration). Enums assign names
// to integer values, allowing us to map things to a set of
// integer identifiers
enum OpId {
    BAD  = 0, // Does not correspond to any operation
    ADD  = 1,
    SUB  = 2,
    MUL  = 3,
    DIV  = 4,
    TOP  = 5,
    POP  = 6,
    DUP  = 7,
    COND = 8,
    ENQ  = 9,
    DEQ  = 10,
    SAVE = 11,
    LOAD = 12,
    END  = 1024
};

// To represent the mapping between operations and their string
// representation, we will make this helper struct to act as an
// entry in our list of mappings
struct Operation {
    std::string name;
    OpId        id;
};

// The mapping of operation string representations to their
// integer id
Operation const OPERATIONS[] = {
    {"add", ADD},
    {"sub", SUB},
    {"mul", MUL},
    {"div", DIV},
    {"top", TOP},
    {"pop", POP},
    {"dup", DUP},
    {"cond", COND},
    {"enq", ENQ},
    {"deq", DEQ},
    {"save", SAVE},
    {"load", LOAD},
    {"end", END},
};

// The number of entries in the operation id mapping, calculated
// by taking the quotient of the total size of the mapping by
// the size of each entry.
int const OPERATION_COUNT = sizeof(OPERATIONS) / sizeof(Operation);

// desc : Maps token strings to ther corresponding operation IDs, if
//        possible.
// pre  : None
// post : If the input token corresponds to a valid string representation
//        for an operation, the corresponding OpId value is returned. If
//        no such matching exists, OpId::BAD is returned instead
OpId token_to_operation_id(std::string token) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        // Linear search through entries until a match is found...
        if (OPERATIONS[i].name == token) {
            return OPERATIONS[i].id;
        }
    }
    // ... or until we run out of entries
    return OpId::BAD;
}

// desc : Returns true if and only if the input string represents a non-empty
//        string consisting only of roman numerals.
// pre  : None
// post : None, aside from description
bool is_numeric(std::string token) {
    int size = token.size();
    // In the odd case we get an empty string, we count it as *not* an integer
    if (size == 0) {
        return false;
    }
    // Iterate through token, double-checking that the character values are only
    // in the valid range for digits
    for (int i = 0; i < size; i++) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
    }
    return true;
}

// desc : please remember to document these functions, including their bodies
// pre  :
// post :
void evaluate(Stack &active_stack, Queue &active_queue, std::string token) {
    int num1, num2, num3, result, copy;
    if (is_numeric(token)) {
        // Convert the token to its integer value
        int value = stoi(token);
        active_stack.push(value);
    } else {
        // It is advised you use the provided OpId enumeration and id mapping
        // functions to switch between your function calls. Of course, not all
        // operations must be handled here, since the end/save/load operations
        // have special requirements that are easier to meet in the main function
        switch (token_to_operation_id(token)) {
        case OpId::ADD:
            num2   = active_stack.pop();
            num1   = active_stack.pop();
            result = num1 + num2;
            active_stack.push(result);
            break;
        case OpId::SUB:
            num2   = active_stack.pop();
            num1   = active_stack.pop();
            result = num1 - num2;
            active_stack.push(result);
            break;
        case OpId::MUL:
            num2   = active_stack.pop();
            num1   = active_stack.pop();
            result = num1 * num2;
            active_stack.push(result);
            break;
        case OpId::DIV:
            num2 = active_stack.pop();
            num1 = active_stack.pop();
            if (num2 == 0) {
                active_stack.push(num1);
                std::cout << "Cannot divide by zero" << std::endl;
            } else {
                result = num1 / num2;
                active_stack.push(result);
            }
            break;
        case OpId::TOP:
            std::cout << active_stack.get_top() << std::endl;
            break;
        case OpId::POP:
            active_stack.pop();
            break;
        case OpId::DUP:
            copy = active_stack.get_top();
            active_stack.push(copy);
            break;
        case OpId::COND:
            num3 = active_stack.pop();
            num2 = active_stack.pop();
            num1 = active_stack.pop();
            if (num3 == 0) {
                active_stack.push(num2);
            } else {
                active_stack.push(num1);
            }
            break;
        case OpId::ENQ:
            active_queue.enqueue(active_stack.pop());
            break;
        case OpId::DEQ:
            active_stack.push(active_queue.dequeue());
            break;
        // The case below should happen if an invalid id (like OpId::BAD) is
        // yielded by the id mapping function
        default:
            std::cout << "Unrecognized token '" << token << "'\n";
        }
    }
}

// desc : please remember to document these functions, including their bodies
// pre  :
// post :
int main() {
    Stack active_stack;
    Queue active_queue;
    Stack save_stack;
    Queue save_queue;
    // we may want to put something additional here to allow
    // us to save and load the active stack and queue.
    std::string token;
    while (std::cin >> token) {
        if (token == "end") {
            // To get the automatic memory cleanup from the Stack/Queue
            // destructors, we must terminate by returning normally from main
            return 0;
        } else if (token == "save") {
            save_stack.operator=(active_stack);
            save_queue.operator=(active_queue);
        } else if (token == "load") {
            active_stack.operator=(save_stack);
            active_queue.operator=(save_queue);
        } else {
            // to prevent main from becoming too large/complex, we delegate the
            // evaluation of "non-special" operations to a separate function
            evaluate(active_stack, active_queue, token);
        }
    }
}
