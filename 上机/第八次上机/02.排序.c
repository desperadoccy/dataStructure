///////////////////////////////////////////////////////////////////////////////////////////
//题目要求：随机生成n个整数（可能会有重复元素），请利用BST设计高效算法，按降序有序的
//          顺序输出所有大于等于k的数据
//          1、自行设计BST的数据结构，自行设计需要的其余的功能函数，不要修改main函数
//          2、数据规模n以及k均从键盘输入
//          3、随机生成的数据，数值不要超过100，方便调试和观察结果，不要以此为条件设计算法        
//          
////////////////////////////////////////////////////////////////////////////////////////////
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define N 100

typedef struct node
{
	int data;
	struct node *left,*right;
}BST;

BST *createbst(int n);//创建BST
BST *insnode(BST *T,int x);//在BST中插入数据点x,并返回根节点指向
BST *delbst(BST *T);//销毁BST
void output(int n,int k);//在n个随机数中，利用BST，按降序有序的顺序输出所有大于等于k的数据


main()
{
	int n,k;
	printf("请输入数据规模n以及需要查找的有序序列的最小值k:\n");
	scanf("%d%d",&n,&k);
	while(n>0&&k>0)
	{
		printf("所有大于等于%d的数据有:\n",k);
		output(n,k);		
		printf("请输入数据规模n以及需要查找的有序序列的最大值k:\n");
	    scanf("%d%d",&n,&k);
	}
}

BST *createbst(int n)
{
	int i,x;
	BST *T=NULL;
	srand(time(0));
	for(i=0;i<n;i++)
	{
		x=rand()%23;//随机生成的数据均小于23，方便调试，这个可以自行调整
		T=insnode(T,x);
	}
	return T;
}

BST *delbst(BST *T)//销毁BST
{
	if(!T)
		return NULL;
	else
	{
		T->left=delbst(T->left);
		T->right=delbst(T->right);
		free(T);
		return NULL;
	}
}

BST *insnode(BST *T,int x)//在BST中做插入，并返回根节点指向
{
/////////////////////////////complete this////////////////////////////////
	if(!T)
	{
		T=(BST *)malloc(sizeof(BST));
		T->left=T->right=NULL;
		T->data=x;
	}
	else if(T->data==x)
	{
		return T;
	}
	else if(T->data<x)
	{
		T->right=insnode(T->right,x);
		return T;
	}
	else if(T->data>x)
	{
		T->left=insnode(T->left,x);
		return T;
	}

	
}

void output(int n,int k)
{
///////////////完成该函数////////////////////////////////////
	BST *T;
	T = createbst(n);
	BST *stack[N];
	int top = 0;
	BST *p = T;
	while(p || top)
	{
		while(p)
		{
			stack[top++] = p;
			p = p->right;
		}
		if(top)
		{
			p = stack[--top];
			if(p->data<k) break;
			printf("%d ",p->data);
			p = p->left;
		}
	}
	printf("\n");
}
