#include <iostream>
using namespace std;
#define Maxsize 100
typedef struct data
{
	int number;
	data * next;
}Data;

/*typedef struct hash_map
{
Data hash;
}Hash_Map[];*/
int key_number;//求余的哈希表
/*
13
4
28
1 2 3 4 5 6 7 8 9 10 11 12 13  15 16 17 18 19 20 21 22 23 24 25 26  28 29 30
1
14
2
27
1
27
3
27
1
27
0
*/
bool insert_map(Data *Hash_Map[], int number)
{
	Data *currents;
	int positon = number%key_number;
	currents = Hash_Map[positon]->next;
	Data *ptr = Hash_Map[positon];
	while (currents != NULL)
	{
		ptr = ptr->next;
		currents = currents->next;
	}
	currents = (Data *)malloc(sizeof(Data));
	currents->number = number;
	currents->next = NULL;
	ptr->next = currents;

	return 1;
}
bool creat_hashmap(Data *Hash_Map[])
{
	int amount;
	cin >> amount;
	for (int i=0; i <amount; i++)
	{
		int number;
		cin >> number;
		insert_map(Hash_Map, number);
	}
	/*for (int i = 0; i < amount; i++)
	{
		Data *currents = Hash_Map[i];
		while (currents!=NULL)
		{
			cout << currents->number << endl;
			currents = currents->next;
		}
	}*/
	return 0;
}
int search_in_HashMap(Data *Hash_Map[], int number)
{
	Data *currents;
	int n = 0;
	int positon = number%key_number;
	currents = Hash_Map[positon];
	while (currents->number != number)
	{
		//ptr=currents;
		n++;
		currents = currents->next;
		if (currents == NULL)
			return 0;
	}
	
	return n;
}

bool delete_map(Data *Hash_Map[],int number)
{
	Data *currents, *ptr=NULL;
	int positon = number%key_number;
	currents = Hash_Map[positon]->next;
	while (currents->number != number)
	{
		ptr = currents;
		currents = currents->next;
	}
	//currents=(Data *)malloc(sizeof(Data));
	if (ptr == NULL)
		return 0;
	ptr->next = currents->next;
	free(currents);
	//currents->number=number;
	//currents->next=NULL;
	return 1;
}

int main()
{
	//int amount,number;
	int number;
	cout << "此哈希表用于除余关键值，输入求余数" << endl;
	cin >> key_number;
	Data *Hash_Map[Maxsize];
	Data *currents;
	for (int i = 0; i<key_number+1; i++)
	{
		/*(Hash_Map[i])->number = -1;
		(Hash_Map[i])->next = NULL;*/
		Hash_Map[i] = (Data *)malloc(sizeof(Data));
		currents = Hash_Map[i];
		currents->number = -1;
		currents->next = NULL;//这里申请空间
	}
	/*for (int i = 0; i<amount; i++)
	{
		cin >> number;
		insert_map(Hash_Map, number);//这里我本来有两个思路，一个是写一个函数用来创建，另一个就是用插入的方法，后来仔细想想插入的方法使用会更广泛一点。这里是传值调用的区别
	}
	while(cin>>number&&number!=0)
	{
	search_in_HashMap(Hash_Map,number);//这里返回查找次数
	}*/
	//上面的程序是需要比较死，我这次打算写一个比较灵活的
	int choice=10;
	while (choice)
	{
		
		cout << "查找为1，插入为2，删除为3,创建为4，退出为0" << endl;
			cin >> choice;
		switch (choice)
		{
		case 0:break;
		case 1:
		{
			cout << "input a data" << endl;
				cin >> number;
			int counts;
			counts = search_in_HashMap(Hash_Map, number);
			printf("%d\n", counts);
			break;
		}
		case 2:
		{
			cout << "input a data" << endl;
				cin >> number;
			bool flag;
			flag = insert_map(Hash_Map, number);
			if (flag == 0)
				printf("failed\n");
			else
				printf("successed\n");
			break;
		}
		case 3:
		{
			cout << "input a data" << endl;
				cin >> number;
			bool flag;
			flag = delete_map(Hash_Map, number);
			if (flag == 0)
				printf("failed\n");
			else
				printf("successed\n");
			break;
		}
		case 4: creat_hashmap(Hash_Map); break;//本来想严谨一点，后面一想太麻烦了中等严谨吧
		default: printf("there is error\n"); break;
		}

	}
	cout << "programme is over" << endl;
	system("pause");
	return 0;
}
