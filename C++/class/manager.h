#ifndef MANAGER_H
#define MANAGER_H
#include"employee.h"

class Manager:public Employee
{
private:
    int level;
public:
    Manager();
    ~Manager();
    void Print_level();
};

#endif // MANAGER_H
