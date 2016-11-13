#include <iostream>
#include <stack>
using namespace std;
typedef struct Tree
{
	int data;
	Tree *left;
	Tree *right;
}BinaryTree;
BinaryTree * BuildATree()
{
	BinaryTree * PrimitiveTree=(BinaryTree *)malloc(sizeof(BinaryTree));
	cout<<"input the number of Treeleaf" <<endl;
	int n=0;
	cin>>n;
	int data=0;
    cin>>data;
	PrimitiveTree->data=data;
	PrimitiveTree->left=NULL;
	PrimitiveTree->right=NULL;
	BinaryTree *currentTree;
	currentTree=PrimitiveTree;
	for(int i=0;i<n;i++)
	{
		BinaryTree *newTree = (BinaryTree *)malloc(sizeof(BinaryTree));
		cin>>data;
		if(data>=currentTree->data)
		{
			currentTree->right=newTree;
			newTree->data=data;
			newTree->left=NULL;
			newTree->right=NULL;
			currentTree=newTree;

		}
		else
		{
			currentTree->left=newTree;
			newTree->data=data;
			newTree->left=NULL;
			newTree->right=NULL;
			currentTree=newTree;
		}

	}
	return PrimitiveTree;

}
BinaryTree* Preorder(BinaryTree *root)
{
	if(root==NUll)return NUll;
	stack <BinaryTree *> login;
	login.push(root);
	BinaryTree *ptr=root;
	while(!s.empty())
	{
		ptr=login.top()
		cout<<ptr->data<<endl;
		login.pop();
		if(ptr->)
		login.push()
	}

}
int main(int argc, char const *argv[])
{
	BinaryTree *FirstTree;
	FirstTree =BuildATree();
	Preorder(FirstTree);
	return 0;
}