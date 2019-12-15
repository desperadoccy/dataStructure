#pragma warning( disable : 4996)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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

int main()
{
	GH G;
	creatgraph(&G);
	showgraph(&G);
	return 0;
}