////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：利用二叉链表示二叉树，完成下列操作：
//          1、根据二叉树的中序、先序序列创建二叉树，并返回根节点指针；
//          2、利用递归算法输出根节点到所有叶子节点的路径；
//          3、利用非递归算法输出根节点到所有叶子节点的路径；
//          4、利用递归算法，寻找距离两个指定节点（互相不为对方的祖先）最近的共同祖先，返回该祖先指针；
//          5、按层次分行输出二叉树的节点数据（每层结点单独一行显示），并判断该二叉树是否为完全二叉树
//          6、销毁以指定节点为根节点的子树；
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define N 30

typedef struct node
{
	char data;
	struct node *left,*right;	
}BT;

typedef struct
{
	BT *t[N];
	int top;
}ST;
char stack[N];
int top=0;
int menu_select();

BT *createtree(char *in,char *pre,int k);//根据二叉树的中序和先序序列创建二叉树，k表示字符串in的长度
void showtree(BT *T);//用括号的形式输出二叉树
void getpath1(BT *T);//递归算法输出根节点到所有叶子节点的路径
void getpath2(BT *T);//非递归算法输出根节点到所有叶子节点的路径
BT *delsubtree(BT *T,char s);//找到包含数据为s的节点，并删除以该节点为根的子树，最后返回根节点（因为这个删除也可能会删除整个树）
BT *getcomances(BT *T,char s1,char s2);//寻找距离两个指定节点s1和s2（互相不为对方的祖先）最近的共同祖先，返回该祖先指针
int layervisit(BT *T);//层次遍历二叉树，逐行输出节点数据，并判断该二叉树是否为完全二叉树，如果是，返回1，否则返回0





int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.创建二叉树\n");
		printf("2.显示二叉树\n");
		printf("3.输出根节点到所有叶子节点的路径\n");
		printf("4.寻找距离两个节点最近的共同祖先\n");
		printf("5.层次遍历二叉树\n");	
		printf("6.销毁以指定节点为根节点的子树\n");	
		printf("0.exit\n");
		printf("Please input index(0-6):");
		i=getchar();		
	}while(i<'0' || i>'6');
	return (i-'0');	
}



main()
{
	BT *T=NULL,*p=NULL;
	char in[]="GBEHDFAC",pre[]="ABGDEHFC";//已知二叉树的中序和先序序列
	char s;
	int k=strlen(in);//k表示中序序列长度
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
            T=createtree(in,pre,k);
			if(T)
				printf("创建成功\n");
			else
				printf("创建不成功\n");
			system("pause");
			break;
		case 2:
			if(!T)
				printf("树是空树\n");
			else
				showtree(T);
			printf("\n");
			system("pause");				
			break;
		case 3:			    			
			printf("\n递归算法得到根节点到所有叶子节点的路径：\n");
			top=0;
			getpath1(T);
			printf("\n非递归算法得到根节点到所有叶子节点的路径：\n");
			getpath2(T);
			system("pause");		
			break;
		case 4:			    
			p=getcomances(T,'H','F');//寻找距离H和F节点最近的共同祖先
	        printf("\n距离 H 和 F 最近的共同祖先是： %c\n",p->data);//输出找到的祖先节点数据，应该是D
	        p=getcomances(T,'H','G');//寻找距离H和G节点最近的共同祖先
	        printf("\n距离 H 和 G 最近的共同祖先是： %c\n",p->data);//输出找到的祖先节点数据，应该是B
			system("pause");
			break;
		case 5:	
			printf("\n二叉树层次遍历结果：\n");
			if(layervisit(T))
				printf("该二叉树是完全二叉树\n");
			else
				printf("该二叉树不是完全二叉树\n");
			system("pause");
			break;
		case 6:	
			T=delsubtree(T,'D');//删除以D作为根节点的子树
			printf("\n删除以D为根节点的子树后，树变为:\n",s);
			if(!T)
				printf("树为空\n");
			else
	            showtree(T);//显示删除后的树
			system("pause");
			break;		
		case 0:
			 printf("GOOD BYE\n");
			 system("pause");
				exit(0);
		}
	}
}


