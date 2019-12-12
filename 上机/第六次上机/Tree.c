////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：利用孩子-兄弟法表示树，完成下列操作：
//          
//          1、以括号的形式显示树；A(B(E,F),C,D(G(H,I,J)))
//          2、利用递归算法输出根节点到所有叶子节点的路径；
//          3、利用非递归算法输出根节点到所有叶子节点的路径；
//          4、计算树的高度；
//          5、统计树中叶子节点的数量；
//          6、层次遍历树，逐行输出各个层次的节点，并计算树的宽度（包含最多节点的层次所实际包含的节点数即树的宽度）
//          7、利用递归算法为每个节点的pa指针赋值，指向该节点的父节点
//          8、复制一个与该树一模一样的树，并返回复制树的根节点指针            
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define N 30

typedef struct node
{
	char data;
	struct node *fir,*sib;
	struct node *pa;
}TR;


int menu_select();
TR *createtree(char *pre,int *k);//根据树的先序序列（包含空格）创建二叉树，*k表示当前先序序列中的第*k个位置，该位置上
                                 //如果是空格，则返回一个空指针，如果是一个确定的字符，则创建一个节点，该节点数据为
                                 //pre[*k]，然后对(*k)++,递归的创建该节点的孩子分支，然后对(*k)++,再递归的创建它的兄弟分支，
                                 //最后返回该节点指针。（注意在该过程中不要对pa指针赋值。）

void showtree(TR *T);//用括号的形式输出树
void getpath1(TR *T);//设计递归算法输出根节点到所有叶子节点的路径
void getpath2(TR *T);//设计非递归算法输出根节点到所有叶子节点的路径
int heighttree(TR *T);///计算并返回树的高度
int leaftree(TR *T);//计算并返回树的叶子节点的数量
int layervisit(TR *T);//逐行输出树各个层次的节点,并返回树的宽度
void getpa(TR *T);//为每个节点的pa指针赋值，指向该节点的父节点，根节点的pa指向NULL
void showpa(TR *T);//显示每个节点及其父节点
TR *copytree(TR *T,TR *pa);//复制一个与该树一模一样的树，并返回复制的树的根节点指向
TR *deltree(TR *T);//销毁树




int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.创建孩子-兄弟二叉树\n");
		printf("2.显示树\n");
		printf("3.输出根节点到所有叶子节点的路径\n");
		printf("4.树的高度和叶子节点数量\n");
		printf("5.层次遍历树\n");	
		printf("6.获取pa指针\n");
		printf("7.复制树\n");
		printf("0.exit\n");
		printf("Please input index(0-7):");
		i=getchar();		
	}while(i<'0' || i>'7');
	return (i-'0');	
}



main()
{
	char pre[]="ABE F  C DGH I J     ";//已知树的先序序列(空格对应空指向)
	TR *T=NULL,*R=NULL;
	int k;
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
			k=0;
            T=createtree(pre,&k);//创建树
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
				showtree(T);//显示树
			printf("\n");
			system("pause");				
			break;
		case 3:			    			
			printf("\n递归算法得到根节点到所有叶子节点的路径：\n");
			getpath1(T);//递归算法找路径
			printf("\n非递归算法得到根节点到所有叶子节点的路径：\n");
			getpath2(T);//非递归算法找路径
			system("pause");		
			break;
		case 4:			    
			printf("\n树的高度=%d ,树中包含 %d 片叶子\n",heighttree(T),leaftree(T));//统计数的高度和叶子节点数量
	        system("pause");
			break;
		case 5:	
			printf("\n树的层次遍历结果：\n");
			k=layervisit(T);//逐行显示各个层次的节点，并返回树的宽度
			printf("\n树的宽度为：%d\n",k);
			system("pause");
			break;
		case 6:	
			getpa(T);//给每个节点的pa指针赋值
			printf("\n树的节点及其对应父节点:\n");			
	        showpa(T);//显示树的所有节点及其对应父节点
			system("pause");
			break;	
		case 7:
			R=copytree(T, NULL);//复制一个与根结点为T的树一模一样的树，将复制树的根节点指向返回赋值给R
			T=deltree(T);//销毁原树
			printf("\n复制的树：\n");
			showtree(R);//显示复制的树R
			printf("\n");
			R=deltree(R);//销毁复制的树
			system("pause");
			break;	
		case 0:
			 printf("GOOD BYE\n");
			 system("pause");
				exit(0);
		}
	}
}


