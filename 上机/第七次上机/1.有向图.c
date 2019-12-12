///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//1�����ڽӱ�������ͼ��
//2����Ƶݹ��㷨Ѱ������ͨ��ָ���ڵ�ļ򵥻�·
//3������㷨�жϴӶ���u������v�Ƿ����·��������ʱ�临�Ӷȣ�
//4������㷨�������ж������ȣ�����ʱ�临�Ӷȣ�
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct arcnode
{	
	int index;//�ڽӵ����
	struct arcnode *next;
}AR;

typedef struct MyGraph
{
	int type;//0����ʾ����ͼ��1��ʾ����ͼ
	int arcnum,vexnum;//ͼ�бߵĸ����Լ��������
	char **vexname;//��Ŷ������Ķ�ά����
	AR *N;//����ڽӱ�ͷ��������
}GH;

int findvex(char *s,GH *G);//ȷ������s��Ӧ�����
void creatgraph(GH *G);//���ڽӱ����ʽ����ͼ
void showgraph(GH *G);//���ڽӱ����ʽ��ʾͼ
void findpath(GH *G,char *start);//Ѱ�����о�������start�ļ�·��
int ispath(GH *G,char *start,char *end);//�жϴӶ���start������end�Ƿ����·�������ڷ���1�����򷵻�0
void indegree(GH *G);//���㲢��ʾ���ͼ��ÿ����������
int menu_select();


int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.��������ͼ���ڽӱ�\n");
		printf("2.������о���ָ������ļ򵥻�·\n");
		printf("3.�ж���������֮���Ƿ����·��\n");
		printf("4.������ж�������\n");		
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
			printf("�����붥����:\n");
			scanf("%s",c1);
			printf("���о���%s�ļ򵥻�·��:\n",c1);
			findpath(&G,c1);				   
			system("pause");
			break;
		case 3:
			showgraph(&G);
			printf("��������ֹ����������:\n");
			scanf("%s%s",c1,c2);
			if(ispath(&G,c1,c2))
				printf("�Ӷ���%s������%s����·��\n",c1,c2);
			else
				printf("�Ӷ���%s������%s������·��\n",c1,c2);			
			system("pause");
			break;
		case 4:
			showgraph(&G);
			printf("\nͼ�����ж�������:\n");
	        indegree(&G);
			system("pause");
			break;
		case 0:
			printf("GOOD BYE\n");
			system("pause");
			exit(0);
		}
	}
}




int findvex(char *s,GH *G)//���ݶ�����ȷ���ö���ı��
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
////////////////////////��ɸú���///////////////////////////////////////////////
	FILE *fp;
	AR *p;
	int i,j,k;
	char c1[4],c2[4];
	char filename[]="graph1.txt";
	fp=fopen(filename,"rb");
	if(fp==NULL)
	{
		printf("read file erro\n");
		exit(-1);
	}
	fscanf(fp,"%d",&k);
	G->arcnum=0;
	G->type=1;
	G->vexnum=k;
	G->vexname=(char **)malloc(k*sizeof(char *));
	G->N=(AR *)malloc(k*sizeof(AR));
	for(i=0;i<k;i++)
	{
		fscanf(fp,"%s",c1);
		G->vexname[i]=(char *)malloc(strlen(c1)*sizeof(char));
		strcpy(G->vexname[i],c1);
		G->N[i].next=NULL;
	}
	while(fscanf(fp,"%s%s",c1,c2)!=EOF)
	{
		(G->arcnum)++;
		i=findvex(c1,G);
		j=findvex(c2,G);
		p=(AR *)malloc(sizeof(AR));
		p->index=j;
		p->next=G->N[i].next;
		G->N[i].next=p;
		if(G->type==0)
		{
			p=(AR *)malloc(sizeof(AR));
			p->index=i;
			p->next=G->N[j].next;
			G->N[j].next=p;
		}
	}
	fclose(fp);
}



void showgraph(GH *G)
{
	int i;
	AR *p;
	for(i=0;i<G->vexnum;i++)
	{
		printf("\n%s ",G->vexname[i]);
		p=G->N[i].next;
		while(p)
		{
			printf("--%s ",G->vexname[p->index]);
			p=p->next;
		}
	}
	printf("\n");
}

int top;
int path[100];
void dfs(GH *G,int start,int v,int *vis)
{
	AR *p=G->N[v].next;
	while(p)
	{
		int i=p->index;
		//printf("%d\n",i);
		//system("pause");
		if(vis[i]&&i==start)
		{
			int l;
			for(l=0;l<top;l++)
			{
				printf("%s--",G->vexname[path[l]]);
			}
			printf("%s\n",G->vexname[start]);
			p=p->next;
			continue;
		}
		if(!vis[i])
		{
			path[top++]=i;
			vis[i]=1;
			dfs(G,start,i,vis);
			vis[i]=0;
			top--;
		}
		p=p->next;
	}

}
void findpath(GH *G,char *start)//Ѱ�����о�������start�ļ򵥻�·
{
////////////////////////��ɸú���///////////////////////////////////////////////
	top=0;
	int vis[100];
	memset(vis,0,sizeof(int)*100);
	int i=findvex(start,G);
	path[top++]=i;
	vis[i]=1;
	dfs(G,i,i,vis);
}

void indegree(GH *G)//���㲢��ʾ���ͼ��ÿ����������
{
////////////////////////��ɸú���///////////////////////////////////////////////
	int i;
	int ingree[100];
	memset(ingree,0,sizeof(int)*100);
	for(i=0;i<G->vexnum;i++)
	{
		AR *p=G->N[i].next;
		while(p)
		{
			ingree[p->index]++;
			p=p->next;
		}
	}
	for(i=0;i<G->vexnum;i++)
	{
		printf("%s--%d\n",G->vexname[i],ingree[i]);
	}
}

int ispath(GH *G,char *start,char *end)//�жϴӶ���start������end�Ƿ����·�������ڷ���1�����򷵻�0
{
///////////////////////��ɸú���///////////////////////////////////////////////
	int s=findvex(start,G);
	int e=findvex(end,G);
	int que[100],vis[100];
	int head=0,tail=0;
	que[tail++]=s;
	int flag=0;
	memset(vis,0,sizeof(int)*100);
	while(head!=tail)
	{
		int i=que[head++];
		AR *p=G->N[i].next;
		while(p)
		{
			if(p->index==e)
			{
				flag=1;
				break;
			}
			if(!vis[p->index])
			{
				vis[p->index]=1;
				que[tail++]=p->index;
			}
			p=p->next;
		}
		if(flag) break;
	}
	if(flag) return 1;
	else return 0;
}






