/////////////////////////////////////////////////////////////////////////////////////
//题目要求：
//        1、设计高效算法实现基数排序，要求空间复杂度O(c)，要求只能用代表0和1的两个桶；
//
//        
//        2、设计高效非递归算法实现归并排序
//        
//        3、在链式的数据结构中设计高效算法实现冒泡排序，使得链表有序，要求空间复杂度O(c)
//
//        4、不要修改已给定的公共代码，可以自行增加和定义需要的功能函数，不可调用库函数
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
}LI;//基数排序所需的链式结构

void getdata(LI *A,LI *B,int *a,int n);//获取n个随机数创建两个无序链表和一个数组
void showlist(LI *head);//显示链表数据
void showarray(int *a,int n);//显示数组数据
void mergesort(int *a,int n);//归并排序
void radixsort(LI *head);//基数排序
void bubblesort(LI *head);//冒泡排序
void dellist(LI *head);//销毁链表


main()
{
	int *a,n;
	LI *A,*B;
	A=(LI *)malloc(sizeof(LI));
	B=(LI *)malloc(sizeof(LI));
	A->next=B->next=NULL;//创建两个空的带头链表
	printf("\n请输入数据规模:\n");
	scanf("%d",&n);
	while(n>0)
	{
		a=(int *)malloc((n+1)*sizeof(int));//0号位置不放数据
		getdata(A,B,a,n);//获取链表与数组数据
		radixsort(A);//基数排序
		mergesort(a,n);//归并排序
		bubblesort(B);//冒泡排序
		free(a);//释放数组空间
		dellist(A);//销毁链表
		dellist(B);//销毁链表
		printf("\n请输入数据规模:\n");//重新输入需要排序的数据规模
	    scanf("%d",&n);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getdata(LI *A,LI *B,int *a,int n)//获取n个随机数创建无序链表与数组
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
		a[n-i+1]=x;//注意数组的有效元素是从a[1]----a[n]
	}	
}



void showlist(LI *head)//显示链表内容
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

void showarray(int *a,int n)//显示数组内容
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

void dellist(LI *head)//销毁链表
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

void mergesort(int *a,int n)//归并排序
{
	int *t;
	t=(int *)malloc((n+1)*sizeof(int));//辅助数组
	
////////////////////////完成该函数////////////////////////////////
	
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
	
////////////////////////完成该函数////////////////////////////////
	printf("\n归并排序的结果：\n");
	showarray(a,n);
	free(t);
}



void bubblesort(LI *head)//冒泡排序
{
////////////////////////完成该函数////////////////////////////////
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
	


////////////////////////完成该函数////////////////////////////////
	printf("\n冒泡排序的结果：\n");
	showlist(head);
}





void radixsort(LI *head)//基数排序
{
////////////////////////完成该函数////////////////////////////////
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



////////////////////////完成该函数////////////////////////////////
	printf("\n基数排序的结果：\n");
	showlist(head);
}




