#ifndef STACK_H
#define STACK_H
const int maxsize=6;
class Stack
{
public:
    Stack();
    ~Stack();
    bool isEmpty();
    bool isFull();
    void Push(float a);
    float Pop();

private:
    float data[maxsize];
    int top;
};

#endif // STACK_H
