#pragma warning( disable : 4996)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2000

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
	AR* R;
}GH;

int start[MAXN], End[MAXN];
int startCnt, endCnt;
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
	char filename[] = "7.txt";
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
	G->R = (AR*)malloc(k * sizeof(AR));
	for (i = 0; i < k; i++)
	{
		fscanf(fp, "%s", c1);
		G->vexname[i] = (char*)malloc(strlen(c1) * sizeof(char));
		strcpy(G->vexname[i], c1);
		G->N[i].next = NULL;
		G->R[i].next = NULL;
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
		p = (AR*)malloc(sizeof(AR));
		p->index = i;
		p->val = w;
		p->next = G->R[j].next;
		G->R[j].next = p;
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

void TopologicalSort(GH* G, int* ve)
{
	int i, top = 0;
	AR* p;
	int in[MAXN], stack[MAXN];             
	for (i = 0; i < G->vexnum; i++)
	{
		in[i] = 0, ve[i] = 0;
	}
	for (i = 0; i < G->vexnum; i++)
	{
		p = G->N[i].next;
		while (p)
		{
			in[p->index]++;
			p = p->next;
		}
	}
	for (i = 0; i < G->vexnum; i++)
		if (!in[i])
			stack[top++] = i, start[startCnt++] = i;
	while (top)
	{
		int x = stack[--top];
		AR* p;
		p = G->N[x].next;
		while (p)
		{
			in[p->index]--;
			ve[p->index] = (ve[x] + p->val) > ve[p->index] ? (ve[x] + p->val) : ve[p->index];
			if (!in[p->index]) stack[top++] = p->index;
			p = p->next;
		}
	}


}

void ReTopologicalSort(GH* G, int* vl)
{
	int i, top = 0;
	AR* p;
	int out[MAXN], stack[MAXN];
	for (i = 0; i < G->vexnum; i++)
	{
		out[i] = 0, vl[i] = 0;
	}
	for (i = 0; i < G->vexnum; i++)
	{
		p = G->N[i].next;
		while (p)
		{
			out[i]++;
			p = p->next;
		}
	}
	for (i = 0; i < G->vexnum; i++)
		if (!out[i])
			stack[top++] = i, End[endCnt++] = i;
	while (top)
	{
		int x = stack[--top];
		AR* p;
		p = G->R[x].next;
		while (p)
		{
			out[p->index]--;
			vl[p->index] = (vl[x] + p->val) > vl[p->index] ? (vl[x] + p->val) : vl[p->index];
			if (!out[p->index]) stack[top++] = p->index;
			p = p->next;
		}
	}


}

void init(GH* G, GH* ANS, int* vl, int* ve)
{
	AR* p, * p1;
	int k = G->vexnum;
	ANS->arcnum = 0;
	ANS->type = 0;
	ANS->vexnum = k;
	ANS->vexname = (char**)malloc(k * sizeof(char*));
	ANS->N = (AR*)malloc(k * sizeof(AR));
	for (int i = 0; i < k; i++)
	{
		ANS->vexname[i] = (char*)malloc(strlen(G->vexname[i]) * sizeof(char));
		strcpy(ANS->vexname[i], G->vexname[i]);
		ANS->N[i].next = NULL;
	}
	for (int i = 0; i < k; i++)
	{
		if (vl[i] != ve[i]) continue;
		p1 = G->N[i].next;
		while (p1)
		{
			if (vl[p1->index] == ve[p1->index])
			{
				p = (AR*)malloc(sizeof(AR));
				p->index = p1->index;
				p->val = p1->val;
				p->next = ANS->N[i].next;
				ANS->N[i].next = p;
			}
			p1 = p1->next;
		}
	}
}
void dfs(GH* ANS, int* route, int* top, int v, int end)
{
	AR* p;
	if (v == end)
	{
		for (int i = 0; i < *top; i++)
			cout << ANS->vexname[route[i]] << " -- ";
		cout << ANS->vexname[v] << endl;
		return;
	}
	route[(*top)++] = v;
	p = ANS->N[v].next;
	while (p)
	{	
		dfs(ANS, route, top, p->index, end);
		p = p->next;
	}
	(*top)--;
}

void CriticalPathSolution(GH* G, GH* ANS)
{
	int vl[MAXN],ve[MAXN];
	int route[MAXN], top = 0;
	TopologicalSort(G, ve);	//拓扑排序
	ReTopologicalSort(G, vl); //反拓扑排序
	for (int i = 0; i < G->vexnum; i++)
		vl[i] = ve[G->vexnum - 1] - vl[i];
	//构造关键路径图
	init(G, ANS, vl, ve);
	printf("\n%12s", "vexname");
	for (int i = 0; i < G->vexnum; i++)
		printf("%8s ", G->vexname[i]);
	cout << endl;
	printf("%12s", "ve");
	for (int i = 0; i < G->vexnum; i++)
		printf("%8d ", ve[i]);
	cout << endl;
	printf("%12s", "vl");
	for (int i = 0; i < G->vexnum; i++)
		printf("%8d ", vl[i]);
	cout << endl << endl;
	cout << "有如下关键路径" << endl;
	//遍历关键路径
	for (int i = 0; i < startCnt; i++)
		for (int j = 0; j < endCnt; j++)
			dfs(ANS, route, &top, start[i], End[j]);
}

int main()
{
	GH G, ANS;
	creatgraph(&G);
	cout << "原图如下" << endl;
	showgraph(&G);
	CriticalPathSolution(&G, &ANS);
	return 0;
}