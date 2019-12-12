#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#define N 1000

using namespace std;

//指定长度字符串转化为整型
int charToInt(char *s,int len)
{
	int ans = 0;
	for (int i = 0; i < len; i++)
	{
		ans *= 10;
		ans = ans + (s[i] - '0');
	}
	return ans;
}

void solve(char *s,int len)
{
	int cnt = 0, lost = -1;
	bool flag = 0;
	for (int i = 0; i < len/2; i++) 
	{
		int ans[N];
		lost = -1;
		cnt = 0;
		int j;
		int l = i + 1;
		int num = 0;
		for (j = 0; j < len; j += l)
		{
			if (j == 0)
			{
				num = charToInt(s, l);
				ans[cnt++] = num;
			}
			else
			{
				int a = charToInt(s + j, l);	//下一位不进位
				int b = charToInt(s + j, l + 1);	//下一位进位
				if (flag)	//已经有过一对相邻数字差值为2
				{
					if (num + 1 == a)
					{
						ans[cnt++] = a;
						num = a;
					}else if(num+1==b)
					{
						ans[cnt++] = b;
						num = b;
						l++;
					}else
					{
						break;
					}
				}
				else	//没有一对相邻数字差值为2
				{
					if (num + 1 == a)
					{
						ans[cnt++] = a;
						num = a;
					}else if (num + 1 == b)
					{
						ans[cnt++] = b;
						num = b;
						l++;
					}else if (num + 2 == a) 
					{
						flag = 1;
						ans[cnt++] = a;
						lost = num + 1;
						num = a;
					}else if (num + 2 == b) 
					{
						flag = 1;
						ans[cnt++] = b;
						lost = num + 1;
						num = b;
						l++;
					}else
					{
						break;
					}
				}
			}
		}
		if (j == len) 
		{
			for (int k = 0; k < cnt; k++)
			{
				cout << ans[k] << " ";
			}
			if (lost == -1)
			{
				cout << "没有漏掉的数字" << endl;
			}
			else {
				cout << "漏掉的数字为" << lost << endl;
			}
			return;
		}
	}
	cout << "字符串不合法，请重试" << endl;
	return;
}
int main()
{
	while (1)
	{
		cout << "请输入字符串： ";
		char s[N];
		cin >> s;
		if (s[0] == '#')
			return 0;
		bool flag = 0;
		int l = strlen(s);
		for (int i = 0; i < l; i++)
		{
			if (s[i] > '9' || s[i] < '0')
			{
				flag = 1;
			}
		}
		if (flag)
		{
			cout << "输入不合法，请重试" << endl;
			continue;
		}
		solve(s,l);
	}
	return 0;
}