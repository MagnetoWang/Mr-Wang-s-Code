#include <iostream>
#include <stdlib.h>//这个头文件没有引入导致后面建立链表出问题，编译器也没有出错真奇怪
/*数据
8
1 2 5
1 4 4
2 4 6
2 3 9
3 4 25
3 6 15
4 5 17
5 6 10

11
1 2 3
1 3 5
1 4 6
1 5 10
2 3 4
3 4 2
4 5 7
4 7 9
4 6 16
5 6 12
6 7 14
终于完成了
*/
using namespace std;
typedef struct edge
{
	int origin;
	int destination;
	int weight;
	edge *next;
}Edge;
#define Maxnum 100
int UnFind[Maxnum];
int import(Edge *Graph, int edge_number)//这里假设输入的数据都是数据，否则我们都要一个个检验才行
{
	Edge *current=Graph;
	//Edge *instead = Graph;
	//current = (Edge *)malloc(sizeof(Edge));
	for (int i = 0; i<edge_number; i++)
	{
		current->next = (Edge *)malloc(sizeof(Edge));//这里赋值有问题，如果有下面那个malloc就会出现问题。真奇怪
		current = current->next;
		//Edge *current;

		//current = (Edge *)malloc(sizeof(Edge));
		
		cout << "依次输入起点，终点，和路径长度" << endl;
		cin >> current->origin >> current->destination >> current->weight;
		//instead = instead->next;
		//instead = current;
	}

	current = Graph;
	for (int i = 0; i<edge_number; i++)
	{
		current = current->next;
		
		//cout << "依次输入起点，终点，和路径长度" << endl;

		cout << current->origin <<" "<< current->destination << " " << current->weight<<endl;
	}
	//system("pause");
	return 0;
}
int Sort(Edge *Graph, int edge_number)//这里我打算选用快速排序，还是算了，用插入排序。快速排序链表形式非常麻烦。写完这个程序我在仔细考虑一下
{
	int i, j, n;
	Edge *current = Graph;
	Edge *second, *third;
	third = (Edge*)malloc(sizeof(Edge));
	for (i = 0; i<edge_number; i++)
	{
		current = current->next;
		n = current->weight;
		second = current->next;
		for (j = i + 1; j<edge_number; j++)
		{

			if (n>second->weight)
			{
				n = second->weight;
				third->origin = current->origin;
				third->destination = current->destination;
				third->weight = current->weight;
				current->origin = second->origin;
				current->destination = second->destination;
				current->weight = second->weight;
				second->origin = third->origin;
				second->destination = third->destination;
				second->weight = third->weight;
			}
			second = second->next;

		}
	}
	current = Graph;
	for (int i = 0; i<edge_number; i++)
	{
		current = current->next;

		//cout << "依次输入起点，终点，和路径长度" << endl;

		cout << current->origin << " " << current->destination << " " << current->weight << endl;
	}
//	system("pause");
	return 0;
}//链表排序相关
int find(int x)
{
	int x1 = x;
	/*if(x==UnFind(x))
	{
	return x;
	}*/
	while (x1 != UnFind[x1])
	{
		x1 = UnFind[x1];
		//if(x1==UnFind(x1));
		//return x1;
	}
	int i = x, j;
	while (i != x1)//这里还有一个重置根节点的操作，一开始总感觉少了些什么，原来是这个
	{
		j = UnFind[i];
		UnFind[i] = x1;
		i = j;
	}
	return x1;
}
int joint(int x, int y)
{
	//int t=UnFind[y];
	int xx = find(x);
	int yy = find(y);
	//cout <<"hahaha"<< endl;
	if (xx != yy)
	{
		UnFind[yy] = xx;
	}
	
	return 0;
}
int GenerateTree(Edge *Graph, int edge_number)//使用并查集
{
	Edge *current;
	int weight = 0;
	int j = 0;
	for (int i = 0; i<Maxnum + 1; i++)
	{
		UnFind[i] = i;
	}
	current = Graph;
	for (int i = 0; i<edge_number; i++)
	{
		current = current->next;
			if (find(current->origin) != find(current->destination))
			{
				j++;
				weight += (current->weight);
				joint(current->origin, current->destination);
			}
		//if(j) 结点个数未知
	}
	//cout << j << endl << endl;
	cout << "最小生成树的路径=" << weight << endl;
	return 0;
}
int main()
{
	int edge_number;
	cout << "输入边的个数" << endl;
	cin >> edge_number;
	Edge *Graph = (Edge *)malloc(sizeof(Edge));
	Graph->origin = Graph->destination = Graph->weight = 0;
	Graph->next = NULL;
	import(Graph, edge_number);
	Sort(Graph, edge_number);
	GenerateTree(Graph, edge_number);
	system("pause");
	return 0;
}

