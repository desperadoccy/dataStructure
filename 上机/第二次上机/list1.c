////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：两个有序单向链表A,B（升序有序，均无重复元素）。请设计高效计算法求取两个链表的并集元素，A=merge(A,B) 
//          要求处理后链表A降序有序，并且没有重复元素，链表B为空。要求空间复杂度为O(c)
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
void getmerge(LI *A,LI *B);//将两个有序链表A，B合并，结果存放在链表A中，B链表为空
main()
{
	LI *A, *B;
	int m, n;
	A=(LI*)malloc(sizeof(LI));
	B=(LI*)malloc(sizeof(LI));
	A->next=B->next=NULL;
	printf("please input sizeof list A and B:\n");
	scanf("%d%d", &m, &n);
	while (n > 0 && m > 0)
	{
		createlist(A,m);
		createlist(B,n);
		printf("the original list A :\n");
		showlist(A);
		printf("the original list B :\n");
		showlist(B);
		getmerge(A,B);
		printf("the merge list is:\n");
		showlist(A);
		dellist(A);	
		printf("please input sizeof list A and B:\n");
	    scanf("%d%d", &m, &n);				
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



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  A,B表示两个升序有序链表的表头,求两个链表的并集，结果存放在链表A中
//
//  要求：链表A降序有序并且没有重复元素；链表B为空；；
//        空间复杂度为O（1），也就是将B中的节点从B中拆下来然后插入到A中，如果B的节点数据与A中重复，那么将B中的该节点释放      
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getmerge(LI *A,LI *B)
{
	LI *pa1,*pa;  //pa指向当前遍历A节点，pa1指向pa的前驱
	LI *pb;  //pb指向当前遍历B节点
	pa = A->next;
	pa1 = A;
	pb = B->next;
	// 进行升序插入 
	while(pa&&pb)
	{
		if(pa->data==pb->data)
		{
			pb = pb->next;	
		}	
		else if(pa->data>pb->data)
		{
			pa1->next = pb;
			pb->next = pa;
			pb = pb->next;
			pa1 = pb;
		}
		else
		{
			pa1 = pa;
			pa = pa->next;
		}
	} 
	if(pb)
	{
		pa->next = pb;
	}
	B->next = NULL;
	
	//进行逆序
	pa1 = A->next;
	pa = pa1->next;
	pa1->next = NULL; //第一个元素指向空 
	while(pa)	//转换指向方向 
	{
		LI *t;
		t = pa->next;
		pa->next = pa1;
		pa1 = pa;
		pa = t;				
	}
	A->next = pa1; //最后一个元素被A指向 
	
}
