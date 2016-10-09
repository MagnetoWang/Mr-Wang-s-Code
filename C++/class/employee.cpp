#include "employee.h"
#include<string.h>
#include<iostream>
#include "ui_stack.h"
using namespace std;
Employee::Employee()
{
    name=0;
    age=0;
    salary=0.0;
}
Employee::Employee(char *name1, short age1, float salary1)
{
    name=new char[strlen(name1)+1];
    age=age1;
    salary=salary1;
}
void Employee::PrintInfo()
{
    cout<<name<<endl<<age<<endl<<salary<<endl;
}

Employee::~Employee(){
    delete name;

}