TR *createtree(char *pre,int *k)//根据树的先序序列创建二叉树
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	TR *p;
	if(pre[*k]==' ')
	{
		(*k)++;
		return NULL;
	}
	else
	{
		p=(TR *)malloc(sizeof(TR));
		p->data=pre[*k];
		(*k)++;
		p->fir=createtree(pre,k);
		p->sib=createtree(pre,k);
		return p;
	}		
}

void showtree(TR *T)//用括号的形式输出二叉树
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	printf("%c",T->data);
	if(T->fir)
	{
		printf("(");
		showtree(T->fir);
		printf(")");
	}
	if(T->sib)
	{
		printf(",");
		showtree(T->sib);
	}
}

TR *a[N];
int top = 0;
void getpath1(TR *T)//递归算法输出根节点到所有叶子节点的路径
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T->fir)
	{
		int i;
		for(i = 0; i < top; i++)
			printf("%c ", a[i]->data);
		printf("%c\n", T->data);
	}
	else
	{
		a[top++] = T;
		getpath1(T->fir);
		top--;
	}
	if(T->sib)
		getpath1(T->sib);
}



TR *b[N];
int top2 = 0;
void getpath2(TR *T)//非递归算法输出根节点到所有叶子节点的路径
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return;
	TR *p = T;
	int i;
	while(p || top2)
	{
		while(p)
		{
			b[top2++] = p;
			p = p->fir;
		}
		if(top2)
		{
			p = b[--top2];
			if(!p->fir)
			{
				for(i = 0; i < top2; i++)
					printf("%c ", b[i]->data);
				printf("%c\n", p->data);
			}
			p = p->sib;
		}
	}
}

int max(int a,int b)
{
	if(a > b) return a;
	else return b;
}
int heighttree(TR *T)///计算并返回树的高度
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return 0;
	int height=1;
	if(T->fir)
	{
		height = max(heighttree(T->fir)+1,height);
	}
	if(T->sib)
	{
		height = max(heighttree(T->sib),height);
	}
	return height;
}

int leaftree(TR *T)//计算并返回树的叶子节点的数量
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return 0;
	int num=0;
	if(T->fir)
	{
		num = num + leaftree(T->fir);
	}
	else
	{
		num = 1;
	}
	if(T->sib)
	{
		num = num + leaftree(T->sib);
	}
	return num;
}

typedef struct node3
{
	TR *node;
	int	deep;
}QUE;
int layervisit(TR *T)//逐行输出树的各个层次，并返回树的宽度
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	int ans = 0;
	int width = 0,pos = 0;
	int head = 0,tail = 0;
	QUE c[N];
	c[tail].node = T;
	c[tail++].deep = 1; 
	while(head != tail)
	{
		QUE t = c[head++];
		if(t.deep != pos)
		{
			ans = max(ans,width);
			pos = t.deep;
			width = 1;
		}
		else
		{
			width++;
		}
		printf("%c", t.node->data);
		TR *tmp = t.node;
		if(t.node->fir)
		{
			c[tail].node = t.node->fir;
			c[tail++].deep = t.deep+1;
		}
		while(tmp->sib)
		{
			tmp = tmp->sib;
			width++;
			printf("%c",tmp->data);
			if(tmp->fir)
			{
				c[tail].node = tmp->fir;
				c[tail++].deep = t.deep+1;
			}
		}
	}
	return ans;
}





void getpa(TR *T)//为每个节点的pa指针赋值，指向该节点的父节点，根节点的pa指向NULL
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return;
	if(T->fir)
	{
		T->fir->pa = T;
		getpa(T->fir);
		T->fir->pa = T;
	}
	if(T->sib)
	{
		T->sib->pa = T->pa;
		getpa(T->sib);
		T->sib->pa = T->pa;
	}
	T->pa = NULL;
}




void showpa(TR *T)//显示每个节点及其父节点
{
	if(T)
	{
		if(T->pa)
			printf("%c---%c\n",T->data,T->pa->data);
		else
			printf("%c---NULL\n",T->data);
		showpa(T->fir);
		showpa(T->sib);
	}
}

TR *copytree(TR *T, TR *pa)//复制树
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return NULL;
	TR *t;
	t = (TR *)malloc(sizeof(TR));
	t->data = T->data;
	t->pa = pa;
	t->fir = copytree(T->fir, t);
	t->sib = copytree(T->sib, t);
	return t;
}

TR *deltree(TR *T)//销毁树
{
	if(T)
	{
		T->fir=deltree(T->fir);
		T->sib=deltree(T->sib);
		free(T);
		return NULL;
	}
	else
		return NULL;
}





