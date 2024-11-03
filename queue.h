using namespace std;

class Queue {
    private:
    int const MAX = 1000;
    int       my_queue[1000];
    int       front;
    int       rear;

    public:
    Queue();
    Queue(Queue const &other);
    ~Queue();
    void operator=(Queue const &other);
    void enqueue(int value);
    int  dequeue();
    void display();
};