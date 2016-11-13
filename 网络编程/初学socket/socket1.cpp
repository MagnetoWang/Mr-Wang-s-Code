#include<iostream>
using namespace std;
class Cbase
{
public:
	Cbase();
	void Print() const;
	{
		cout<<"Cbase"<<mstatic<<endl;
	}
	static int mstatic;
	~Cbase();
	
};
int Cbase::mstatic=2;
class CDerived:public Cbase
{
public:
	CDerived();
	void Print() const{
		cout<<"CDerived:mstatic="<<mstatic<<endl;
	}
	~CDerived();
	
};
int main(int argc, char const *argv[])
{
	Cbase base;
	CDerived derived;
	base.Print();
	derived.Print();
	cout<<endl;
	base.static=4;
	base.Print();
	derived.Print();
	
	return 0;
}
#include