#pragma warning( disable : 4996)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200
#define mmax 999999

using namespace std;

typedef struct node
{
	int v1, v2;
	float val;
}node;
typedef struct node2
{
	int pre;
	float val;
}node2;
typedef struct arcnode
{
	int index;
	float val;
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
	float w;
	char c1[4], c2[4], c3[40];
	char filename[] = "6.txt";
	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		printf("read file erro\n");
		exit(-1);
	}
	fscanf(fp, "%d", &k);
	G->arcnum = 0;
	G->type = 0;
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
		w = atof(c3);
		(G->arcnum)++;
		i = findvex(c1, G);
		j = findvex(c2, G);
		p = (AR*)malloc(sizeof(AR));
		p->index = j;
		p->val = w;
		p->next = G->N[i].next;
		G->N[i].next = p;
		if (G->type == 0)
		{
			p = (AR*)malloc(sizeof(AR));
			p->index = i;
			p->val = w;
			p->next = G->N[j].next;
			G->N[j].next = p;
		}
	}
	fclose(fp);
}

void showgraph(GH* G)
{
	int i;
	AR* p;
	for (i = 0; i < G->vexnum; i++)
	{
		cout << endl << G->vexname[i];
		p = G->N[i].next;
		while (p)
		{
			cout << "--" << G->vexname[p->index] << "(" << p->val << ")";
			p = p->next;
		}
	}
	cout << endl;
}

void init(GH* G, GH* T)
{
	int k = G->vexnum;
	T->arcnum = 0;
	T->type = 0;
	T->vexnum = k;
	T->vexname = (char**)malloc(k * sizeof(char*));
	T->N = (AR*)malloc(k * sizeof(AR));
	for (int i = 0; i < k; i++)
	{
		T->vexname[i] = (char*)malloc(strlen(G->vexname[i]) * sizeof(char));
		strcpy(T->vexname[i], G->vexname[i]);
		T->N[i].next = NULL;
	}
}

void prim(GH* G, GH* T)
{
	AR* p;
	int i, j;
	bool v[MAXN];
	node2 d[MAXN];
	init(G, T);
	for (i = 0; i < G->vexnum; i++)
		d[i].val = mmax, v[i] = 0;
	d[0].val = 0;
	p = G->N[0].next;
	while (p)
	{
		d[p->index].pre = 0;
		d[p->index].val = p->val;
		p = p->next;
	}

	for (i = 0; i < G->vexnum; i++)
	{
		int x = 1;
		for (j = 1; j < G->vexnum; j++)
		{
			if (!v[j] && (x == 1 || d[j].val < d[x].val))
				x = j;
		}
		v[x] = 1;
		AR* p1;
		p1 = (AR*)malloc(sizeof(AR));
		p1->index = x;
		p1->val = d[x].val;
		p1->next = T->N[d[x].pre].next;
		T->N[d[x].pre].next = p1;
		p1 = (AR*)malloc(sizeof(AR));
		p1->index = d[x].pre;
		p1->val = d[x].val;
		p1->next = T->N[x].next;
		T->N[x].next = p1;
		
		p = G->N[x].next;
		while (p)
		{
			if (!v[p->index])
			{
				if (p->val < d[p->index].val)
				{
					d[p->index].pre = x;
					d[p->index].val = p->val;
				}
			}
			p = p->next;
		}
	}

}

int pa[MAXN];
node E[MAXN * MAXN];
int findpa(int v)
{
	if (pa[v] == v)
		return v;
	else return findpa(pa[v]);
}

void unionVex(int v1, int v2)
{
	pa[findpa(v2)] = findpa(v1);
}

void kruscal(GH* G, GH* T)
{
	int i, j, cnt = 0, k = 0;
	//init
	for (i = 0; i < G->vexnum; i++)
		pa[i] = i;
	init(G, T);
	for (i = 0; i < G->vexnum; i++)
	{
		AR* p;
		p = G->N[i].next;
		while (p)
		{
			E[cnt].v1 = i;
			E[cnt].v2 = p->index;
			E[cnt].val = p->val;
			cnt++;
			p = p->next;
		}
	}
	for (i = 0; i < G->vexnum; i++)
		for (j = 0; j < G->vexnum - i - 1; j++)
		{
			if (E[j].val > E[j + 1].val)
			{
				node t;
				t = E[j];
				E[j] = E[j + 1];
				E[j + 1] = E[j];
			}
		}
	//每个边重复了两次
	for (i = 0; i < cnt; i += 2)
	{
		if (k == G->vexnum - 1) break;
		if (findpa(E[i].v1) != findpa(E[i].v2))
		{
			unionVex(E[i].v1, E[i].v2);
			AR* p;
			p = (AR*)malloc(sizeof(AR));
			p->index = E[i].v1;
			p->val = E[i].val;
			p->next = T->N[E[i].v2].next;
			T->N[E[i].v2].next = p;
			p = (AR*)malloc(sizeof(AR));
			p->index = E[i].v2;
			p->val = E[i].val;
			p->next = T->N[E[i].v1].next;
			T->N[E[i].v1].next = p;
			k++;

		}
	}
}

int main()
{
	GH G, T1, T2;
	creatgraph(&G);
	showgraph(&G);
	prim(&G, &T1);
	kruscal(&G, &T2);
	showgraph(&T1);
	showgraph(&T2);
	return 0;
}