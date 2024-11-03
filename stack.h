using namespace std;

int const MAX = 1000;

class Stack {
    private:
    int top;

    public:
    int my_stack[MAX];

    Stack();
    Stack(Stack const &other);
    ~Stack();
    void operator=(Stack const &other);
    void push(int value);
    int  pop();
    int  get_top();
};