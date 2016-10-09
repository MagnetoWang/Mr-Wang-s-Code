#ifndef EMPLOYEE_H
#define EMPLOYEE_H


class Employee
{
private:
    char *name;
    short age;
    float salary;
public:
    Employee();
    Employee(char *name1,short age1,float salary1);
    void PrintInfo();
    ~Employee();
};


#endif // EMPLOYEE_H
