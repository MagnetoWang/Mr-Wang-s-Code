#ifndef CDERIVED_H
#define CDERIVED_H


class CDerived : public CBase
{
public:
    CDerived();
    void Print() const{
        cout<<"CDerived:mStatic="<<mStatic<<endl
    }
};

#endif // CDERIVED_H
