#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;

typedef struct tree {
	char c;
	int pos;
	tree* left, * right;
}tree;

typedef struct node {
	int pos;
	int cnt;
	tree* treenode;
}node;

class Heap {
public:
	node a[26];
	int tail;
	Heap()
	{
		tail = 0;
		for (int i = 0; i < 26; i++)
			a[i].pos = i, a[i].cnt = 0, a[i].treenode = NULL;
	}
	bool isempty()
	{
		if (tail == 1)
			return 1;
		else
			return 0;
	}
	void push(node x)
	{
		a[tail++] = x;
		int pa = (tail - 1) / 2;
		int child = tail - 1;
		while (pa >= 0)
		{
			if (a[pa].cnt > a[child].cnt)
			{
				node t = a[child];
				a[child] = a[pa];
				a[pa] = t;
				child = pa;
				pa = (pa - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
	node pop()
	{
		node t = a[0];
		a[0] = a[--tail];
		int pa = 0;
		int child = 1;
		while (child <= tail - 1)
		{
			if ((child != tail - 1) && (a[child].cnt) > a[child + 1].cnt)
			{
				child = child + 1;
			}
			if (a[child].cnt < a[pa].cnt)
			{
				node tmp = a[pa];
				a[pa] = a[child];
				a[child] = tmp;
				pa = child;
				child = 2 * child + 1;
			}
			else
			{
				break;
			}
		}
		return t;
	}
};

void preorder(tree* T, char (&encode)[26][100])
{          
	if (!T) return;
	tree* stack[100];
	int top = 0;
	tree* p, * p1;
	p = T;
	do
	{
		while (p)
		{
			stack[top++] = p;
			p = p->left;
		}
		p1 = NULL;
		while (top)
		{
			p = stack[top - 1];
			if (p->right == p1)	//无右节点或者已经被访问出栈
			{
				int i;
				if (!p->left && !p->right)
				{
					for (i = 1; i < top; i++)
					{
						encode[p->pos][i - 1] = stack[i]->c;
					}
					encode[p->pos][top - 1] = p->c;
				}
				top--;
				p1 = p;
			}
			else
			{
				p = p->right;
				break;
			}

		}
	} while (top);
}

void huffman(tree* T, Heap* heap, int cnt[], char (&encode)[26][100])
{
	for (int i = 0; i < 26; i++)
	{
		node t;
		t.pos = i;
		t.cnt = cnt[i];
		t.treenode = (tree*)malloc(sizeof(tree));
		t.treenode->c = '2';
		t.treenode->pos = i;
		t.treenode->left = NULL;
		t.treenode->right = NULL;
		heap->push(t);
	}
	while (!heap->isempty())
	{
		node t1 = heap->pop();
		node t2 = heap->pop();
		node t;
		t.cnt = t1.cnt + t2.cnt;
		t.pos = -1;
		t.treenode = (tree*)malloc(sizeof(tree));
		t.treenode->left = t1.treenode;
		t1.treenode->c = '0';
		t.treenode->right = t2.treenode;
		t2.treenode->c = '1';
		t.treenode->c = '2';
		T = t.treenode;
		heap->push(t);
	}
	preorder(T, encode);
}
int main()
{
	Heap heap;
	int cnt[26];
	char encode[26][100];
	tree* T = NULL;
	memset(cnt, 0, sizeof(int) * 26);
	memset(encode, 0, sizeof(char) * 2600);
	char str[100], c[1000];
	cout << "请输入你想要读取的文件路径：";
	cin >> str;
	fstream file(str);
	while (!file.eof())
	{
		file.getline(c, 1000);
		for (int i = 0; i < strlen(c); i++)
		{
			if (c[i] >= 'a' && c[i] <= 'z')
			{
				cnt[c[i]-'a']++;
			}
			if (c[i] == ' ') cout << " ";
			else cout << c[i];
		}
		cout << endl;
	}
	huffman(T, &heap, cnt, encode);
	for (int i = 0; i < 26; i++)
	{
		char ch = 'a' + i;
		cout << ch << ":";
		cout << encode[i] << endl;
	}
	file.close();
	return 0;
}
