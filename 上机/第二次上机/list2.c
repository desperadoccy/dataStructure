////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：三个有序单向链表A,B,C（升序有序，均无重复元素）。请设计高效计算法求取三个链表的交集元素，A=common(A,B,C) 
//          要求处理后链表A依然升序有序，并且没有重复元素，链表B和C保持不变。要求空间复杂度为O(c)
//          
//学   号： 161830218                                                                                                 
//姓   名： 陈楚燚                                                                                                  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////




#include "stdlib.h"
#include "math.h"
#include "stdio.h"


typedef struct node
{
	int data;
	struct node *next;
}LI;

void createlist(LI *head,int n);//根据n各随机数创建一个有序链表
void showlist(LI *head);//显示链表内容
void dellist(LI *head);//销毁链表
void insertdata(LI *head,int data);//在有序链表中插入一个数据，插入后链表依然有序
void getcommon(LI *A,LI *B,LI *C);//将三个有序链表A，B和C合并，结果存放在链表A中，B，C保持不变
main()
{
	LI *A, *B,*C;
	int m, n,p;
	A=(LI*)malloc(sizeof(LI));
	B=(LI*)malloc(sizeof(LI));
	C=(LI*)malloc(sizeof(LI));
	A->next=B->next=C->next=NULL;
	printf("please input sizeof list A , B and C:\n");
	scanf("%d%d%d", &m, &n,&p);
	while (n > 0 && m > 0&&p>0)
	{
		createlist(A,m);
		createlist(B,n);
		createlist(C,p);
		printf("the original list A :\n");
		showlist(A);
		printf("the original list B :\n");
		showlist(B);
		printf("the original list C :\n");
		showlist(C);
		getcommon(A,B,C);
		printf("the merge list is:\n");
		showlist(A);
		printf("please input sizeof list A , B and C:\n");
	    scanf("%d%d%d", &m, &n,&p);
		dellist(A);	
		dellist(B);		
		dellist(C);		
	}
}

void createlist(LI *head,int n)
{
	int i,x;
	for(i=0;i<n;i++)
	{
		x=rand()%29;//随机生成的数据不超过29，这个值可以自行调整
		insertdata(head,x);
	}	
}
void showlist(LI *head)
{
	LI *p;
	int i=0;
	p=head->next;
	if(!p)
	{
		printf("the list is empty\n");
		return;
	}
	while(p)
	{
		printf("%4d",p->data);
		p=p->next;
		i++;
		if(i%15==0)
			printf("\n");
	}
	printf("\n\n");
}
void dellist(LI *head)
{
	LI *p,*p2;//p指向当前遍历节点,p2指向p 的后继
	p=head->next;
	head->next=NULL;
	while(p)
	{
		p2=p->next;
		free(p);
		p=p2;
	}
}
void insertdata(LI *head,int data)
{
	LI *p1,*p,*q;//p指向当前遍历节点,p1指向p的前驱,q指向新生成的将要插入的节点
	p1=head;p=p1->next;
	while(p)
	{
		if(p->data<data)
		{
			p1=p;
			p=p->next;
		}
		else
			break;
	}
	if(p&&p->data==data)//重复出现的数据不做插入
		return;
	else
	{
		q=(LI *)malloc(sizeof(LI));
		q->data=data;
		p1->next=q;
		q->next=p;
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  A,B,C表示三个升序有序链表的表头,求三个链表的交集，结果存放在链表A中
//
//  要求：处理过后链表A升序有序并且没有重复元素；链表B和C保持不变；
//        空间复杂度为O（1），将A中的非交集结点删除并释放即可      
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getcommon(LI *A,LI *B,LI *C)
{
	LI *pa,*pb,*pc; //分别表示A，B，C当前遍历的节点
	LI *pa0; //pa0表示pa的前驱 
	pa0 = A;
	pa = A->next;
	pb = B->next;
	pc = C->next;
	while(pa&&pb&&pc)
	{
		if(pa->data==pb->data&&pa->data==pc->data)
		{
			pa0 = pa; 
			pa = pa->next;
			pb = pb->next;
			pc = pc->next;
		}
		else
		{
			if(pa->data<=pb->data&&pa->data<=pc->data)
			{
				pa0->next = pa->next;
				pa = pa->next;
			}
			else if(pb->data<=pc->data&&pb->data<=pa->data)
			{
				pb = pb->next;
			}
			else if(pc->data<=pb->data&&pc->data<=pa->data)
			{
				pc = pc->next;
			}
		}
	}
	pa0->next = NULL;
}
