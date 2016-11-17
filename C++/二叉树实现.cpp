#include <iostream>
#include <stack>
//实验数据7
//31 4 33 1 10 32 40
using namespace std;
typedef struct Tree
{
	int data;
	Tree *left;
	Tree *right;
}BinaryTree;
BinaryTree * BuildATree()
{
	BinaryTree * PrimitiveTree = (BinaryTree *)malloc(sizeof(BinaryTree));
	cout << "input the number of Treeleaf" << endl;
	int n = 0;
	cin >> n;
	int data = 0;
	cin >> data;
	PrimitiveTree->data = data;
	PrimitiveTree->left = NULL;
	PrimitiveTree->right = NULL;
	BinaryTree *currentTree;
	currentTree = PrimitiveTree;
	for (int i = 0; i<n - 1; i++)
	{
		BinaryTree *newTree = (BinaryTree *)malloc(sizeof(BinaryTree));
		cin >> data;
		currentTree = PrimitiveTree;
		while (1)
		{
			if (data >= currentTree->data)
			{
				//currentTree = currentTree->right;
				if (currentTree->right == NULL)
				{
					currentTree->right = newTree;
					newTree->data = data;
						newTree->left = NULL;
					newTree->right = NULL;
					break;
				}
				currentTree = currentTree->right;
				//newTree->data = data;
				//newTree->left = NULL;
				//newTree->right = NULL;
				//currentTree = newTree;

			}
			else
			{
				if (currentTree->left == NULL)
				{
					currentTree->left = newTree;
					newTree->data = data;
					newTree->left = NULL;
					newTree->right = NULL;
					break;
				}
				currentTree = currentTree->left;
				//newTree->data = data;
				//newTree->left = NULL;
				//newTree->right = NULL;
				//currentTree = newTree;
			}

		}

	}
	return PrimitiveTree;

}
bool Preorder(BinaryTree *root)//前序遍历

{
	if (root == NULL)return 0;
	stack <BinaryTree *> login;
	login.push(root);
	BinaryTree *ptr = root;
	while (!login.empty())
	{
		ptr = login.top();
		cout << ptr->data << endl;
		login.pop();
		if (ptr->right != NULL)
			login.push(ptr->right);
		if (ptr->left != NULL)
			login.push(ptr->left);
	}
	return 1;
}
bool postorder(BinaryTree *root)//前序遍历
{
	if (root == NULL)return 0;
	stack<BinaryTree *> log;
	BinaryTree *ptr = root;
	//log.push(root);
	while (!log.empty() || ptr != NULL)
	{
		if (ptr != NULL)
		{
			log.push(ptr);
			ptr = ptr->left;
		}
		else
		{
			ptr = log.top();
			log.pop();
			cout << ptr->data << endl;
			ptr = ptr->right;
		}

	}
	return 1;
}
bool real_postorder(BinaryTree *root)//后序遍历
{
	if (root == NULL)return 0;
	stack<BinaryTree *>log;
	log.push(root);
	BinaryTree * logg, *flag;
	//logg=root;
	flag = root;
	int i = 0;
	while (!log.empty())
	{
		//int i = 0;
		logg = log.top();
		//if ((logg->left == NULL&&logg->right == NULL )|| (logg->left == flag&&logg->right == NULL) || (logg->right == flag&&logg->left== NULL))
		if((logg->left == NULL&&logg->right == NULL) || logg->left == flag || logg->right == flag)
		{
			cout <<i<< ":";
			i++;
			cout << logg->data << endl;
			
			flag = logg;
			log.pop();
		}
		else {


			if (logg->right != NULL)
			{
				log.push(logg->right);
			}
			if (logg->left != NULL)
			{
				log.push(logg->left);
			}
		}
	}
	return 1;
}
int NodeNumber(BinaryTree *root)//计算结点数量
{
	BinaryTree *root1;
	int number;
	queue<BinaryTree*>Tree;
	Tree.push(root);
	root1=root;
	number=1;
	while(!Tree.empty())
	{
		if(root1->left!=NULL)
		{
			Tree.push(root1->left);
			number++;
		}
		if(root1->right!=NULL)
		{
			Tree.push(root1->right);
			number++;
		}
		Tree.pop();
	}
	return number;
}
int main(int argc, char const *argv[])
{
	BinaryTree *FirstTree;
	FirstTree = BuildATree();
	//Preorder(FirstTree);
	//postorder(FirstTree);
	cout<<NodeNumber(FirstTree)<<endl;
	system("pause");
	return 0;
}