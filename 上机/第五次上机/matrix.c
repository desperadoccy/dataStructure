///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//          ����A��0    3    0     0����Ԫ���ʾϡ�����A��B������㷨ʵ������ϡ�����ļӷ��Լ��������ô�����������Լ����õ�ʱ�临�Ӷ�
//                 0   -1    0    12
//                 9    0    0     0
//
//          ����B��0    0    0     4
//                 0    1    5     0
//                 2    -6   0     0
//
//
//ѧ�ţ�
//������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "stdio.h"
#include "stdlib.h"
#define N 30
typedef struct mytripple//������Ԫ��
{
	int i,j,data;
}TR;

typedef struct mymatrix//����ϡ���������ݽṹ
{
	TR T[N];//��Ԫ������
	int mu,nu,tu;//mu��ʾ����,nu��ʾ����,tu��ʾ����Ԫ�ĸ���
}MA;

void showmatrix(MA *A);//��ʾϡ�����
MA reversema(MA *A);//��ϡ�������п������ã����������ý��
void init(MA *A,MA *B);//��ϡ������ʼ��������ʼֵ
MA addition(MA *A,MA *B);//������ϡ�������ӣ������ؽ��
main()
{
	MA A,B;
	init(&A,&B);//������ϡ�����ֵ
	printf("the original matrix A is:\n");
	showmatrix(&A);//��ʾϡ�����A	
	printf("the original matrix B is:\n");
	showmatrix(&B);//��ʾϡ�����B	
	A=addition(&A,&B);//��A��B��Ӳ���������ظ�A
	printf("the result of addition is:\n");
	showmatrix(&A);	//��ʾ��ӵĽ��
	A=reversema(&A);//������A����
	printf("after reverse,the matrix is:\n");
	showmatrix(&A);//��ʾ���ú�Ľ��
}

void showmatrix(MA *A)
{
	int i,j,k;//i��ʾ�кţ�j��ʾ�кţ�k��ʾ��Ԫ���з���Ԫ�����
	for(i=1,k=1;i<=A->mu;i++)
	{
		for(j=1;j<=A->nu;j++)
		{
			if(A->T[k].i==i&&A->T[k].j==j)
			{
				printf("%4d",A->T[k].data);
				k++;
			}
			else
				printf("   0");			
		}
		printf("\n");
	}
	printf("\n");
}



MA reversema(MA *A)
{
////////////////////////////////��ɸú���////////////////////////////////////////////////////////////////////////
	int i,j,k=1;//i��ʾ�кţ�j��ʾ��Ԫ��A�з���Ԫ����ţ�k��ʾ��Ԫ��B�з���Ԫ�����
	MA B;
	int num[N],opt[N]; 
	num[0]=0;
	opt[0]=1;
	B.mu=A->nu;
	B.nu=A->mu;
	B.tu=A->tu;
	for(i=1;i<=A->nu;i++) num[i]=0;
	for(j=1;j<=A->tu;j++) ++num[A->T[j].j];
	for(i=1;i<=A->nu;i++) opt[i]=opt[i-1]+num[i-1];
	for(j=1;j<=A->tu;j++)
	{
		int col=A->T[j].j;
		int q=opt[col];
		B.T[q].i=A->T[j].j;
		B.T[q].j=A->T[j].i;
		B.T[q].data=A->T[j].data;
		++opt[col];
	}
	return B;
}

MA addition(MA *A,MA *B)
{
////////////////////////////////��ɸú���////////////////////////////////////////////////////////////////////////
	int k=1,k1=1,k2=1;//k1��ʾ��Ԫ��A�з���Ԫ�����,k2��ʾ��Ԫ��A�з���Ԫ�����,k��ʾ��Ԫ��C�з���Ԫ�����
	MA C;
	C.mu = A->mu;
	C.nu = A->nu;
	while(k1<=A->tu&&k2<=B->tu)
	{
		if(A->T[k1].i<B->T[k2].i)
		{
			C.T[k].i = A->T[k1].i;
			C.T[k].j = A->T[k1].j;
			C.T[k].data = A->T[k1].data;
			k++;
			k1++;
		}
		else if(A->T[k1].i==B->T[k2].i)
		{
			if(A->T[k1].j<B->T[k2].j)
			{
				C.T[k].i = A->T[k1].i;
				C.T[k].j = A->T[k1].j;
				C.T[k].data = A->T[k1].data;
				k++;
				k1++;
			}
			else if(A->T[k1].j==B->T[k2].j)
			{
				if(A->T[k1].data + B->T[k2].data == 0)
				{
					k1++;
					k2++;
				}
				else
				{
					C.T[k].i = A->T[k1].i;
					C.T[k].j = A->T[k1].j;
					C.T[k].data = A->T[k1].data + B->T[k2].data;
					k++;
					k1++;	
					k2++;					
				}
			}
			else
			{
				C.T[k].i = B->T[k2].i;
				C.T[k].j = B->T[k2].j;
				C.T[k].data = B->T[k2].data;
				k++;
				k2++;
			}
		}
		else
		{
			C.T[k].i = B->T[k2].i;
			C.T[k].j = B->T[k2].j;
			C.T[k].data = B->T[k2].data;
			k++;
			k2++;
		}
	}
	while(k1<=A->tu)
	{
		C.T[k].i = A->T[k1].i;
		C.T[k].j = A->T[k1].j;
		C.T[k].data = A->T[k1].data;
		k++;
		k1++;		
	}
	while(k2<=B->tu)
	{
		C.T[k].i = B->T[k2].i;
		C.T[k].j = B->T[k2].j;
		C.T[k].data = B->T[k2].data;
		k++;
		k2++;		
	}
	C.tu=k-1;
	return C;
}
void init(MA *A,MA *B)
{
	A->mu=3;
	A->nu=4;
	A->tu=4;
	A->T[1].data=3;
	A->T[1].i=1;
	A->T[1].j=2;
	A->T[2].data=-1;
	A->T[2].i=2;
	A->T[2].j=2;
	A->T[3].data=12;
	A->T[3].i=2;
	A->T[3].j=4;
	A->T[4].data=9;
	A->T[4].i=3;
	A->T[4].j=1;
///////////////////////////////////////////////////////////////////
	B->mu=3;
	B->nu=4;
	B->tu=5;
	B->T[1].data=4;
	B->T[1].i=1;
	B->T[1].j=4;
	B->T[2].data=1;
	B->T[2].i=2;
	B->T[2].j=2;
	B->T[3].data=5;
	B->T[3].i=2;
	B->T[3].j=3;
	B->T[4].data=2;
	B->T[4].i=3;
	B->T[4].j=1;
	B->T[5].data=-6;
	B->T[5].i=3;
	B->T[5].j=2;

}
