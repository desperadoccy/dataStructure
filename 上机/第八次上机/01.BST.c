///////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ����BST��������
//          1������ϵͳ������ɵ����ݴ���BST��
//          2�������BST��ƽ�����ҳ���ASL���ȸ��ʣ����ҳɹ��ģ���
//          3����BST����ɾ��
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
BST *delnode(BST *T,int x);//��BST��ɾ������x�Ľڵ㣬�����ظ��ڵ�ָ��
void showbst(BST *T);//��ʾBST
float comasl(BST *T);//���㲢���صȸ��ʲ����£���BST��ƽ�����ҳ���
BST *delbst(BST *T);//����BST

main()
{
	int i,n,x;
	BST *T=NULL;
	printf("���������ݹ�ģ��\n");
	scanf("%d",&n);
	while(n>0)
	{
		T=createbst(n);//����BST
		printf("�����õ�BSTΪ��\n");
		showbst(T);//��ʾBST
		printf("\n\n��BST���ҳɹ���ƽ�����ҳ���=%.2f\n\n",comasl(T));//����BST���ҳɹ���ASL
		for(i=1;T&&i<=4;i++)
		{
//////////////////////�������Ĵε�ɾ������ɾ�������������///////////////////////////////////////////////
			x=rand()%23;
			printf(" \nɾ������%d��BSTΪ��\n",x);	
			T=delnode(T,x);//��BST����ɾ��
			showbst(T);
			printf("\n\n");	
		}
		T=delbst(T);//����BST
		printf("���������ݹ�ģ��\n");
	    scanf("%d",&n);
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

BST *searchdata(BST *T,BST **pa,int x)
{
	if(!T) return NULL;
	if(T->data==x) return T;
	else if(T->data>x)
	{
		*pa=T;
		return searchdata(T->left,pa,x);
	}
	else if(T->data<x)
	{
		*pa=T;
		return searchdata(T->right,pa,x);
	}
}

BST *delnode(BST *T,int x)//��BST����ɾ�������ظ��ڵ�ָ�����x�����ڣ�������ʾ��Ϣ�������ݲ����ڡ�
{
/////////////////////////////complete this////////////////////////////////
	BST *p,*pa=NULL;
	BST *q,*qa=NULL;
	p=searchdata(T,&pa,x);
	//if(p) printf("%d",p->data);
	if(!p)
	{
		printf("can not find\n");
		return T;
	}
	else if(!p->left&&!p->right)
	{
		if(!pa)
		{
			free(p);
			return NULL;
		}
		else if(pa->data<x)
			pa->right=NULL;
		else if(pa->data>x)
			pa->left=NULL;
		free(p);
		return T;
	}
	else if(!p->left||!p->right)
	{
		if(p->left)
		{
			if(!pa)
			{
				return p->left;
			}
			else if(pa->left==p)
			{
				pa->left=p->left;
			}	
			else
			{
				pa->right=p->left;
			}
			free(p);
			return T;
		}
		if(p->right)
		{
			if(!pa)
			{
				return p->right;
			}
			else if(pa->left==p)
			{
				pa->left=p->right;
			}
			else
			{
				pa->right=p->right;
			}
			free(p);
			return T;
		}
	}
	else
	{
		q=p->right;
		qa=p;
		while(q->left)
		{
			qa=q;
			q=q->left;
		}
		if(qa->left==q)
			qa->left=NULL;
		else
			qa->right=NULL;
		p->data=q->data;
		free(q);
		return T;
	}
	return T;
}

void showbst(BST *T)//��ʾBST
{
	if(T)
	{
		printf("%d",T->data);
		if(T->left||T->right)
		{
			printf("(");
			showbst(T->left);
			printf(",");
			showbst(T->right);
			printf(")");
		}
	}
}

void search(BST *T,float *length,float *cnt,int depth)
{
	(*length)=(*length)+depth;
	(*cnt)++;
	if(T->left)
		search(T->left,length,cnt,depth+1);
	if(T->right)
		search(T->right,length,cnt,depth+1);
}
float comasl(BST *T)//����BST��ƽ�����ҳ���
{
/////////////////////////////complete this////////////////////////////////
	float length=0;
	float cnt=0,ans;
	search(T,&length,&cnt,1);
	ans=length/cnt;
	return ans;
}

