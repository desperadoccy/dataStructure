////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��ģ��ʵ��Լɪ�����⡣����N����Χ��Ȧ������ÿ����Mʱ����һ�����Ƴ�Ȧ�⣬Ȼ��ӵ�ǰλ�ü�����1��ʼ
//          ����������Mʱ�ٽ�һ���Ƴ�Ȧ�⣬�������ƣ�ֱ��Ȧ�н�ʣһ�ˡ���ô�Ƴ���˳�򽫻���������
//          ���統N=5��M=3ʱ����ʼ����������1 2 3 4 5������M�ı�����������α�ɾ�����Ľڵ���3 1 5 2 4        
//          
//          
//ѧ   �ţ�161830218                                                                                                        
//��   �����³��D                                                                                                         
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////




#include "stdlib.h"
#include "math.h"
#include "stdio.h"

typedef struct node
{
	int data;
	struct node *next;
}LI;


LI *createcyclist(int n);//����������n���ڵ�ĵ���ѭ����������β�ڵ�ָ��
void showcyclist(LI *A);//���մ�ͷ��β��˳����ʾѭ�����������
void joesph(LI *A,int m);//ģ��ʵ��Լɪ�����⡣����n��m����ֵ�����ν���Ӧ�ڵ��������ɾ�������ɾ����˳��
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

	LI *head,*rear,*p;//headָ��ѭ������ĵ�һ���ڵ㣬rearָ��β�ڵ㣬pָ��ǰ�����ɵĽڵ�
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


void showcyclist(LI *A)//Aָ��ѭ�������β�ڵ�
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
//    A�ǳ���Ϊn��ѭ�������β�ڵ㣬����m�ļ��ɾ���ڵ㣬ÿɾ��һ���ڵ㣬����ýڵ�����
//   
//    ��������ֻʣ�����һ���ڵ�ʱ�����ýڵ����������ͬʱҲ�ͷŵ����һ���ڵ㣬��ʱ����Ϊ�գ����нڵ�����ͷ�
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void joesph(LI *A,int m)//Aָ��ѭ�������β�ڵ�
{
	int cnt=0; //������ 
	LI *pa0,*pa; //pa��ʾ��ǰ�����Ľڵ㣬pa0��ʾpaǰ��
	pa0 = A;
	pa = A->next;
	while(pa!=pa->next)
	{
		cnt++;
		if(cnt%m == 0)
		{
			printf("%d ",pa->data);  //���ɾ��Ԫ�� 
			LI *t;
			t = pa;
			pa = pa->next;
			pa0->next = pa;
			free(t);	//ɾ��Ԫ�� 
		}
		else
		{
			pa0 = pa;
			pa = pa->next;
		}
	}
	printf("%d\n",pa->data); //������һ��Ԫ��
	free(pa); //ɾ�����һ��Ԫ�� 
}

