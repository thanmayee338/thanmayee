#include<stdio.h>
#include<stdlib.h>
struct Node
{
	int key;
	struct Node* left;
	struct Node* right;
	int height;
};
int getHeight(struct Node* n)
{
	if(n==NULL)
		return 0;
	return n->height;
}
struct Node* createNode(int key)
{
	struct Node* node=(struct Node*)malloc(sizeof(struct Node));
	node->key=key;
	node->left=NULL;
	node->right=NULL;
	node->height=1;
	return node;
}
int max(int a, int b)
{
	return(a>b) ? a:b;
}
int getBalanceFactor(struct Node* n)
{
	if(n==NULL)
		return 0;
	return getHeight(n->left)-getHeight(n->right);
}
struct Node* rightRotate(struct Node* y)
{
	struct Node* x=y->left;
	struct Node* T2=x->right;
	x->right=y;
	y->left=T2;
	y->height=max(getHeight(y->left),getHeight(y->right))+1;
	x->height=max(getHeight(x->left),getHeight(x->right))+1;
	return x;
}
struct Node* leftRotate(struct Node* x)
{
	struct Node* y=x->right;
	struct Node* T2=y->left;
	y->left=x;
	x->right=T2;
	x->height=max(getHeight(x->left),getHeight(x->right))+1;
	y->height=max(getHeight(y->left),getHeight(y->right))+1;
	return y;
	
}
struct Node* insert(struct Node* node,int key)
{
	if(node==NULL)
		return createNode(key);
	
	if(key<node->key)
		node->left=insert(node->left,key);
	else if(key>node->key)
		node->right=insert(node->right,key);
	else
		return node;
  	node->height=1+max(getHeight(node->left),getHeight(node->right));
  	int balance=getBalanceFactor(node);
  	if (balance>1 && key<node->left->key)
  		return rightRotate(node);
  	if (balance<-1 && key>node->right->key)
  		return leftRotate(node);
  	if (balance>1 && key>node->left->key)
  	{
  		node->left=leftRotate(node->left);
  		return  rightRotate(node);
	  }
	if (balance<-1 && key<node->right->key)
  	{
  		node->right=rightRotate(node->left);
  		return  rightRotate(node);
	  }
	  return node;
}
void inOrder(struct Node* root)
{
	if(root!=NULL)
	{
		inOrder(root->left);
		printf("%d",root->key);
		inOrder(root->right);
	}
}
int main()
{
	struct Node* root=NULL;
	root=insert(root,1);
	root=insert(root,2);
	root=insert(root,4);
	root=insert(root,5);
	root=insert(root,6);
	root=insert(root,3);	
	printf("Inorder traversal of AVL tree:");
	inOrder(root);
	
	return 0;
}

