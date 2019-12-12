////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ����������������A,B,C���������򣬾����ظ�Ԫ�أ�������Ƹ�Ч���㷨��ȡ��������Ľ���Ԫ�أ�A=common(A,B,C) 
//          Ҫ���������A��Ȼ�������򣬲���û���ظ�Ԫ�أ�����B��C���ֲ��䡣Ҫ��ռ临�Ӷ�ΪO(c)
//          
//ѧ   �ţ� 161830218                                                                                                 
//��   ���� �³��D                                                                                                  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////




#include "stdlib.h"
#include "math.h"
#include "stdio.h"


typedef struct node
{
	int data;
	struct node *next;
}LI;

void createlist(LI *head,int n);//����n�����������һ����������
void showlist(LI *head);//��ʾ��������
void dellist(LI *head);//��������
void insertdata(LI *head,int data);//�����������в���һ�����ݣ������������Ȼ����
void getcommon(LI *A,LI *B,LI *C);//��������������A��B��C�ϲ���������������A�У�B��C���ֲ���
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
		x=rand()%29;//������ɵ����ݲ�����29�����ֵ�������е���
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
	LI *p,*p2;//pָ��ǰ�����ڵ�,p2ָ��p �ĺ��
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
	LI *p1,*p,*q;//pָ��ǰ�����ڵ�,p1ָ��p��ǰ��,qָ�������ɵĽ�Ҫ����Ľڵ�
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
	if(p&&p->data==data)//�ظ����ֵ����ݲ�������
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
//  A,B,C��ʾ����������������ı�ͷ,����������Ľ�����������������A��
//
//  Ҫ�󣺴����������A����������û���ظ�Ԫ�أ�����B��C���ֲ��䣻
//        �ռ临�Ӷ�ΪO��1������A�еķǽ������ɾ�����ͷż���      
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getcommon(LI *A,LI *B,LI *C)
{
	LI *pa,*pb,*pc; //�ֱ��ʾA��B��C��ǰ�����Ľڵ�
	LI *pa0; //pa0��ʾpa��ǰ�� 
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
