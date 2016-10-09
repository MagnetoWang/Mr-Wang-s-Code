
#include<iostream>//int
#include<stdlib.h>
using namespace std;
typedef struct sets
{
	int elements;
	struct sets *next;
	int howmany;

}Sets, *XSets;
void CreatSets(Sets *head);
void And_Sets(Sets *Sets1, Sets *Sets2, XSets and_sets);
void Set_Intersection(Sets *Sets1, Sets *Sets2, XSets Inter_sets);//似乎局部变量传值总是内存无法读取
void Complementary_Sets(Sets *Sets1, Sets *Sets2, XSets Complementary);
void PrintSets(Sets *Setss)
{
	XSets p = Setss;
	int n = p->howmany;
	for (int i = 0; i < n; i++)
	{
		p = p->next;
		cout << p->elements << ' ';

	}
};
int main(int argc, char const *argv[])
{
	Sets *Sets1 = (Sets *)malloc(sizeof(Sets1));
	//memset(&Sets1, 0, sizeof(Sets))
	//(&Sets1)malloc(sizeof(Sets1));
	CreatSets(Sets1);
	PrintSets(Sets1);
	Sets *Sets2 = (Sets *)malloc(sizeof(Sets2));
	//memset(&Sets2, 0, sizeof(Sets));
	CreatSets(Sets2);

	PrintSets(Sets2);
	Sets *Set_And = (XSets)malloc(sizeof(Sets));
	And_Sets(Sets1, Sets2, Set_And);
	PrintSets(Set_And);
	XSets Set_Inter = (XSets)malloc(sizeof(Sets));
	Set_Intersection(Sets1, Sets2, Set_Inter);
	PrintSets(Set_Inter);
	XSets Set_Complem = (XSets)malloc(sizeof(Sets));
	Complementary_Sets(Sets1, Sets2, Set_Complem);//不是结构体数组，这里传值需要特别注意
	PrintSets(Set_Complem);
	return 0;
}
void CreatSets(Sets *head)
{
	cout << "How many elements" << endl;
	int n;
	cin >> n;
	/*	Sets head;//结构体需要初始化
	memset(&head, 0, sizeof(head));
	head.howmany = n;
	head.elements = 0;
	Sets *follow = head.next;//结构体需要初始化
	*/
	//head = (Sets *)malloc(sizeof(*head));
	Sets *follow;
	XSets p = head;
	p->howmany = n;
	for (int i = 0; i < n; i++)
	{
		follow = (Sets *)malloc(sizeof(*follow));//一定要开辟一个空间
		cin >> follow->elements;
		//	cout << follow->elements << "printf elements";
		//	cout << endl;
		p->next = follow;
		p = p->next;
		follow = follow->next;

	}
	follow = NULL;
	follow = head->next;
/*	for (int i = 0; i<n; i++)
	{
		cout << follow->elements << "printf elements" << endl;
		follow = follow->next;
	}*/
	//return head;//局部变量问题
}
void And_Sets(Sets *Sets1, Sets *Sets2, XSets and_sets)
{
	//and_sets = (XSets)malloc(sizeof(Sets));
	Sets *P1 = Sets1->next;
	Sets *P2 = Sets2->next;
	int number = 0;
	Sets *P3 = and_sets;
	XSets instead;//初始化也有一定的限制
	for (int i = 0; i<Sets1->howmany; i++)
	{
		int front_element = P1->elements;
		int j;
		for (j = 0; j<Sets2->howmany; j++)
		{
			if (front_element == P2->elements)
			{
				break;
			}
		}
		if (j == Sets2->howmany)
		{
			number++;

			//P3->next;
			instead = (XSets)malloc(sizeof(Sets));
			instead->elements = front_element;
			instead->howmany = number;
			P3->next = instead;
			P3 = P3->next;
		}
		P1 = P1->next;
	}
	P2 = Sets2;
	for (int j = 0; j<Sets2->howmany; j++)
	{
		number++;

		instead = (XSets)malloc(sizeof(Sets));
		P2 = P2->next;
		instead->elements = P2->elements;
		P3->next = instead;
		P3 = P3->next;
		instead->howmany = number;

	}
	P3->next = NULL;
	and_sets->howmany = number;
	// for(int j = 0; j < number; j++)
	{

	}
	//return and_sets;
}
void Set_Intersection(Sets *Sets1, Sets *Sets2, XSets Inter_sets)
{
	//	XSets Inter_sets = (XSets)malloc(sizeof(Sets));
	Sets *P1 = Sets1;
	Sets *P2 = Sets2;
	int number = 0;
	Sets *P3 = Inter_sets;
	XSets instead;
	for (int i = 0; i < Sets1->howmany; i++)
	{
		P1 = P1->next;
		int front_element = P1->elements;
		for (int j = 0; j < Sets2->howmany; j++)
		{
			P2 = P2->next;
			if (front_element == P2->elements)
			{
				instead = (XSets)malloc(sizeof(Sets));

				number++;
				instead->elements = front_element;
				P3->next = instead;
				P3 = P3->next;
				break;
			}
		}
		P2 = Sets2;
	}
	Inter_sets->howmany = number;
	//	return Inter_sets;
}
void Complementary_Sets(Sets *Sets1, Sets *Sets2, XSets Complementary)
{
	//Complementary = (XSets)malloc(sizeof(Sets));
	XSets instead;
	XSets p1;
	XSets last = Complementary;
	XSets Set_Inter = (XSets)malloc(sizeof(Sets));
	Set_Intersection(Sets1, Sets2, Set_Inter);
	int k = 0,number,l=0;
	int u = Sets1->howmany;
	for (int i = 0; i < u; i++)
	{
		Sets1 = Sets1->next;
		p1 = Set_Inter;
		 l = 0;

			 number = Sets1->elements;
		for (int j = 0; j< Set_Inter->howmany; j++)
		{

			if (number == p1->elements)
			{
				
				break;
			}
			p1 = p1->next;
			l++;
		}
		if (l == Set_Inter->howmany)
		{
			instead = (XSets)malloc(sizeof(Sets));
			instead->elements = number;
			//	Complementary->next=instead;
			//	Complementary=Complementary -> next;
			last->next = instead;
			last = last->next;
			k++;
		}
	}
	Complementary->howmany = k-1;
	//memset(&Complementary, 0, sizeof(Complementary));

	//	return Complementary;

}

