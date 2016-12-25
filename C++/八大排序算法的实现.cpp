#include <iostream>
using namespace std;//可视化排序过程
#define Maxsize 100
void printSort(int *b,int n)
{
	   for(int pp=0;pp<n;pp++)
		   {
			   cout<<b[pp]<<" ";
		    }
}
int Derect_insertion_sort(int *a,int n)
{
	int b[Maxsize];
	   for(int pp=0;pp<n;pp++)
		{
			b[pp]=-1;
		}
	for(int i=0;i<n;i++)
	{
		cout<<"第"<<i+1<<"次；";
		for(int pp=0;pp<n;pp++)
		{
			cout<<b[pp]<<" ";
		}
		cout<<endl;
		if(i==0)
			b[i]=a[i];
		else
		{
			int j=i;
			while(j)
			{
				if(b[j-1]<=a[i])
				b[j]=a[i];
		     	else
		     	{
		     		b[j]=b[j-1];
		     	    j--;
		     	}

			}
			if(j==0)
				b[0]=a[i];

		}
	}
	return 0;
}
int Hill_sort(int *a,int n)
{
	int b[Maxsize];
		for(int pp=0;pp<n;pp++)
		{
			b[pp]=a[pp];//就一个数组可以完成
		}
		int step=n/2;
		int t;
		int o=0;
		while(step)
		{

			cout<<"第"<<o<<"次；";
			printSort(b,n);
		   cout<<endl;
			for(int i=0;i+step<n;i++)
			{

				if(b[i]<b[i+step])
				{
					t=b[i];
					b[i]=b[i+step];
					b[i+step]=t;
				}
			}
			step--;
			o++;
		}
		return 0;
}
int Bubble_sort(int *a,int n)
{
	int b[Maxsize];
			for(int pp=0;pp<n;pp++)
		{
			b[pp]=a[pp];//就一个数组可以完成
		}
	int t,flag=0;
	int o=0;
	do
	{
		cout<<"第"<<o<<"次；";
		printSort(b,n);
		cout<<endl;
		flag=0;
	   for(int i=0;i<n;i++)
	   {
	   	 if(b[i]>b[i+1])
	   	 {
	   	 	t=b[i];
	   	 	b[i]=b[i+1];
	   	 	b[i+1]=t;
	   	 	flag++;
	   	 }
	   }
	   o++;

	}while(flag)

	return 0;
}
int Quick_sort(int *a,int begin,int end)
{
	//int Ibegin=begin,Iend=end;
	int b[Maxsize];
	for(int pp=0;pp<end;pp++)
	{
		b[pp]=a[pp];//就一个数组可以完成
	}
	Quick(b,begin,end);
	return 0;
}
int Quick(int *b,int begin,int end)
{
	int Ibegin=begin,Iend=end;
	int max,min;
	int t;
	int basis=b[begin];
	int flag=1;
	printSort(b);
	do
	{
	for(int i=begin+1;i<end;i++)
	{
		if(basis<b[i])
		{
			max=i;
			break;
		}
	}
	for(int i=end-1;i>begin;i--)
	{
		if(basis>b[i])
		{

			min=i;
			break;
		}
	}
	t=b[max];
	b[max]=b[min];
	b[min]=t;
	if(max-min==1)
	{
		t=b[begin];
		b[begin]=b[min];
		b[min]=t;
		flag=0; 
	}

	}while(flag)
	Quick(b,begin,min);
	Quick(b,max,end);
}
int Simple_select_sort(int *a,int n)
{
	int b[Maxsize];
	for(int pp=0;pp<end;pp++)
	{
		b[pp]=a[pp];//就一个数组可以完成
	}
	int t;
	int o=0;
	for(int i=0;i<n;i++)
	{
		cout<<"第"<<o<<"次；";
		printSort(b,n);
		cout<<endl;
		int j=b[i];
		int flag;
		for(int k=i+1;k<n;k++)
		{
			if(j>b[k])
			{
				flag=k;
				j=b[k];
			}
		}
		t=b[i];
		b[i]=j;
		b[flag]=t;
	}	
	for(int i=0;i<n;i++)
	{

	}
	return 0;
}
int heap_sort(int *a,int n)//参考书中内容
{
	int i;
	int temp;
	for(i=len/2;i>=2;i--)
	{
		HeapAdjust(a,i,len);
	}
	for(i=len;i>=2;i--)
	{
		temp=a[1];
		a[1]=a[i];
		HeapAdjust(a,1,i-1);
	}
}
int HeapAdjust(int a,int s,int t)
{
	int i,j;
	i=s,j=2*i;
	int temp;
	temp=a[s];
	while(j<=t)
	{
		if(j<t&&a[j]<a[j+1])
			j++;
		if(temp<a[j])
		{
			a[i]=a[j];
			i=j;
			j=2*i;

		}
		else 
			break;
	}
	a[i]=temp;
	return 0;
}
void Merge_sort(int *a,int len)//参考书中内容
{
	int length,k,i=1,j;
	for(length=1;length<len;length=2*length)
	{
		for(j=0;j+2*length-1<len;j=j+2*length)
		{
			Merge(a,j,j+length,j+2*length-1);

		}
		if(j+length-1<len)
		{
			Merge(a,j,j+length-1,j-1);
		}
		printf("第%d趟排序\n", i++);
		for(k=0;k<len;k++)
			cout<<a[k];
		cout<<endl;
	}
}
void Merge(int *a,int low,int mid,int high)
{
	int B[Maxsize];
	int i=low,j=mid+1,k=0;
	while(i<=mid&&j<=high)
	{
		if(a[i]<=a[j])
		{
			B[k]=a[i];
			i++;
			k++;
		}
		else
		{
			B[k]=a[i];
			j++;
			k++;
		}
	}
	while(i<=mid)
	{
		B[k]=a[i];
		i++;
		k++;

	}
	while(j<=high)
	{
		B[k]=a[j];
		j++;
		k++;
	}
	for(k=0,i=low;i<=high;k++,i++)
	{
		a[i]=B[k];
	}
}
#define maximun 10
void Cardinal_sort(int *a,int len)//参考书中内容
{
	int i,j,k,index,no;
	int max=0;
	int level;
	int nocount[10];
	for(i=0;i<10;i++)
		nocount[i]=0;
	int noarray[10][maximun];
	max=GetMazValue(a,len);
	level=MaxLevel(max);
	for(i=0;i<=level;i++)
	{
		for(j=0;j<=9;j++)
		{
			nocount[j]=0;
		}
		for(j=0;j<maximun;j++)
		{
			no=digitk(a[j],i);
			noarray[no][nocount[no]]=a[j];
			nocount[no]=nocount[no]+1;	
		}
		index=0;
		for(j=0;j<=9;j++)
		{
			for(k=0;k<nocount[j];k++)
			{
				a[index]=noarray[j][k];
				index;
			}
		}
		cout<<"第"<<i+1<<"趟排序:"
		for(j=0;j<len;j++)
			cout<<a[j];
		cout<<endl;
	}
}
int digitk(int data,int th)
{
	int i,j,k;
	if(th==0)
		return data%10;
	else
	{
		for(i=0;i<th;i++)
		{
			if(i==0)
				k=10;
			else
				k=k*10;
		}
		i=((int)(data/k)%10);
		return i;
	}
}
int MaxLevel(int level)
{
	int i=0;
	value =value/10;
	while(value>1)
	{
		value=value/10;
		i++;
	}
	return i;
}
int main()
{
	int a[Maxsize];
	cout<<"输入总共数量"<<endl;
	int n;
	cin>>n;
	cout<<"请输入数据"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	int choice=10;
	while(choice)
	{
		cout<<"请选择排序方式"<<endl;
		cout<<"1：直接插入排序\n2；希尔排序\n3；冒泡排序\n4；快速排序\n5；简单选择排序\n6；堆排序\n7；归并排序\n；8；基数排序\n0；表示退出"
		

		cin>>choice;
		switch (choice){
			case 1:Derect_insertion_sort(a,n);break;
			case 2:Hill_sort(a,n);break;
			case 3:Bubble_sort(a,n);break;
			case 4:Quick_sort(a,0,n);break;
			case 5:Simple_select_sort(a,n);break;
			case 6:heap_sort(a,n);break;
			case 7:Merge_sort(a,n);break;
			case 8:Cardinal_sort(a,n);break;
			case 0:break;
			default :cout<<"there is a error,please input a number again\n";
		}
		 
	}


}