#include <iostream>
using namespace std;
typedef struct TreeNode{
	int data;
	TreeNode *left,*right;
}
TreeNode * insert_node(TreeNode * root,int d)
{
	TreeNode * newNode;
	TreeNode*currentnode;
	TreeNode *parrentnode;
	newNode=(TreeNode*)malloc(sizeof(TreeNode));
	newNode->data=d;
	newNode->right=NULL;
	newNode->left=NULL;
	if(root==NULL)
		return newNode;
	else
	{
		currentnode=root;
		while(currentnode!=NULL)
		{
			parrentnode=currentnode;
			if(currentnode->data>d)
			{
				currentnode=currentnode->left;
			}
			else
			{
				currentnode=currentnode->right;
			}
		}
		if(parrentnode->data>d)
			parrentnode->left=newNode;
		else
			parrentnode->right=newNode;
	}
}//从这个函数看，插入一个节点，需要注意插入的位置，根节点还是尾节点，这里有点意思的是while循环
//似乎要不停到最后为null的指针处。这里不是很理解。以后再回来看看吧
TreeNode * FindNode(TreeNode * root,int x)
{
	TreeNode *p;
	if(root==NULL)
	{
		return NULL;
	}
	else 
		if(root->data==x)
			return root;
		else
		{
			p=FindNode(root->left,x);
			if(p!=NULL)
				return p;
			else
				return FindNode(root->right,x);
		}
}
//这里使用迭代的方式寻找结点。我觉得效率不高。不好
//返回左右孩子的结点
TreeNode * LeftNode(TreeNode *root,int x)
{
	if(x==0)
	     return root->left;
    else
    	return root->right;
}
//计算树的深度
int BTDepth(TreeNode * root)
{
	int LDepth,RDepth;
	if(root==NULL)
		return 0;
	else
	{
		LDepth=BTDepth(root->left);
		RDepth=BTDepth(root->right);
		return max(LDepth+1,RDepth+1);
	}
}
//这里双重递归，我有点弄混。不太形象啊，尤其是赋值那里。
//遍历（TRAVERSAL)
//先序，中序，后序遍历
void preorder(TreeNode *root)
{
	if(root!=NULL)
	{
		printf("%d\n",root->data );
		preorder(root->left);
		preorder(root->right);
	}
}
void inorder(TreeNode *root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		cout<<root->data;
		inorder(root->right);
	}
}
void postorder(TreeNode * root)
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout<<root->data;
	}
}
//求叶子结点数, 递归方式求叶子，到底返1,即可
int leaf(TreeNode * root)
{
	int L,R;
    if(root==NULL)
    	return 0;
    if(root->left==NULL&&root->right==NULL)
    	return 1;
    L=leaf(root->left);
    R=leaf(root->right);
    return L+R;
}
//先序遍历复制二叉树
TreeNode *CopyTree(TreeNode *root)
{
	TreeNode *newNode;
	if(root==NULL)
		return NULL;
	else
	{
		newNode=(TreeNode*)malloc(sizeof(TreeNode));
		newNode->data=root->data;
		newNode->left=CopyTree(root->left);
		newNode->right=CopyTree(root->right);
		return newNode;
	}
}
//二叉树比较，通过数据对比即可
int CompareBTree(TreeNode * root1,TreeNode *root2)
{
	if(root1==NULL||root2==NULL)
	{
		return 1;

	}
	else 
		if(root1->data==root2->data)
		{


		if (CompareBTree(root1->left,root2->left))
		{
			return CompareBTree(root1->right,root2->right);
		}
	}
		else
			return 0;
}
//左右树交换
TreeNode *mirror(TreeNode *root)
{
	TreeNode *mirtree;
	if(root==NULL)
	{
		return NULL;
	}
	else
	{
		mirtree=(TreeNode *)malloc(sizeof(TreeNode));
		mirtree->data=root->data;
		mirtree->left=mirror(root->right);
		mirtree->right=mirror(root->left);
	}
	return mirtree;
}
//以上为二叉树的基本函数操作，仅供参考
//下面将要介绍线索二叉树的使用函数
typedef struct thread_tree
{
	DataType data;
	struct thread_tree *right,*left;
	int lthread,rthread;
}ThreadTree;
//将二叉树线索化
ThreadTree *InsertNode(ThreadTree *root,int nodedata)
{
	ThreadTree *newnode,*currentnode,*parrentnode;
	ThreadTree *prenode//前趋结点指针
	int position;
	newnode=(ThreadTree *)malloc(sizeof(ThreadTree));
	newnode->data=nodedata;
	newnode->left=NULL;
	newnode->right=NULL;
	newnode->rthread=1;
	newnode->lthread=1;
	currentnode=root->left;
	if(currentnode==NULL)
	{
		root->left=newnode;
		newnode->left=root;
		newnode->right=root;
		return root
	}
	parrentnode=root;
	position=0;
	while(currentnode!=NULL)
	{
		if(nodedata<currentnode->data)
		{
			position=-1;
			prenode=parrentnode;

		}
		parrentnode=currentnode;
		if(currentnode->lthread==0)
			currentnode=currentnode->left;
		else
			currentnode=NULL;
	
	else
	{
		if(position!=-1)
		{
			position=-1;
			prenode=parrentnode;
		}
		parrentnode=currentnode;
		if(currentnode->rthread==0)
		{
			currentnode=currentnode->right;
		}
		else
			currentnode=NULL;
	}

    }
    if(nodedata<parrentnode->data)
    {
    	parrentnode->lthread=0;
    	parrentnode->left=newnode;
    	newnode->left=prenode;
    	newnode->right=parrentnode;
    }
    else
    {
    	parrentnode->rthread=0;
    	parrentnode->right=newnode;
    	newnode->left=parrentnode;
    	newnode->right=prenode;
    }
    return root;
}

int main()
{

}