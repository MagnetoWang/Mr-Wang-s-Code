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
bool creat_hashmap(Data *Hash_Map[])
{
	int amount;
	cin >> amount;
	for (int i; i = 0; i++)
	{
		int number;
		insert_map(Hash_Map, number);
	}
	return 0;
}
int search_in_HashMap(Data *Hash_Map[], int number)
{
	Data *currents;
	int n = 0;
	int positon = number%key_number;
	currents = Hash_Map[positon]->next;
	while (currents->number != number)
	{
		//ptr=currents;
		n++;
		currents = currents->next;
	}
	return n;
}
bool insert_map(Data *Hash_Map[],int number)
{
	Data *currents;
	int positon = number%key_number;
	currents = Hash_Map[positon]->next;
	while (currents != NULL)
	{
		currents = currents->next;
	}
	currents = (Data *)malloc(sizeof(Data));
	currents->number = number;
	currents->next = NULL;
	return 1;
}
bool delete_map(Data *Hash_Map[],int number)
{
	Data *currents, *ptr;
	int positon = number%key_number;
	currents = Hash_Map[positon]->next;
	while (currents->number != number)
	{
		ptr = currents;
		currents = currents->next;
	}
	//currents=(Data *)malloc(sizeof(Data));
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
	cin >> key_number;
	Data *Hash_Map[Maxsize];
	for (int i = 0; i<Maxsize; i++)
	{
		Hash_Map[i]->number = -1;
		Hash_Map[i]->next = NULL;
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
	while (1)
	{
		int choice;
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
}
