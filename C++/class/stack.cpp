#include "stack.h"
#include "ui_stack.h"
#include<iostream>
using namespace std;
Stack::Stack()
{
    top=-1;
    cout<<"stack initialized"<<endl;
}

Stack::~Stack()
{
    cout<<"stack destroyed"<<endl;

}
bool Stack::isEmpty()
{
    return top==-1?true:false;
}
void Stack::Push(float a)
{
    if(top==maxsize-1)
    {
        cout<<"stack is full!"<<endl;

    }
    else
    {
        top++;
        data[top]=a;
    }
}
float Stack::Pop()
{
    float num;
    if (top==-1)
    {
        cout<<"stack is empty"<<endl;
    }
    else{
        num=data[top];
        top--;
        return num;
    }
}
