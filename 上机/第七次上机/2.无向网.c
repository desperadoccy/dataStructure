///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//1�����ڽӾ��󴴽���������
//2�����жϸ��������Ƿ���ͨ���Ƿ������·������ʱ�临�Ӷȣ�
//3�����������������֮������м�·�����Լ����Ե�·�����ȣ�·������ָ����·�������бߵ�Ȩֵ֮�ͣ�
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define maxx 9999999//����������ֵ

typedef struct MyGraph
{
	int type;//0����ʾ��������1��ʾ������
	int arcnum,vexnum;//ͼ�бߵĸ����Լ��������
	char **vexname;//��Ŷ������Ķ�ά����
	int **A;//�ڽӾ���A[i][j]��ʾi�Ŷ�����j�Ŷ���֮��ߵ�Ȩֵ����i,j֮��û�бߣ���A[i][j]ȡֵ�����
}GH;
int menu_select();
int findvex(char *s,GH *G);//ȷ������s��Ӧ�����
void creatgraph(GH *G);//���ڽӾ������ʽ����ͼ
void showgraph(GH *G);//���ڽӱ����ʽ��ʾͼ
void findpath(GH *G,char *start,char *end);//Ѱ�Ҽ�·��
int iscycle(GH *G);//�ж�ͼ���Ƿ��л�·���з���1�����򷵻�0
int isconnect(GH *G);//�ж�ͼ�Ƿ���ͨ���Ƿ���1�����򷵻�0

int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.�������������ڽӾ���\n");
		printf("2.�ж��������Ƿ���ͨ\n");
		printf("3.�ж����������Ƿ��л�·\n");
		printf("4.���������������֮������м�·���Լ�·������\n");		
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
				   printf("\n��ͼ����ͨ��\n");
			else
				   printf("\n��ͼ������ͨ��\n");
			system("pause");
			break;
		case 3:
			showgraph(&G);
			if(iscycle(&G))
				   printf("\n��ͼ�а�����·\n");
			else
				   printf("\n��ͼ�в�������·\n");
			system("pause");
			break;
		case 4:
			showgraph(&G);
			printf("\n��������ֹ����������:\n");
	        scanf("%s%s",c1,c2);
			printf("���д� %s �� %s �ļ�·���Լ�·�����ȣ�\n",c1,c2);
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
///////////////////////////��ɸú���////////////////////////////////
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
void findpath(GH *G,char *start,char *end)//Ѱ�Ҽ�·������
{
///////////////////////////��ɸú���////////////////////////////////
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
int iscycle(GH *G)//�ж�ͼ���Ƿ��л�·���з���1�����򷵻�0
{
///////////////////////////��ɸú���////////////////////////////////
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
int isconnect(GH *G)//�ж�ͼ�Ƿ���ͨ���Ƿ���1�����򷵻�0
{
///////////////////////////��ɸú���////////////////////////////////
	int vis[100];
	int i;
	memset(vis,0,sizeof(int)*100);
	bfs2(G,vis,0);
	for(i=0;i<G->vexnum;i++)
		if(!vis[i])
			return 0;
	return 1;
}





