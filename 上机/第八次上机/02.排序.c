///////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ���������n�����������ܻ����ظ�Ԫ�أ���������BST��Ƹ�Ч�㷨�������������
//          ˳��������д��ڵ���k������
//          1���������BST�����ݽṹ�����������Ҫ������Ĺ��ܺ�������Ҫ�޸�main����
//          2�����ݹ�ģn�Լ�k���Ӽ�������
//          3��������ɵ����ݣ���ֵ��Ҫ����100��������Ժ͹۲�������Ҫ�Դ�Ϊ��������㷨        
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

BST *createbst(int n);//����BST
BST *insnode(BST *T,int x);//��BST�в������ݵ�x,�����ظ��ڵ�ָ��
BST *delbst(BST *T);//����BST
void output(int n,int k);//��n��������У�����BST�������������˳��������д��ڵ���k������


main()
{
	int n,k;
	printf("���������ݹ�ģn�Լ���Ҫ���ҵ��������е���Сֵk:\n");
	scanf("%d%d",&n,&k);
	while(n>0&&k>0)
	{
		printf("���д��ڵ���%d��������:\n",k);
		output(n,k);		
		printf("���������ݹ�ģn�Լ���Ҫ���ҵ��������е����ֵk:\n");
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
		x=rand()%23;//������ɵ����ݾ�С��23��������ԣ�����������е���
		T=insnode(T,x);
	}
	return T;
}

BST *delbst(BST *T)//����BST
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

BST *insnode(BST *T,int x)//��BST�������룬�����ظ��ڵ�ָ��
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
///////////////��ɸú���////////////////////////////////////
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
