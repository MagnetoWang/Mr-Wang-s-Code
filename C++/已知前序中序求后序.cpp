#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#define MaxSize 20
using namespace std;
//GDAFEMHZ
//ADEFGHMZ
int main()
{
	//stack <char> PostOrder;
	//stack <int> LeftTree,LeftLength,Leftrear,Leftfront;
	stack<int> LeftTree, RightTree;
	queue<char> PostOrder;
	vector<int> Root;
	//Root.assign(MaxSize, 0);
	char preorder[MaxSize];
	char inorder[MaxSize];
	cout << "输入字符个数" << endl;
	int n;
	cin >> n;
	
	cout << "输入前序" << endl;
	for (int i = 0; i<n; i++)
	cin >> preorder[i];
	cout << "输入中序" << endl;
	for (int i = 0; i < n; i++)
	cin >> inorder[i];
	int pre = 0;
	int width = 0;
	//Leftfront.push(0);
	//int LeftLength;
	//	while(PostOrder.size()==n)
	//	{
	int n1 = n;
	for (pre = 0; pre < n; pre++)
	{
		for (int i = 0; i < n1; i++)
		{
			if (Root.size() != 0)
			{
				if (pre == Root.at(0))
				{
					PostOrder.push(inorder[i]);
					while (!LeftTree.size())
					{
						PostOrder.push(preorder[LeftTree.top()]);
						LeftTree.pop();
						Root.pop_back();
					}
					Root.front() = n;
					continue;
				}
			}
			if (preorder[pre] == inorder[i])
			{
				if (Root.size() != 0)
				{
					if (i == Root.at(0) - 1)
					{
						Root.push_back(i);
						break;
					}
					
					if (inorder[i + 1] == inorder[Root.back()])
					{
						PostOrder.push(inorder[i]);
						LeftTree.pop();
						LeftTree.push(pre + 1);
						break;
					}
				}
				

				RightTree.push(i + 1);
				LeftTree.push(pre + 1);
				Root.push_back(i);
				break;

			}

		}

		/*		if(preorder[pre]==inorder[i])
		{
		//width++;
		if(i==n-1)
		{
		//width++;
		PostOrder(preorder[pre]);
		n=Leftrear.top()+1;
		i=Leftfront.top();
		pre=LeftTree.top();
		Leftfront.pop();
		Leftrear.pop();
		LeftTree.pop();
		//LeftLength.pop();

		continue;
		}
		//LeftLength.push(i- Leftfront.top());
		LeftTree.push(pre+1);
		Leftfront.push(pre);
		PostOrder.push(preorder[pre]);
		Leftrear.push(i-1);
		//Leftfront.push(i+1);
		pre=pre+Leftrear.top()-Leftfront.top()+2;
		}*/


	}

	for (int i = 0; i < PostOrder.size(); i++)
	{
		cout << PostOrder.front()<<endl;
		PostOrder.pop();
	}
	system("pause");
}
//GDAFEMHZ
//ADEFGHMZ
//8


