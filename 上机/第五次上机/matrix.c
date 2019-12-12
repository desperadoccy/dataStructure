///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：
//          矩阵A：0    3    0     0用三元组表示稀疏矩阵A与B，设计算法实现两个稀疏矩阵的加法以及快速逆置处理，分析相加以及逆置的时间复杂度
//                 0   -1    0    12
//                 9    0    0     0
//
//          矩阵B：0    0    0     4
//                 0    1    5     0
//                 2    -6   0     0
//
//
//学号：
//姓名：
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "stdio.h"
#include "stdlib.h"
#define N 30
typedef struct mytripple//定义三元组
{
	int i,j,data;
}TR;

typedef struct mymatrix//定义稀疏矩阵的数据结构
{
	TR T[N];//三元组数组
	int mu,nu,tu;//mu表示行数,nu表示列数,tu表示非零元的个数
}MA;

void showmatrix(MA *A);//显示稀疏矩阵
MA reversema(MA *A);//对稀疏矩阵进行快速逆置，并返回逆置结果
void init(MA *A,MA *B);//对稀疏矩阵初始化，赋初始值
MA addition(MA *A,MA *B);//将两个稀疏矩阵相加，并返回结果
main()
{
	MA A,B;
	init(&A,&B);//对两个稀疏矩阵赋值
	printf("the original matrix A is:\n");
	showmatrix(&A);//显示稀疏矩阵A	
	printf("the original matrix B is:\n");
	showmatrix(&B);//显示稀疏矩阵B	
	A=addition(&A,&B);//将A与B相加并将结果返回给A
	printf("the result of addition is:\n");
	showmatrix(&A);	//显示相加的结果
	A=reversema(&A);//将矩阵A逆置
	printf("after reverse,the matrix is:\n");
	showmatrix(&A);//显示逆置后的结果
}

void showmatrix(MA *A)
{
	int i,j,k;//i表示行号，j表示列号，k表示三元组中非零元的序号
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
////////////////////////////////完成该函数////////////////////////////////////////////////////////////////////////
	int i,j,k=1;//i表示行号，j表示三元组A中非零元的序号，k表示三元组B中非零元的序号
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
////////////////////////////////完成该函数////////////////////////////////////////////////////////////////////////
	int k=1,k1=1,k2=1;//k1表示三元组A中非零元的序号,k2表示三元组A中非零元的序号,k表示三元组C中非零元的序号
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