BT *createtree(char *in,char *pre,int k)//根据二叉树的中序和先序序列创建二叉树，k表示字符串in的长度
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(k<=0) return NULL;
	BT *node = (BT *)malloc(sizeof(BT));
	node->data = pre[0];
	if(k==1)
	{
	 node->left = NULL;
	 node->right = NULL;
	 return node; 
	}
	int i;
	for(i=0;i<k;i++)
	{
		if(in[i]==pre[0])
			break;
	}
	node->left = createtree(in,pre+1,i);
	node->right = createtree(in+i+1,pre+i+1,k-i-1);
	return node;
}

void showtree(BT *T)//用括号的形式输出二叉树
{
	if(T)
	{
		printf("%c",T->data);
		if(T->left||T->right)
		{
			printf("(");
			showtree(T->left);
			printf(",");
			showtree(T->right);
			printf(")");
		}
	}
}


int layervisit(BT *T)//层次遍历二叉树，逐行输出节点数据，并判断该二叉树是否为完全二叉树，如果是，返回1，否则返回0
{

////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	int head=0,tail=0;
	int ans=1,flag=0;
	BT queue[2*N];
	queue[tail++]=*T;
	while(head!=tail)
	{
		BT t = queue[head++];
		printf("%c ",t.data);
		flag=1;
		if(t.left)
		{
			queue[tail++]=*t.left;
		}
		else
		{
			flag = -1;
		}
		if(t.right)
		{
			queue[tail++]=*t.right;
		}
		else
		{
			flag *=-1;
		}
		if(flag==-1) ans = 0;
	}
	return ans;
}


void getpath1(BT *T)//递归算法输出根节点到所有叶子节点的路径
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(T->left==NULL&&T->right==NULL)
	{
		int i;
		for(i=0;i<top;i++)
			printf("%c->",stack[i]);
		printf("%c\n",T->data);
		return;
	}
	stack[top++] = T->data;
	if(T->left)
	{
		getpath1(T->left);
	}
	if(T->right)
	{
		getpath1(T->right);
	}
	top--;
}

void getpath2(BT *T)//非递归算法输出根节点到所有叶子节点的路径
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	ST stack1;
	stack1.top=0;
	int flag=0;
	BT *p,*p1=NULL;
	int i;
	p=T;
	do
	{
		while(p!=NULL)
		{
			stack1.t[stack1.top++]=p;
			p=p->left;
		}
		p1=NULL;
		flag=1;
		while(stack1.top&&flag)
		{
			p=stack1.t[stack1.top-1];
			if(p->right==p1)
			{
				if(p->left==NULL&&p->right==NULL)
				{
					for(i=0;i<stack1.top-1;i++)
						printf("%c->",stack1.t[i]->data);
					printf("%c\n",stack1.t[stack1.top-1]->data);
				
				}
				stack1.top--;
				p1=p;
			}
			else
			{
				p=p->right;
				flag=0;
			}
		}
	}while(stack1.top);
	
}


BT *deltree(BT *T)
{
	if(!T) return NULL;
	T->left=deltree(T->left);
	T->right=deltree(T->right);
	free(T);
	return NULL;
 } 
BT *delsubtree(BT *T,char s)//找到包含数据为s的节点，并删除以该节点为根的子树，最后返回根节点（因为这个删除也可能会删除整个树）
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(T->data==s) return deltree(T);
	if(T->left)
		T->left = delsubtree(T->left,s);
	if(T->right)
		T->right = delsubtree(T->right,s);
	return T;	
}


int Finds(BT *T,char s)
{
	if(!T) return 0;
	if(T->data == s)
		return 1;
	return Finds(T->left,s) | Finds(T->right,s);
}

BT *getcomances(BT *T,char s1,char s2)//寻找距离两个指定节点s1和s2（互相不为对方的祖先）最近的共同祖先，返回该祖先指针
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(T->data==s1||T->data==s2) return T;
	int pos1 = Finds(T->left,s1);
	int pos2 = Finds(T->left,s2);
	if(pos1+pos2==0)
	{
		return getcomances(T->right,s1,s2);
	}
	else if(pos1+pos2==1)
	{
		return T;
	}
	else
	{
		return getcomances(T->left,s1,s2);
	}
}







