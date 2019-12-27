#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int* f, * cnt;
int findpa(int x)
{
	if (f[x] == x)
		return x;
	else
		return f[x] = findpa(f[x]);
}

void Union(int x, int y)
{
	f[findpa(x)] = findpa(y);
}

int main()
{
	int n, m, i, j, M, a, b;
	cin >> n >> m;
	f = (int*)malloc(sizeof(int) * n);
	cnt = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		f[i] = i, cnt[i] = 0;
	for (i = 0; i < m; i++)
	{
		cin >> M;
		cin >> a;
		for (j = 1; j < M; j++)
		{
			cin >> b;
			Union(a-1, b-1);
		}
	}
	for (i = 0; i < n; i++)
	{
		cnt[findpa(i)]++;
	}
	int mmax = 0;
	for (i = 0; i < n; i++)
		if (mmax < cnt[i])
			mmax = cnt[i];
	cout << mmax << endl;
	return 0;
}