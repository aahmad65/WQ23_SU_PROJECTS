#include <iostream>

using namespace std;

struct EntryNode {
    bool       checked;
    string     text;
    EntryNode *next;
};

class TodoList {
    private:
    EntryNode *head;

    public:
    TodoList();
    TodoList(TodoList const &other);
    ~TodoList();
    void add_entry(string text);
    void remove_entry(string text);
    void raise(string text);
    void check(string text);
    void uncheck(string text);
    void show();
};
