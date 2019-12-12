////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ����������������A,B���������򣬾����ظ�Ԫ�أ�������Ƹ�Ч���㷨��ȡ��������Ĳ���Ԫ�أ�A=merge(A,B) 
//          Ҫ���������A�������򣬲���û���ظ�Ԫ�أ�����BΪ�ա�Ҫ��ռ临�Ӷ�ΪO(c)
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
void getmerge(LI *A,LI *B);//��������������A��B�ϲ���������������A�У�B����Ϊ��
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



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  A,B��ʾ����������������ı�ͷ,����������Ĳ�����������������A��
//
//  Ҫ������A����������û���ظ�Ԫ�أ�����BΪ�գ���
//        �ռ临�Ӷ�ΪO��1����Ҳ���ǽ�B�еĽڵ��B�в�����Ȼ����뵽A�У����B�Ľڵ�������A���ظ�����ô��B�еĸýڵ��ͷ�      
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getmerge(LI *A,LI *B)
{
	LI *pa1,*pa;  //paָ��ǰ����A�ڵ㣬pa1ָ��pa��ǰ��
	LI *pb;  //pbָ��ǰ����B�ڵ�
	pa = A->next;
	pa1 = A;
	pb = B->next;
	// ����������� 
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
	
	//��������
	pa1 = A->next;
	pa = pa1->next;
	pa1->next = NULL; //��һ��Ԫ��ָ��� 
	while(pa)	//ת��ָ���� 
	{
		LI *t;
		t = pa->next;
		pa->next = pa1;
		pa1 = pa;
		pa = t;				
	}
	A->next = pa1; //���һ��Ԫ�ر�Aָ�� 
	
}
