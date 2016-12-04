#include <iostream>
using namespace std;
#define N 30004
int n,Sets[N],distance[N],boxs[N];
void init()
{
	int i;
	for(i=0;i<N;i++)
	{
		distance[i]=0;
		boxs[i]=1;
		Sets[i]=i;
	}
}
int find(int x)
{
	int fx=Sets[x];
	if(fx!=x)
	{
		fx=find(Sets[x]);//将根节点赋值
		distance[x]+=distance[Sets[x]];//当前结点的旧根结点与新节点的距离相加
	}
	return Sets[x]=fx;//返回最新根结点
}
void Union(int x,int y)//两个结点的根要在一起，核心思想
{
	int fx=find(x),fy=find(y);
	Sets[fy]=fx;//旧根的位置设置为新根
	distance[fy]+=boxs[fx];//旧根的距离加上新根底部的所有箱子数。即为新的距离
	boxs[fx]+=boxs[fy];//新根需要变化箱子数，对箱子数进行操作
}
int main()
{
	int n;
	cin>>n;
	char Operate;
	for(int i=0;i<n;i++)
	{
		cin>>Operate;
		if(Operate=='M')
		{
			int x,y;
			cin>>x>>y;
			Union(x,y);
		}else
		{
			int number;
			cin>>number;
			int sum=find(number);
			cout<<boxs[sum]-distance[number]-1<<endl;
		}
	}
}