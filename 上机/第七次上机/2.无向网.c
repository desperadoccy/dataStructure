///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：
//1、用邻接矩阵创建无向网；
//2、请判断该无向网是否连通，是否包含回路（分析时间复杂度）
//3、输出任意两个顶点之间的所有简单路径，以及各自的路径长度（路径长度指的是路径中所有边的权值之和）
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define maxx 9999999//定义的无穷大值

typedef struct MyGraph
{
	int type;//0，表示无向网，1表示有向网
	int arcnum,vexnum;//图中边的个数以及顶点个数
	char **vexname;//存放顶点名的二维数组
	int **A;//邻接矩阵，A[i][j]表示i号顶点与j号顶点之间边的权值，若i,j之间没有边，则A[i][j]取值无穷大
}GH;
int menu_select();
int findvex(char *s,GH *G);//确定顶点s对应的序号
void creatgraph(GH *G);//以邻接矩阵的形式创建图
void showgraph(GH *G);//以邻接表的形式显示图
void findpath(GH *G,char *start,char *end);//寻找简单路径
int iscycle(GH *G);//判断图中是否有回路，有返回1，否则返回0
int isconnect(GH *G);//判断图是否连通，是返回1，否则返回0

int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.创建无向网（邻接矩阵）\n");
		printf("2.判断无向网是否连通\n");
		printf("3.判断无向网中是否有回路\n");
		printf("4.输出任意两个顶点之间的所有简单路径以及路径长度\n");		
		printf("0.exit\n");
		printf("Please input index(0-4):");
		i=getchar();		
	}while(i<'0' || i>'4');
	return (i-'0');	
}

main()
{
	GH G;
	char c1[20],c2[20];
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
			creatgraph(&G);
			showgraph(&G);
			system("pause");
			break;
		case 2:
			showgraph(&G);
			if(isconnect(&G))
				   printf("\n该图是连通的\n");
			else
				   printf("\n该图不是连通的\n");
			system("pause");
			break;
		case 3:
			showgraph(&G);
			if(iscycle(&G))
				   printf("\n该图中包含回路\n");
			else
				   printf("\n该图中不包含回路\n");
			system("pause");
			break;
		case 4:
			showgraph(&G);
			printf("\n请输入起止两个顶点名:\n");
	        scanf("%s%s",c1,c2);
			printf("所有从 %s 到 %s 的简单路径以及路径长度：\n",c1,c2);
			findpath(&G,c1,c2);
			system("pause");
			break;
		case 0:
			printf("GOOD BYE\n");
			system("pause");
			exit(0);
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int findvex(char *s,GH *G)
{
	int i;
	for(i=0;i<G->vexnum;i++)
	{
		if(strcmp(s,G->vexname[i])==0)
			return i;
	}
	printf("read file erro\n");
	exit(-1);
}

void creatgraph(GH *G)
{
///////////////////////////完成该函数////////////////////////////////
	char filename[]="graph2.txt";
	FILE *fp;
	int i,j,k,w;
	char c1[4],c2[4],c3[4];
	fp=fopen(filename,"rb");
	if(fp==NULL)
	{
		printf("read file erro\n");
		exit(-1);
	}
	fscanf(fp,"%d",&k);
	G->arcnum=0;
	G->type=0;
	G->vexnum=k;
	G->vexname=(char **)malloc(k*sizeof(char *));
	G->A=(int **)malloc(k*sizeof(int *));
	for(i=0;i<k;i++)
	{
		fscanf(fp,"%s",c1);
		G->vexname[i]=(char *)malloc(strlen(c1)*sizeof(char));
		strcpy(G->vexname[i],c1);
		G->A[i]=(int *)malloc(k*sizeof(int));
		for(j=0;j<k;j++)
			G->A[i][j]=maxx;
	}
	
	while(fscanf(fp,"%s%s%s",c1,c2,c3)!=EOF)
	{
		w=atoi(c3);
		(G->arcnum)++;
		i=findvex(c1,G);
		j=findvex(c2,G);
		G->A[i][j]=w;
		G->A[j][i]=w;
	}
	fclose(fp);
	
}



void showgraph(GH *G)
{
	int i,j;
	for(i=0;i<G->vexnum;i++)
	{
		printf("\n%s",G->vexname[i]);
		for(j=0;j<G->vexnum;j++)		
		{
			if(G->A[i][j]<maxx)
				printf("--%s(%d) ",G->vexname[j],G->A[i][j]);			
		}
	}
	printf("\n");
}



int top,cnt,path[100];
void dfs(GH *G,int start,int end,int v,int *vis,int weight)
{
	int i;
	for(i=0;i<G->vexnum;i++)
	{
		if(G->A[v][i]!=maxx)
		{
			if(i==end)
			{
				int l;
				cnt++;
				for(l=0;l<top;l++)
				{
					printf("%s--",G->vexname[path[l]]);
				}
				printf("%s\n",G->vexname[end]);
				printf("the weight is %d\n",weight+G->A[v][i]);
				continue;
			}
			if(!vis[i])
			{
				path[top++]=i;
				vis[i]=1;
				dfs(G,start,end,i,vis,weight+G->A[v][i]);
				vis[i]=0;
				top--;
			}
		}
	}
}
void findpath(GH *G,char *start,char *end)//寻找简单路径函数
{
///////////////////////////完成该函数////////////////////////////////
	cnt=0;
	top=0;
	int vis[100];
	memset(vis,0,100);
	int i=findvex(start,G);
	int j=findvex(end,G);
	vis[i]=1;
	path[top++]=i;
	dfs(G,i,j,i,vis,0);
	if(cnt==0)
		printf("no path\n");
}

void bfs(GH *G,int *vis,int v,int *flag)
{
	int que[100];
	int A[100][100];
	int head=0,tail=0;
	int i,j;
	for(i=0;i<G->vexnum;i++)
		for(j=0;j<G->vexnum;j++)
			A[i][j]=G->A[i][j];
	que[tail++]=v;
	while(head!=tail)
	{
		int t=que[head++];
		for(i=0;i<G->vexnum;i++)
		{
			if(A[t][i]!=maxx)
			{
				if(vis[i])
				{
					*flag=1;
					return;
				}
				else
				{
					vis[i]=1;
					A[t][i]=A[i][t]=maxx;
					que[tail++]=i;
				}
			}
		}
	}
	return;
}
int iscycle(GH *G)//判断图中是否有回路，有返回1，否则返回0
{
///////////////////////////完成该函数////////////////////////////////
	int vis[100];
	memset(vis,0,sizeof(int)*100);
	int i,flag=0;
	for(i=0;i<G->vexnum;i++)
	{
		if(!vis[i])
		{
			bfs(G,vis,0,&flag);
			if(flag)
				return 1;
		}
	}
	return 0;
}

void bfs2(GH *G,int *vis,int v)
{
	int que[100];
	int head=0,tail=0;
	int i,j;
	que[tail++]=v;
	while(head!=tail)
	{
		int t=que[head++];
		for(i=0;i<G->vexnum;i++)
		{
			if(G->A[t][i]!=maxx)
			{
				if(!vis[i])
				{
					vis[i]=1;
					que[tail++]=i;
				}
			}
		}
	}
	return;
}
int isconnect(GH *G)//判断图是否连通，是返回1，否则返回0
{
///////////////////////////完成该函数////////////////////////////////
	int vis[100];
	int i;
	memset(vis,0,sizeof(int)*100);
	bfs2(G,vis,0);
	for(i=0;i<G->vexnum;i++)
		if(!vis[i])
			return 0;
	return 1;
}





