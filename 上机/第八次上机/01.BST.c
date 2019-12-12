///////////////////////////////////////////////////////////////////////////////////////////
//题目要求：在BST中做处理
//          1、根据系统随机生成的数据创建BST；
//          2、计算该BST的平均查找长度ASL（等概率，查找成功的）；
//          3、在BST中做删除
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
BST *delnode(BST *T,int x);//在BST中删除包含x的节点，并返回根节点指向
void showbst(BST *T);//显示BST
float comasl(BST *T);//计算并返回等概率查找下，该BST的平均查找长度
BST *delbst(BST *T);//销毁BST

main()
{
	int i,n,x;
	BST *T=NULL;
	printf("请输入数据规模：\n");
	scanf("%d",&n);
	while(n>0)
	{
		T=createbst(n);//创建BST
		printf("创建好的BST为：\n");
		showbst(T);//显示BST
		printf("\n\n该BST查找成功的平均查找长度=%.2f\n\n",comasl(T));//计算BST查找成功的ASL
		for(i=1;T&&i<=4;i++)
		{
//////////////////////做连续四次的删除，待删除数据随机生成///////////////////////////////////////////////
			x=rand()%23;
			printf(" \n删除数据%d后，BST为：\n",x);	
			T=delnode(T,x);//在BST中做删除
			showbst(T);
			printf("\n\n");	
		}
		T=delbst(T);//销毁BST
		printf("请输入数据规模：\n");
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

BST *delnode(BST *T,int x)//在BST中做删除并返回根节点指向。如果x不存在，给出提示信息“该数据不存在”
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

void showbst(BST *T)//显示BST
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
float comasl(BST *T)//计算BST的平均查找长度
{
/////////////////////////////complete this////////////////////////////////
	float length=0;
	float cnt=0,ans;
	search(T,&length,&cnt,1);
	ans=length/cnt;
	return ans;
}

