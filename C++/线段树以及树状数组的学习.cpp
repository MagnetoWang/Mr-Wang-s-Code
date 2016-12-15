#include <iostream>
using namespace std;
#define people 50004
int soldiers[people], army;
int lowbit(int k)
{
	return k&-k;//这里使用位运算和，二进制的运算，-k的意思就是二进制码反转，他们之和是什么数，我也不清楚
}
int sum(int k)//求前k个兵营的集合
{
	int re = 0;//
	while (k>0)
	{
		re += soldiers[k];//找出k,
		k -= lowbit(k);//对k,不知道做了什么措施，反正转移到了正确位置
	}
	return re;
}
void add(int k, int v)
{
	while (k <= army)
	{
		s[k] += v;
		k += lowbit(k)
	}
}
int main()
{
	char op[5];
	int test;
	cin >> test;
	for (int i = 0; i<test; i++)
	{
		cin >> army;
		int soldierss;
		memset(soldiers, 0, sizeof(soldiers));
		for (int j = 0; j<army; j++)
		{
			cin >> soldierss;
			add(j, soldierss);
		}
		while (1)
		{
			cin >> op;
			int army1, army2;
			cin >> army1 >> army2;
			if (op[0] == 'Q')
			{
				cout >> sum(army2) - sum(army1) << endl;
			}
			else
			{
				if (op[0] = 'A')
				{
					add(army1, army2);
				}
				else //sub(army1,army2);
				{
					add(army1, -army2);//这里特别注意直接用负号，省去了一段代码
				}
			}

			if (op[0] = 'E')
			{
				break;
			}
		}

	}
}



#define N 5002
int n,s[N],num[N];
int lowbit(int k)
{
	return k&(-k);
}
void add(int k,int v)
{
	int re;
	if(k<n)
	{
		re+=s[k];
		k-=lowbit(k);
	}
}
int sum(int k)
{
	int re;
	while(k>0)
	{
		re+=s[k];
		k-=lowbit[k];
	}
	return re;
}
int main()
{
	int i,j,ans;
	while(cin>>n&&n!=-1)
	{
		memset(s,0,sizeof(s));
		for(i=0;i<n;i++)
		{
			cin>>s[i];
		}
		int tm,tp;
		for(int i=0;i<n;i++)
		{
			tm+=sum(n-num[i]);
			add(n-num[i],1);

		}
		ans =tm;
		for(int i=0;i<n-1;i++)
		{
			tp=tm;
			add(n-num[i],-1);
			tp=tp+sum(n-num[i])-num[i];
			add(n-num[i],1);
			if(ans>tp)
				ans=tp;

		}
		cout<<ans;
	}
}

//树状数组的核心代码
#define MAXN100
int lowbit(int x)
{
	return x&(-x);//求二进制的1的位置
}
void modify(int x,int add)
{

	while(x<=MAXN)
	{
		a[x]+=add;//只需要在指定位置进行修改，不要怕位置弄错。因为位置用lowbit函数作为保证
		x+=lowbit(x);
	}
}
int get_sum(int x)
{
	int ret=0;
	while(x!=0)
	{
		ret+=a[x];//只需要找位置然后相加，不要多想其他的，不要搞的太复杂了
		x=lowbit(x);
	}
	return ret;
}