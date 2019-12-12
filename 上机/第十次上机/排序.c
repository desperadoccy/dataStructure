/////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//        1����Ƹ�Ч�㷨ʵ�ֻ�������Ҫ��ռ临�Ӷ�O(c)��Ҫ��ֻ���ô���0��1������Ͱ��
//
//        
//        2����Ƹ�Ч�ǵݹ��㷨ʵ�ֹ鲢����
//        
//        3������ʽ�����ݽṹ����Ƹ�Ч�㷨ʵ��ð������ʹ����������Ҫ��ռ临�Ӷ�O(c)
//
//        4����Ҫ�޸��Ѹ����Ĺ������룬�����������ӺͶ�����Ҫ�Ĺ��ܺ��������ɵ��ÿ⺯��
//
//////////////////////////////////////////////////////////////////////////////////////




#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
typedef struct node
{
	int data;
	struct node *next;
}LI;//���������������ʽ�ṹ

void getdata(LI *A,LI *B,int *a,int n);//��ȡn������������������������һ������
void showlist(LI *head);//��ʾ��������
void showarray(int *a,int n);//��ʾ��������
void mergesort(int *a,int n);//�鲢����
void radixsort(LI *head);//��������
void bubblesort(LI *head);//ð������
void dellist(LI *head);//��������


main()
{
	int *a,n;
	LI *A,*B;
	A=(LI *)malloc(sizeof(LI));
	B=(LI *)malloc(sizeof(LI));
	A->next=B->next=NULL;//���������յĴ�ͷ����
	printf("\n���������ݹ�ģ:\n");
	scanf("%d",&n);
	while(n>0)
	{
		a=(int *)malloc((n+1)*sizeof(int));//0��λ�ò�������
		getdata(A,B,a,n);//��ȡ��������������
		radixsort(A);//��������
		mergesort(a,n);//�鲢����
		bubblesort(B);//ð������
		free(a);//�ͷ�����ռ�
		dellist(A);//��������
		dellist(B);//��������
		printf("\n���������ݹ�ģ:\n");//����������Ҫ��������ݹ�ģ
	    scanf("%d",&n);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getdata(LI *A,LI *B,int *a,int n)//��ȡn�������������������������
{
	LI *p;
	int i,x;
	srand(time(0));
	for(i=1;i<=n;i++)
	{
		x=rand();
		p=(LI *)malloc(sizeof(LI));
		p->data=x;
		p->next=A->next;
		A->next=p;
		p=(LI *)malloc(sizeof(LI));
		p->data=x;
		p->next=B->next;
		B->next=p;
		a[n-i+1]=x;//ע���������ЧԪ���Ǵ�a[1]----a[n]
	}	
}



void showlist(LI *head)//��ʾ��������
{
	int i=0;
	LI *p=head->next;
	while(p)
	{
		printf("%-6d ",p->data);
		i++;
		if(i%15==0)
			printf("\n");
		p=p->next;
	}
	printf("\n");
}

void showarray(int *a,int n)//��ʾ��������
{
	int i,j;
	for(i=1,j=0;i<=n;i++)
	{
		printf("%-6d ",a[i]);
		j++;
		if(j%15==0)
			printf("\n");
	}
	printf("\n");
}

void dellist(LI *head)//��������
{
	LI *p,*p2;
	p=head->next;
	head->next=NULL;
	while(p)
	{
		p2=p->next;
		free(p);
		p=p2;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void merge(int *a,int *t,int L,int mid,int R)
{
	int p1=L,p2=mid+1,k,i=0;
	while(p1<=mid&&p2<=R)
	{
		if(a[p1]<=a[p2]){
			t[i++]=a[p1++];
		}else{
			t[i++]=a[p2++];
		}
	}
	while(p1<=mid)
		t[i++]=a[p1++];
	while(p2<=mid)
		t[i++]=a[p2++];
	for(k=0;k<i;k++)
		a[L+k]=t[k];
}

void mergesort(int *a,int n)//�鲢����
{
	int *t;
	t=(int *)malloc((n+1)*sizeof(int));//��������
	
////////////////////////��ɸú���////////////////////////////////
	
	int i,len=1;
	while(len<=n)
	{
		for(i=1;i<=n;i+=len*2)
		{
			int L=i;
			int mid=i+len-1;
			int R=i+len*2-1;
			mid = mid<n?mid:n;
			R = R<n?R:n;
			merge(a,t,L,mid,R);
		}
		len*=2;
	}
	
////////////////////////��ɸú���////////////////////////////////
	printf("\n�鲢����Ľ����\n");
	showarray(a,n);
	free(t);
}



void bubblesort(LI *head)//ð������
{
////////////////////////��ɸú���////////////////////////////////
	LI *tail=NULL,*cur=head;
	int t;
	while(head->next!=tail)
	{
		cur = head->next;
		while(cur->next!=tail)
		{
			if(cur->data>cur->next->data)
			{
				t = cur->data;
				cur->data = cur->next->data;
				cur->next->data = t;
			}
			cur = cur->next;
		}
		tail = cur;
	}
	


////////////////////////��ɸú���////////////////////////////////
	printf("\nð������Ľ����\n");
	showlist(head);
}





void radixsort(LI *head)//��������
{
////////////////////////��ɸú���////////////////////////////////
	LI *tong[2],*p=head->next;
	int mmax=0,maxlen=1;
	tong[0]=(LI *)malloc(sizeof(LI));
	tong[1]=(LI *)malloc(sizeof(LI));
	tong[0]->next=NULL;
	tong[1]->next=NULL;
	while(p!=NULL)
	{
		if(p->data>mmax) mmax=p->data;
		p=p->next;
	}
	while(mmax>>1)
	{
		maxlen++;
		mmax=mmax>>1;
	}
	int i;
	LI *p0,*p1;
	for(i=0;i<maxlen;i++)
	{
		int k;
		p=head->next;
		p0=tong[0],p1=tong[1];
		while(p!=NULL)
		{
			k=((p->data)>>i)&1;
			if(k){
				p1->next=p;
				p1=p1->next;
			}else{
				p0->next=p;
				p0=p0->next;
			}
			p=p->next;
		}
		p0->next=NULL;
		p1->next=NULL;
		p=head;
		p0=tong[0]->next;
		p1=tong[1]->next;
		while(p0)
		{
			p->next=p0;
			p=p->next;
			p0=p0->next;
		}
		while(p1)
		{
			p->next=p1;
			p=p->next;
			p1=p1->next;
		}
		p->next=NULL;
	}



////////////////////////��ɸú���////////////////////////////////
	printf("\n��������Ľ����\n");
	showlist(head);
}




