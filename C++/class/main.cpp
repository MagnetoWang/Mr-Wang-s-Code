#include "stack.h"
#include <QApplication>
#include<iostream>
#include"employee.h"
#include"manager.h"
using namespace std;

int main(int argc, char *argv[])
{
        Stack S1;
        Employee E1;
        Manager M1;
        for (int i = 0; i <= maxsize-1; i++)
        {
            S1.Push(i);

        }
        while (!S1.isEmpty())
        {
            cout<<S1.Pop()<<""<<endl;

        };
        E1.PrintInfo();
        M1.Print_level();
        return 0;


}
