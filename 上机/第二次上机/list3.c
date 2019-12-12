////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：模拟实现约瑟夫问题。当有N个人围成圈，报数每报到M时，将一个人移出圈外，然后从当前位置继续从1开始
//          报数，报到M时再将一人移出圈外，依次类推，直至圈中仅剩一人。那么移除的顺序将会是怎样？
//          例如当N=5，M=3时，初始链表内容是1 2 3 4 5；按照M的报数间隔，依次被删除掉的节点是3 1 5 2 4        
//          
//          
//学   号：161830218                                                                                                        
//姓   名：陈楚燚                                                                                                         
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////




#include "stdlib.h"
#include "math.h"
#include "stdio.h"

typedef struct node
{
	int data;
	struct node *next;
}LI;


LI *createcyclist(int n);//创建包含有n个节点的单向循环链表并返回尾节点指针
void showcyclist(LI *A);//按照从头到尾的顺序显示循环链表的内容
void joesph(LI *A,int m);//模拟实现约瑟夫问题。根据n和m的数值，依次将对应节点从链表中删除，输出删除的顺序
main()
{
	LI *A;
	int n,m;
	printf("please input the data of N and M:\n");
	scanf("%d%d", &n, &m);
	while (n > 0 && m > 0)
	{
		A = createcyclist(n);			
		printf("the original list is :\n");
		showcyclist(A);
		printf("the del order is:\n");
		joesph(A,m);		
		printf("please input the data of N and M:\n");
	    scanf("%d%d", &n, &m);	
	}
}

LI *createcyclist(int n)
{

	LI *head,*rear,*p;//head指向循环链表的第一个节点，rear指向尾节点，p指向当前新生成的节点
	int i;
	head=(LI *)malloc(sizeof(LI));
	head->data=1;
	rear=head;
	for(i=2;i<=n;i++)		
	{
		p=(LI *)malloc(sizeof(LI));
		p->data=i;
		rear->next=p;
		rear=p;
	}
	rear->next=head;
	return rear;	
}


void showcyclist(LI *A)//A指向循环链表的尾节点
{
/////////////////////////please complete the function///////////////////////////////////////////////////////////////////////////////
	LI *p,*head;
	int i=0;
	head=A->next;
	p=head;
	do
	{
		printf("%4d",p->data);
		i++;
		if(i%15==0)
			printf("\n");
		p=p->next;
	}while(p!=head);
	printf("\n\n");	
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    A是长度为n的循环链表的尾节点，按照m的间隔删除节点，每删除一个节点，输出该节点数据
//   
//    当链表中只剩下最后一个节点时，将该节点数据输出，同时也释放掉最后一个节点，此时链表为空，所有节点均被释放
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void joesph(LI *A,int m)//A指向循环链表的尾节点
{
	int cnt=0; //计数器 
	LI *pa0,*pa; //pa表示当前遍历的节点，pa0表示pa前驱
	pa0 = A;
	pa = A->next;
	while(pa!=pa->next)
	{
		cnt++;
		if(cnt%m == 0)
		{
			printf("%d ",pa->data);  //输出删除元素 
			LI *t;
			t = pa;
			pa = pa->next;
			pa0->next = pa;
			free(t);	//删除元素 
		}
		else
		{
			pa0 = pa;
			pa = pa->next;
		}
	}
	printf("%d\n",pa->data); //输出最后一个元素
	free(pa); //删除最后一个元素 
}

