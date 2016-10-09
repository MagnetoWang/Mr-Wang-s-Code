
#include<iostream>//int
using namespace std;
struct Sets
{
	int elements;
	Sets *next;
	int howmany;

};
Sets CreatSets();
Sets And_Sets(Sets *Sets1, Sets *Sets2);
Sets Set_Intersection(Sets *Sets1, Sets *Sets2);
Sets Complementary_Sets(Sets *Sets1, Sets *Sets2);
void PrintSets(Sets *Setss)
{
    Sets *p=Setss;
    int n=p->howmany;
	for(int i=0;i<=n;i++)
    {
        p=p->next;
        cout<<p -> elements;
        
    }
};
int main(int argc, char const *argv[])
{
	Sets Sets1 = CreatSets();
	Sets Sets2 = CreatSets();
    PrintSets(&Sets1);
    PrintSets(&Sets2);
	Sets Set_And = And_Sets(&Sets1, &Sets2);
	Sets Set_Inter = Set_Intersection(&Sets1, &Sets2);
	Sets Set_Complem = Complementary_Sets(&Sets1,&Sets2);//不是结构体数组，这里传值需要特别注意

	return 0;
}
Sets CreatSets()
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
	Sets *head = (Sets *)malloc(sizeof(*head));
	Sets *follow = head->next;
	head->howmany=n;
	for (int i = 0; i < n; i++)
	{
		follow = (Sets *)malloc(sizeof(*follow));//一定要开辟一个空间
		cin >> follow->elements;
		cout << follow->elements << "printf elements";
		cout << endl;
		follow = follow->next;
	}
	follow = NULL;
	return *head;//局部变量问题
}
Sets And_Sets(Sets *Sets1, Sets *Sets2)
{
	Sets and_sets;
	Sets *P1 = Sets1->next;
	Sets *P2 = Sets2->next;
	int number = 0;
	Sets *P3 = &and_sets;
	for (int i = 0; i<Sets1->howmany; i++)
	{
		int front_element = P1->elements;
		int j;
		for ( j = 0; j<Sets2->howmany; j++)
		{
			if (front_element == P2->elements)
			{
				break;
			}
		}
		if (j == Sets2->howmany)
		{
			number++;
			P3 =P3->next;
			P3->elements = front_element;
		}
		P1 = P1->next;
	}
	P2 = Sets2;
	for (int j = 0; j<Sets2->howmany; j++)
	{
		number++;
		P3= P3->next;
		P2 = P2->next;
		P3->elements = P2->elements;
	}
	P3->elements = number;
	return *P3;
}
Sets Set_Intersection(Sets *Sets1, Sets *Sets2)
{
	Sets Inter_sets;
	Sets *P1 = Sets1;
	Sets *P2 = Sets2;
	int number = 0;
	Sets *P3 = &Inter_sets;
	for (int i = 0; i < Sets1->elements; i++)
	{
		P1 = P1->next;
		int front_element = P1->elements;
		for (int j = 0; j < Sets2->elements; j++)
		{
			P2 = P2->next;
			if (front_element == P2->elements)
			{
				P3 = P3->next;
				number++;
				P3->elements = front_element;
				break;
			}
		}
		P2 = Sets2;
	}
	Inter_sets.elements = number;
	return Inter_sets;
}
Sets Complementary_Sets(Sets *Sets1, Sets *Sets2)
{
	Sets Complementary;
	memset(&Complementary, 0, sizeof(Complementary));
	return Complementary;

}

