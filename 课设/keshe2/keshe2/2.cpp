#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

struct node1{
	double a[100];
	int top;
};
struct node2{
	char a[100];
	int top;
};

bool cmp(char a, char b)
{
	if (a == '(') return 1;
	if (a == '+' || a == '-')
	{
		if (b == '+' || b == '-')
		{
			return 0;
		}
		else
			return 1;
	}
	else
		return 0;
}

int main()
{
	while (1)
	{

		node1 num;	//操作数栈
		node2 ope;  //操作符栈
		char ans[100][100];
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
				ans[i][j] = '\0';
		int anslen = -1;
		string test;
		int pos = 0;
		ope.top = -1;
		num.top = -1;
		cout << "请输入要计算的算式" << endl;
		cin >> test;
		if (test[0] == '#') return 0;
		for (int i = 0; i < test.length() - 1; i++)
			if (test[i] != '+' && test[i] != '-' && test[i] != '*' && test[i] != '/' && test[i] != '(' && test[i] != ')' && test[i] != '.' && (test[i] > '9' || test[i] < '0'))
			{
				cout << "格式出错" << endl;
				return main();
			}
		test.append("#"); //添加结尾标志
		bool flag = 0;
		int numcnt = 0;
		int optcnt = 0;
		while (1)
		{
			char t = test[pos];
			switch (t)
			{
			case '(':
				ope.a[++ope.top] = '(';
				break;
			case ')':
				while (ope.a[ope.top] != '(' && ope.top != -1)
				{
					ans[++anslen][0] = ope.a[ope.top--];
				}
				if (ope.top == -1)
				{
					cout << "格式出错" << endl;
					return main();
				}
				ope.top--;
				break;
			case '*':
				optcnt++;
				while (!cmp(ope.a[ope.top], '*') && ope.top != -1)
				{
					ans[++anslen][0] = ope.a[ope.top--];
				}
				ope.a[++ope.top] = '*';
				break;
			case '/':
				optcnt++;
				while (!cmp(ope.a[ope.top], '/') && ope.top != -1)
				{
					ans[++anslen][0] = ope.a[ope.top--];
				}
				ope.a[++ope.top] = '/';
				break;
			case '+':
				optcnt++;
				while (!cmp(ope.a[ope.top], '+') && ope.top != -1)
				{
					ans[++anslen][0] = ope.a[ope.top--];
				}
				ope.a[++ope.top] = '+';
				break;
			case '-':
				optcnt++;
				while (!cmp(ope.a[ope.top], '-') && ope.top != -1)
				{
					ans[++anslen][0] = ope.a[ope.top--];
				}
				ope.a[++ope.top] = '-';
				break;
			case '#':
				flag = 1;
				while (ope.top != -1)
				{
					if (ope.a[ope.top] == '(')
					{
						cout << "格式出错" << endl;
						return main();
					}
					ans[++anslen][0] = ope.a[ope.top--];
				}
				break;
			default:
				numcnt++;
				anslen++;
				int len = -1;
				int cnt = -1;
				while ((test[pos + 1] <= '9' && test[pos + 1] >= '0') || test[pos + 1] == '.')
				{
					if (test[pos] == '.') cnt++;
					if (cnt > 0) { cout << "格式错误" << endl; return main(); }
					ans[anslen][++len] = test[pos];
					pos++;
				}
				ans[anslen][++len] = test[pos];
				break;
			}
			if (flag) break;
			pos++;
		}
		if (optcnt + 1 != numcnt) { cout << "格式错误" << endl; return main(); }
		for (int i = 0; i <= anslen; i++)
		{
			for (int j = 0; j < strlen(ans[i]); j++)
				cout << ans[i][j];
			cout << " ";
		}
		cout << endl;
		//计算后缀表达式

		for (int i = 0; i <= anslen; i++)
		{
			if (ans[i][0] == '+')
			{
				double tmp, a, b;
				a = num.a[num.top--];
				b = num.a[num.top--];
				tmp = b + a;
				//cout << b << "+" << a << "=" << tmp << endl;
				num.a[++num.top] = tmp;
			}
			else if (ans[i][0] == '-')
			{
				double tmp, a, b;
				a = num.a[num.top--];
				b = num.a[num.top--];
				tmp = b - a;
				//cout << b << "-" << a << "=" << tmp << endl;
				num.a[++num.top] = tmp;
			}
			else if (ans[i][0] == '*')
			{
				double tmp, a, b;
				a = num.a[num.top--];
				b = num.a[num.top--];
				tmp = b * a;
				//cout << b << "*" << a << "=" << tmp << endl;
				num.a[++num.top] = tmp;
			}
			else if (ans[i][0] == '/')
			{
				double tmp, a, b;
				a = num.a[num.top--];
				b = num.a[num.top--];
				tmp = b / a;
				//cout << b << "/" << a << "=" << tmp << endl;
				num.a[++num.top] = tmp;
			}
			else
			{
				double tmp;
				stringstream ss;
				ss << ans[i];
				ss >> tmp;
				ss.clear();
				num.a[++num.top] = tmp;
			}
		}
		printf("%.2lf\n", num.a[num.top]);
	}
	return 0;
}