#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 8000

using namespace std;

typedef struct stack
{
	int top;
	int stack[1000];
}ST;
typedef struct arcnode
{
	int index;
	struct arcnode* next;
}AR;
typedef struct MyGraph
{
	int type;
	int arcnum, vexnum;
	char** vexname;
	AR* N;
	ST* S;
}GH;

int findvex(char* s, GH* G)
{
	int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (strcmp(s, G->vexname[i]) == 0)
			return i;
	}
	return -1;
}

void creatgraph(GH* G)
{
	FILE* fp;
	AR* p;
	int i, j, k,m,n;
	int w;
	char c1[100],c3[200], c4[200],c2[8000];
	char filename[] = "3.txt";
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("read file erro\n");
		exit(-1);
	}
	G->type = 0;
	G->arcnum = 0;
	G->vexnum = 0;
	G->vexname = (char**)malloc(MAXN * sizeof(char*));
	G->N = (AR*)malloc(MAXN * sizeof(AR));
	G->S = (ST*)malloc(MAXN * sizeof(ST));
	for (i = 0; i < MAXN; i++)
	{
		G->S[i].top = 0;
	}
	while (fscanf(fp, "%s%s", c1, c2) != EOF)
	{
		w = atoi(c1);
		for (i = 0; i < strlen(c2);)
		{
			j = 0;
			while (c2[i] != ',')
				c3[j++] = c2[i++];
			c3[j]='\0',i++;
			j = 0, k = i;
			while (c2[k] != ','&&c2[k]!='\0')
				c4[j++] = c2[k++];
			c4[j] = '\0';
			m = findvex(c3, G);
			if (m == -1)
			{
				m = G->vexnum;
				G->vexname[m] = (char*)malloc(strlen(c3) * sizeof(char));
				strcpy(G->vexname[G->vexnum++], c3);
				G->N[m].next = NULL;
			}
			n = findvex(c4, G);
			if (n == -1)
			{
				n = G->vexnum;
				G->vexname[n] = (char*)malloc(strlen(c4) * sizeof(char));
				strcpy(G->vexname[G->vexnum++], c4);
				G->N[n].next = NULL;
			}
			G->S[m].stack[G->S[m].top++] = w;
			G->S[n].stack[G->S[n].top++] = w;
			p = (AR*)malloc(sizeof(AR));
			p->index = n;
			p->next = G->N[m].next;
			G->N[m].next = p;
			p = (AR*)malloc(sizeof(AR));
			p->index = m;
			p->next = G->N[n].next;
			G->N[n].next = p;
			G->arcnum++;
			if (k == strlen(c2)) break;
		}
	}
	fclose(fp);
}

void showroute(GH* G, int* pre, int i,int j)
{
	if (pre[j] == i)
	{
		cout << G->vexname[i];
		return;
	}
	showroute(G, pre, i, pre[j]);
	cout << "--" << G->vexname[pre[j]];
}

int dis[MAXN], pre[MAXN], lu[MAXN];
bool vis[MAXN];
void find1(GH* G,int start,int end)
{
	int n = G->vexnum;
	for (int i = 0; i < n; i++)
	{
		dis[i] = 999999;
		vis[i] = 0;
		pre[i] = i;
	}
	dis[start] = 0;
	for (int i = 0; i < n; i++)
	{
		int k = -1, mmin = 999999;
		for (int j = 0; j < n; j++)
		{
			if (mmin>dis[j]&&!vis[j])
			{
				mmin = dis[j];
				k = j;
			}
		}
		if (k == -1) break;
		vis[k] = 1;
		AR *p = G->N[k].next;
		while (p)
		{
			if (!vis[p->index] && dis[p->index] > dis[k] + 1)
			{
				dis[p->index] = dis[k] + 1;
				pre[p->index] = k;
			}
			p = p->next;
		}
	}
	if (dis[end] == 999999)
	{
		cout << "两站点不通车" << endl;
		return;
	}
	cout << "经过站点最少次数为" << dis[end] << "。乘车路线如下:" << endl;
	showroute(G,pre,start, end);
	cout << "--"<<G->vexname[end] << endl;
}

void find2(GH* G, int start, int end)
{
	int n = G->vexnum;
	for (int i = 0; i < n; i++)
	{
		dis[i] = 999999;
		vis[i] = 0;
		pre[i] = i;
		lu[i] = 0;
	}
	dis[start] = 0; 
	for (int i = 0; i < n; i++)
	{
		int k = -1, mmin = 999999;
		for (int j = 0; j < n; j++)
		{
			if (mmin > dis[j] && !vis[j])
			{
				mmin = dis[j];
				k = j;
			}
		}
		if (k == -1) break;
		vis[k] = 1;
		AR* p = G->N[k].next;
		while (p)
		{
			if (!vis[p->index]&&dis[p->index]>dis[k])
			{
				bool flag=0;
				if (!lu[k])
				{
					for (int j = 0; j < G->S[p->index].top; j++)
					{
						for (int l = 0; l < G->S[k].top; l++)
							if (G->S[p->index].stack[j] == G->S[k].stack[l])
							{
								dis[p->index] = dis[k];
								pre[p->index] = k;
								lu[p->index] = G->S[k].stack[l];
								flag = 1;
								break;
							}
						if (flag) break;
					}
					continue;
				}
				for (int j = 0; j < G->S[p->index].top; j++)
				{
					if (G->S[p->index].stack[j] == lu[k])
					{
							dis[p->index] = dis[k];
							pre[p->index] = k;
							lu[p->index] = G->S[i].stack[j];
							flag = 1;
							break;
					}
				}
					if (dis[p->index] > dis[k] + 1)
					{
						dis[p->index] = dis[k] + 1;
						pre[p->index] = k;
						for (int j = 0; j < G->S[p->index].top; j++)
						{
							for (int l = 0; l < G->S[k].top; l++)
								if (G->S[p->index].stack[j] == G->S[k].stack[l])
								{
									lu[p->index] = G->S[k].stack[l];
									flag = 1;
									break;
								}
							if (flag) break;
						}
					}
			}
			p = p->next;
		}
	}
	if (dis[end] == 999999)
	{
		cout << "两站点不通车" << endl;
		return;
	}
	cout << "转车次数最少次数为" << dis[end] << "。乘车路线如下:" << endl;
	showroute(G, pre, start, end);
	cout << "--" << G->vexname[end] << endl;
}

void busLine(GH *G)
{
	char a[100], b[100];
	cout << "请输入起始站：";
	cin >> a;
	int x = findvex(a, G);
	cout << "请输入终点站：";
	cin >> b;
	int y = findvex(b, G);
	if (x == -1 || y == -1)
	{
		cout << "未查到站点信息" << endl;
		return;
	}
	find1(G,x,y);
	find2(G,x, y);
}

void showgraph(GH* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		AR* p = G->N[i].next;
		cout << G->vexname[i];
		while (p)
		{
			cout << "--" << G->vexname[p->index];
			p = p->next;
		}
		cout << endl;
	}
}

int main()
{
	GH G;
	creatgraph(&G);
	busLine(&G);
	//showgraph(&G);
	return 0;
}