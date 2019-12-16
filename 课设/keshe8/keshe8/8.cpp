#pragma warning( disable : 4996)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200
#define mmax 0x3ffffff

using namespace std;

typedef struct arcnode
{
	int index;
	int val;
	struct arcnode* next;
}AR;
typedef struct MyGraph
{
	int type;
	int arcnum, vexnum;
	char** vexname;
	AR* N;
}GH;

int findvex(char* s, GH* G)
{
	int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (strcmp(s, G->vexname[i]) == 0)
			return i;
	}
	printf("read file erro\n");
	exit(-1);
}

void creatgraph(GH* G)
{
	FILE* fp;
	AR* p;
	int i, j, k;
	int w;
	char c1[4], c2[4], c3[40];
	char filename[] = "8.txt";
	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		printf("read file erro\n");
		exit(-1);
	}
	fscanf(fp, "%d", &k);
	G->arcnum = 0;
	G->type = 1;
	G->vexnum = k;
	G->vexname = (char**)malloc(k * sizeof(char*));
	G->N = (AR*)malloc(k * sizeof(AR));
	for (i = 0; i < k; i++)
	{
		fscanf(fp, "%s", c1);
		G->vexname[i] = (char*)malloc(strlen(c1) * sizeof(char));
		strcpy(G->vexname[i], c1);
		G->N[i].next = NULL;
	}

	while (fscanf(fp, "%s%s%s", c1, c2, c3) != EOF)
	{
		w = atoi(c3);
		(G->arcnum)++;
		i = findvex(c1, G);
		j = findvex(c2, G);
		p = (AR*)malloc(sizeof(AR));
		p->index = j;
		p->val = w;
		p->next = G->N[i].next;
		G->N[i].next = p;
	}
	fclose(fp);
}

void showgraph(GH* G)
{
	int i;
	AR* p;
	for (i = 0; i < G->vexnum; i++)
	{
		cout << G->vexname[i];
		p = G->N[i].next;
		while (p)
		{
			cout << "--" << G->vexname[p->index] << "(" << p->val << ")";
			p = p->next;
		}
		cout << endl;
	}
	cout << endl;
}

void showRoute(GH* G, int(*p)[200], int i, int j)
{
	if (p[i][j] == i)
	{
		cout << G->vexname[i];
		return;
	}
	showRoute(G, p, i, p[i][j]);
	cout << "--" << G->vexname[p[i][j]];
}
void showRouteD(GH* G, int* pre, int i, int j)
{
	if (pre[j] == i)
	{
		cout << G->vexname[i];
		return;
	}
	showRouteD(G, pre, i, pre[j]);
	cout << "--" << G->vexname[pre[j]];
}

void floyd(GH* G)
{
	int d[MAXN][MAXN], p[MAXN][MAXN];
	int i, j, k, l;
	l = G->vexnum;

	for (i = 0; i < l; i++)
		for (j = 0; j < l; j++)
		{
			if (i == j) d[i][j] = 0;
			else d[i][j] = mmax;
			p[i][j] = i;
		}
	for (i = 0; i < l; i++)
	{
		AR* p;
		p = G->N[i].next;
		while (p)
		{
			d[i][p->index] = p->val;
			p = p->next;
		}
	}
	for (k = 0; k < l; k++)
		for (i = 0; i < l; i++)
			for (j = 0; j < l; j++)
				if (d[i][j] > d[i][k] + d[k][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = p[k][j];
				}
	for (i = 0; i < l; i++)
		for (j = 0; j < l; j++)
		{
			if (d[i][j] == mmax || i == j) continue;
			cout << G->vexname[i] << "到" << G->vexname[j] << "的最短路径长度为" << d[i][j] << endl;
			cout << "其最短路径为：";
			k = p[i][j];
			showRoute(G, p, i, j);
			cout << "--" << G->vexname[j] << endl;
		}
}

void dijkstra(GH* G)
{
	int d[MAXN][MAXN], pre[MAXN];
	bool vis[MAXN];
	int i, j, k, l, m;
	l = G->vexnum;

	for (i = 0; i < l; i++)
		for (j = 0; j < l; j++)
		{
			if (i == j) d[i][j] = 0;
			else d[i][j] = mmax;
			vis[i] = 0;
		}
	for (i = 0; i < l; i++)
	{
		for (int a = 0; a < l; a++)
			pre[a] = a, vis[a] = 0;
		for (j = 0; j < l; j++)
		{
			int k = 0, mmin = mmax;
			for (m = 0; m < l; m++)
				if (mmin > d[i][m] && !vis[m])
				{
					mmin = d[m][i];
					k = m;
				}
			vis[k] = 1;
			AR* p;
			p = G->N[k].next;
			while (p)
			{
				if (!vis[p->index] && d[i][p->index] > d[i][k] + p->val)
				{
					d[i][p->index] = d[i][k] + p->val;
					pre[p->index] = k;
				}
				p = p->next;
			}
		}
		for (j = 0; j < l; j++)
		{
			if (d[i][j] == mmax || i == j) continue;
			cout << G->vexname[i] << "到" << G->vexname[j] << "的最短路径长度为" << d[i][j] << endl;
			cout << "其最短路径为：";
			showRouteD(G, pre, i, j);
			cout << "--" << G->vexname[j] << endl;
		}
	}
}

int main()
{
	GH G;
	creatgraph(&G);
	showgraph(&G);
	system("pause");
	system("cls");
	cout << "如下为floyd算法求解结果：" << endl;
	floyd(&G);
	system("pause");
	system("cls");
	cout << "如下为dijkstra算法求解结果：" << endl;
	dijkstra(&G);
	return 0;
}