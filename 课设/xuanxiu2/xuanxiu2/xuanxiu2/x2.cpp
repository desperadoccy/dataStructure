#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <graphics.h>
#include <ctime>
#include <conio.h>
#include <windows.h>
#define N 2000

using namespace std;

typedef struct member
{
	char name[20];
	char birth[12];
	bool isMarried;
	char address[100];
	char death[12];
	bool isdeath;
}member;
typedef struct familytree
{
	member info;
	struct familytree* bro, * fir, * fa, * prebro;
}FT;
typedef struct node
{
	FT* p;
	int sx;
	int sy;
	int ex;
	int ey;
}widget;
typedef struct node2
{
	FT* node;
	int	deep;
}QUE;
char filename[20];

int menu_select()
{
	char i;
	do {
		system("cls");
		printf("1.创建最初家谱（从文件读入）\n");
		printf("2.打印家谱\n");
		printf("3.显示第n代人所有记录\n");
		printf("4.按姓名查询成员信息\n");
		printf("5.按出生日期查询成员信息\n");
		printf("6.查询两人关系\n");
		printf("7.为成员添加孩子\n");
		printf("8.删除某成员\n");
		printf("9.修改某成员信息\n");
		printf("0.退出\n");
		printf("请输入选择序号(0-9):");
		i = getchar();
	} while (i < '0' || i>'9');
	return (i - '0');
}

FT* create(FT* A, FT* fa, FT* prebro, fstream& file)
{
	char t[20];
	FT* p, * pre;
	p = A, pre = NULL;
	if (!file.eof())
	{
		file.getline(t, 20);
		if (t[0] == '#' || t[0] == '\0')
		{
			return NULL;
		}
		A->fa = fa;
		A->prebro = prebro;
		strcpy_s(A->info.name, t);
		file.getline(A->info.birth, 12);
		file.getline(t, 20);
		if (t[0] == '1')
			A->info.isMarried = 1;
		else
			A->info.isMarried = 0;
		file.getline(A->info.address, 100);
		file.getline(t, 20);
		if (t[0] == '1')
			A->info.isdeath = 1;
		else
			A->info.isdeath = 0;
		file.getline(A->info.death, 12);
		A->fir = (FT*)malloc(sizeof(FT));
		A->bro = (FT*)malloc(sizeof(FT));
		A->fir = create(A->fir, A, NULL, file);
		A->bro = create(A->bro, A->fa, A, file);
		return A;
	}
	return NULL;
}

void CreateFT(FT* A)
{
	cout << "请输入文件名：";
	cin >> filename;
	fstream file(filename);
	if (!file)
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	//递归建树
	create(A, NULL, NULL, file);
	file.close();
	cout << "创建成功" << endl;
}

void save(FT* A, fstream& file)
{
	if (!A)
	{
		file << '#' << endl;
		return;
	}
	file << A->info.name << endl;
	file << A->info.birth << endl;
	if (A->info.isMarried)
		file << '1' << endl;
	else
		file << '0' << endl;
	file << A->info.address << endl;
	if (A->info.isdeath)
	{
		file << '1' << endl;
		file << A->info.death << endl;
	}
	else
	{
		file << '0' << endl;
		file << "0000-00-00" << endl;
	}
	save(A->fir, file);
	save(A->bro, file);
	return;
}
void Close(FT* A)
{
	fstream file(filename);
	//递归存储
	//先序遍历
	save(A, file);
	file.close();
}

void subPrint(FT* A, widget* data, int* cnt)
{
	//清空画布
	cleardevice();
	*cnt = 0;
	wchar_t name[20];

	//画出退出按钮
	RECT r_exit = { 535,405,600,440 };
	rectangle(535, 405, 600, 440);
	drawtext(_T("退出"), &r_exit, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//画出返回按钮
	RECT r_return = { 430, 405, 495, 440 };
	rectangle(430, 405, 495, 440);
	drawtext(_T("返回"), &r_return, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//画出父亲结点
	RECT r_pa = { 260,100,380,150 };
	rectangle(260, 100, 380, 150);
	//信息转换，utf-8转为Unicode，char转为wchar
	int nRet = MultiByteToWideChar(CP_ACP, 0, A->info.name, 20, name, 20);
	drawtext(name, &r_pa, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//画出所有子结点
	FT* p = A->fir;
	while (p)
	{
		data[*cnt].p = p;
		(*cnt)++;
		p = p->bro;
	}
	int x = (640 - 60 * (*cnt)) / ((*cnt) + 1);
	int i, sx = x;
	for (i = 0; i < *cnt; i++)
	{
		data[i].sx = sx;
		data[i].sy = 270;
		data[i].ex = sx + 60;
		data[i].ey = 300;
		RECT r_son = { sx,270,sx + 60,300 };
		rectangle(sx, 270, sx + 60, 300);
		line(sx + 30, 270, 320, 150);
		int nRet = MultiByteToWideChar(CP_ACP, 0, data[i].p->info.name, 20, name, 20);
		drawtext(name, &r_son, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		sx += x + 60;
	}
}

void Print(FT* A)
{
	if (!strlen(filename))
	{
		cout << "未导入初始家谱" << endl;
		return;
	}
	// 设置随机函数种子
	srand((unsigned)time(NULL));

	// 初始化图形模式
	initgraph(640, 480);

	// 设置字体
	settextstyle(16, 8, _T("Courier"));

	// 设置颜色
	COLORREF color = RGB(252, 253, 248);
	setbkcolor(color);
	settextcolor(BLACK);
	setlinecolor(BLACK);

	// 定义鼠标参数
	MOUSEMSG m;

	FT* tree = A;
	widget data[20];
	int cnt = 0, i;
	subPrint(A, data, &cnt);
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//退出
			if (m.x <= 600 && m.x >= 535 && m.y >= 405 && m.y <= 440)
			{
				break;
			}
			//返回
			if (m.x <= 495 && m.x >= 430 && m.y >= 405 && m.y <= 440)
			{
				if (tree->fa != NULL)
				{
					subPrint(tree->fa, data, &cnt);
					tree = tree->fa;
				}
			}
			//选择子结点
			for (i = 0; i < cnt; i++)
			{
				if (m.x >= data[i].sx && m.x <= data[i].ex && m.y >= data[i].sy && m.y <= data[i].ey)
				{
					tree = data[i].p;
					subPrint(tree, data, &cnt);
				}
			}
		}
	}

	// 关闭图形模式
	closegraph();

}

void printInfo(FT* A)
{
	cout << "姓名：" << A->info.name << endl;
	cout << "生日：" << A->info.birth << endl;
	cout << "婚否：";
	if (A->info.isMarried)
	{
		cout << "是" << endl;
	}
	else
	{
		cout << "否" << endl;
	}
	cout << "地址：" << A->info.address << endl;
	cout << "健在否：";
	if (A->info.isdeath)
	{
		cout << "否" << endl;
		cout << "死亡日期：" << A->info.death << endl;
	}
	else
	{
		cout << "是" << endl;
	}
	cout << endl;
}

void PrintN(FT* A)
{
	if (!strlen(filename))
	{
		cout << "未导入初始家谱" << endl;
		return;
	}
	int n;
	cout << "请输入要查询的代数n：";
	cin >> n;
	if (n == 0)
	{
		cout << "n不为0！" << endl;
		return;
	}
	int head = 0, tail = 0;
	QUE c[N];
	c[tail].node = A;
	c[tail++].deep = 1;
	while (head != tail)
	{
		QUE t = c[head++];
		if (t.deep == n)
		{
			printInfo(t.node);
		}
		FT* tmp = t.node;
		if (t.node->fir)
		{
			c[tail].node = t.node->fir;
			c[tail++].deep = t.deep + 1;
		}
		while (tmp->bro)
		{
			tmp = tmp->bro;
			if (t.deep == n)
			{
				printInfo(tmp);
			}
			if (tmp->fir)
			{
				c[tail].node = tmp->fir;
				c[tail++].deep = t.deep + 1;
			}
		}
	}
}

void dfsSearchByName(FT* A, char* name)
{
	if (!strcmp(A->info.name, name))
	{
		cout << "本人：" << endl;
		printInfo(A);
		cout << "其父亲：" << endl;
		if (A->fa)
			printInfo(A->fa);
		else
			cout << "族谱中无其父亲信息" << endl;
		cout << "其孩子：" << endl;
		if (A->fir)
		{
			FT* p = A->fir;
			printInfo(p);
			while (p->bro)
			{
				p = p->bro;
				printInfo(p);
			}
		}
		else
			cout << "族谱中无其孩子信息" << endl;
	}
	if (A->fir)
		dfsSearchByName(A->fir, name);
	if (A->bro)
		dfsSearchByName(A->bro, name);
}

void SearchByName(FT* A)
{
	if (!strlen(filename))
	{
		cout << "未导入初始家谱" << endl;
		return;
	}
	char name[20];
	cout << "请输入要查询的成员姓名：";
	cin >> name;
	dfsSearchByName(A, name);
	cout << "查询完毕" << endl;
}

void dfsSearchByDate(FT* A, char* name)
{
	if (!strcmp(A->info.birth, name))
	{
		cout << "本人：" << endl;
		printInfo(A);
		cout << "其父亲：" << endl;
		if (A->fa)
			printInfo(A->fa);
		else
			cout << "族谱中无其父亲信息" << endl;
		cout << "其孩子：" << endl;
		if (A->fir)
		{
			FT* p = A->fir;
			printInfo(p);
			while (p->bro)
			{
				p = p->bro;
				printInfo(p);
			}
		}
		else
			cout << "族谱中无其孩子信息" << endl;
	}
	if (A->fir)
		dfsSearchByDate(A->fir, name);
	if (A->bro)
		dfsSearchByDate(A->bro, name);
}

void SearchByDate(FT* A)
{
	if (!strlen(filename))
	{
		cout << "未导入初始家谱" << endl;
		return;
	}
	char data[12];
	int year, month, day;
	cout << "请输入要查询的出生日期：";
	while (1)
	{
		cout << "输入年份：";
		cin >> year;
		if (year < 10000 && year >= 0)
			break;
		else
			cout << "格式错误!" << endl;
	}
	while (1)
	{
		cout << "输入月份：";
		cin >> month;
		if (month <= 12 && month >= 1)
			break;
		else
			cout << "格式错误!" << endl;
	}
	while (1)
	{
		cout << "输入日数：";
		cin >> day;
		if (day <= 31 && day >= 1)
			break;
		else
			cout << "格式错误!" << endl;
	}
	_itoa(year, data, 10);
	data[4] = '-';
	if (month / 10)
		_itoa(month, data + 5, 10);
	else
	{
		data[5] = '0';
		_itoa(month, data + 6, 10);
	}
	data[7] = '-';
	if (day / 10)
		_itoa(day, data + 8, 10);
	else
	{
		data[8] = '0';
		_itoa(day, data + 9, 10);
	}
	cout << "查询的生日为" << data << endl;
	dfsSearchByDate(A, data);
	cout << "查询完毕" << endl;
}

int Finds(FT*A,FT*S)
{
	int a = -1, b = -1;
	if (A == S)
		return 0;
	else
	{
		if (A->fir)
		{
			a = Finds(A->fir, S) + 1;
		}
		if (A->bro)
		{
			b = Finds(A->bro, S);
		}
	}
	if (a <=0&&b<0)
		return -1;
	else
		return a>b?a:b;
}

int LCA(FT* A, FT* T1, FT* T2,FT *fa)
{
	if (A == T1 || A == T2)
	{
		if (A == T1) fa = T1;
		else fa = T2;
		return Finds(A, T1) - Finds(A, T2);
	}
	int pos1 = Finds(A->fir, T1)+1;
	int pos2 = Finds(A->fir, T2)+1;
	if (pos1==0&&pos2==0)
	{
		return LCA(A->bro, T1, T2,fa);
	}
	else if (pos1==0&&pos2>0)
	{
		fa = A;
		pos1 = Finds(A->bro, T1);
		return pos1-pos2;
	}
	else if (pos2 == 0 && pos1 > 0)
	{
		fa = A;
		pos2 = Finds(A->bro, T2);
		return pos1 - pos2;
	}
	else
	{
		return LCA(A->fir, T1, T2,fa);
	}
}

FT* dfsRelation(FT* A, char* name)
{
	if (!strcmp(A->info.name, name))
	{
		printInfo(A);
		cout << "是否为查询对象？(Y/N):";
		cin.ignore();
		char c = getchar();
		if (c == 'y' || c == 'Y') return A;
		else return NULL;
	}
	FT* p1 = NULL, * p2 = NULL;
	if (A->fir) p1 = dfsRelation(A->fir, name);
	if (p1) return p1;
	if (A->bro) p2 = dfsRelation(A->bro, name);
	if (p2) return p2;
	return NULL;
}

void Relation(FT* A)
{
	if (!strlen(filename))
	{
		cout << "未导入初始家谱" << endl;
		return;
	}
	char Seniority[8][20] = { "兄弟","父亲","祖父","曾祖","玄祖","高祖","太祖","元祖" };
	char name1[20], name2[20];
	FT* T1, * T2,*fa=A;
	cout << "输入你要查找的两人姓名" << endl;
	cout << "输入第一个人的姓名：";
	cin.ignore();
	cin >> name1;
	T1=dfsRelation(A, name1);
	if (!T1)
	{
		cout << "查无此人" << endl;
		return;
	}
	cout << "输入第二个人的姓名：";
	cin.ignore();
	cin >> name2;
	T2 = dfsRelation(A, name2);
	if (!T2)
	{
		cout << "查无此人" << endl;
		return;
	}
	cout << "=========================================" << endl;
	cout << "结果如下" << endl;
	int ans= LCA(A, T1, T2, fa);
	cout << "他们相差" << abs(ans) << "代" << endl;
	if (!ans)
	{
		cout << T1->info.name << "和" << T2->info.name << "是兄弟关系" << endl;
	}
	else if (ans < 0)
	{
		ans = -1 * ans;
		int i = ans > 7 ? 7 : ans;
		cout << T1->info.name << "是" << T2->info.name << "的" << Seniority[i]<<"辈"<< endl;
	}
	else
	{
		int i = ans > 7 ? 7 : ans;
		cout << T2->info.name << "是" << T1->info.name << "的" << Seniority[i] << "辈" << endl;
	}
}

FT* dfsInsert(FT* A, char* name)
{
	if (!strcmp(A->info.name, name))
	{
		printInfo(A);
		cout << "是否为插入对象？(Y/N):";
		cin.ignore();
		char c = getchar();
		if (c == 'y' || c == 'Y') return A;
		else return NULL;
	}
	FT* p1 = NULL, * p2 = NULL;
	if (A->fir) p1 = dfsInsert(A->fir, name);
	if (p1) return p1;
	if (A->bro) p2 = dfsInsert(A->bro, name);
	if (p2) return p2;
	return NULL;
}

void Insert(FT* A)
{
	char c;
	if (!strlen(filename))
	{
		cout << "未导入初始家谱" << endl;
		return;
	}
	char name[20];
	cout << "输入要插入孩子的成员名字：";
	cin >> name;
	FT* fa = dfsInsert(A, name);
	if (!fa)
	{
		cout << "未找到此人" << endl;
		return;
	}
	FT* t = (FT*)malloc(sizeof(FT));
	if (fa->fir)
	{
		t->bro = fa->fir;
		t->fa = fa;
		t->fir = NULL;
		fa->fir = t;
		fa->prebro = NULL;
	}
	else
	{
		fa->fir = t;
		t->fa = fa;
		t->prebro = NULL;
		t->bro = NULL;
		t->fir = NULL;
	}
	cout << "==============================================================" << endl;
	cout << "开始添加新成员" << endl;
	cout << "输入该成员的姓名：";
	cin >> t->info.name;
	cout << "输入该成员的生日" << endl;
	char data[12];
	int year, month, day;
	while (1)
	{
		cout << "输入年份：";
		cin >> year;
		if (year < 10000 && year >= 0)
			break;
		else
			cout << "格式错误!" << endl;
	}
	while (1)
	{
		cout << "输入月份：";
		cin >> month;
		if (month <= 12 && month >= 1)
			break;
		else
			cout << "格式错误!" << endl;
	}
	while (1)
	{
		cout << "输入日数：";
		cin >> day;
		if (day <= 31 && day >= 1)
			break;
		else
			cout << "格式错误!" << endl;
	}
	_itoa(year, data, 10);
	data[4] = '-';
	if (month / 10)
		_itoa(month, data + 5, 10);
	else
	{
		data[5] = '0';
		_itoa(month, data + 6, 10);
	}
	data[7] = '-';
	if (day / 10)
		_itoa(day, data + 8, 10);
	else
	{
		data[8] = '0';
		_itoa(day, data + 9, 10);
	}
	cout << "输入的生日为" << data << endl;
	strcpy(t->info.birth, data);
	cout << "是否已婚(Y/N)：";
	cin.ignore();
	c = getchar();
	if (c == 'y' || c == 'Y') t->info.isMarried = 1;
	else t->info.isMarried = 0;
	cout << "输入地址：";
	cin >> t->info.address;
	cout << "是否健在(Y/N)：";
	cin.ignore();
	c = getchar();
	if (c == 'y' || c == 'Y')
	{
		t->info.isdeath = 0;
	}
	else
	{
		t->info.isdeath = 1;
		char death[12];
		cout << "输入其死亡日期" << endl;
		while (1)
		{
			cout << "输入年份：";
			cin >> year;
			if (year < 10000 && year >= 0)
				break;
			else
				cout << "格式错误!" << endl;
		}
		while (1)
		{
			cout << "输入月份：";
			cin >> month;
			if (month <= 12 && month >= 1)
				break;
			else
				cout << "格式错误!" << endl;
		}
		while (1)
		{
			cout << "输入日数：";
			cin >> day;
			if (day <= 31 && day >= 1)
				break;
			else
				cout << "格式错误!" << endl;
		}
		_itoa(year, death, 10);
		death[4] = '-';
		if (month / 10)
			_itoa(month, death + 5, 10);
		else
		{
			death[5] = '0';
			_itoa(month, death + 6, 10);
		}
		death[7] = '-';
		if (day / 10)
			_itoa(day, death + 8, 10);
		else
		{
			death[8] = '0';
			_itoa(day, death + 9, 10);
		}
		cout << "输入的日期为" << death << endl;
		strcpy(t->info.death, death);
	}
}

void deleteTree(FT* A)
{
	if (!A->fir && !A->bro)
	{
		free(A);
		return;
	}
	else
	{
		if (A->fir)
			deleteTree(A->fir);
		if (A->bro)
			deleteTree(A->bro);
		free(A);
	}
}

void dfsdelete(FT* A, char* name)
{
	if (!strcmp(A->info.name, name))
	{
		printInfo(A);
		cout << "是否为删除对象？(Y/N):";
		cin.ignore();
		char c = getchar();
		if (c == 'y' || c == 'Y')
		{
			if (A->prebro)
			{
				A->prebro->bro = A->bro;
			}
			else
			{
				A->fa->fir = A->bro;
			}
			if (A->fir)
				deleteTree(A->fir);
			free(A);
			return;
		}
	}
	if (A->fir) dfsdelete(A->fir, name);
	if (A->bro) dfsdelete(A->bro, name);
}

void Delete(FT* A)
{
	if (!strlen(filename))
	{
		cout << "未导入初始家谱" << endl;
		return;
	}
	char name[20];
	cout << "输入要删除的成员姓名：";
	cin >> name;
	dfsdelete(A, name);
	cout << "删除完毕" << endl;
}

FT* dfschange(FT* A, char* name)
{
	if (!strcmp(A->info.name, name))
	{
		printInfo(A);
		cout << "是否为修改对象？(Y/N):";
		cin.ignore();
		char c = getchar();
		if (c == 'y' || c == 'Y')
			return A;
		else
			return NULL;
	}
	FT* p1 = NULL, * p2 = NULL;
	if (A->fir) p1 = dfschange(A->fir, name);
	if (p1) return p1;
	if (A->bro) p2 = dfschange(A->bro, name);
	if (p2) return p2;
	return NULL;
}

void Change(FT* A)
{
	char c;
	if (!strlen(filename))
	{
		cout << "未导入初始家谱" << endl;
		return;
	}
	char name[20];
	cout << "输入要修改的成员姓名：";
	cin >> name;
	FT* t = dfschange(A, name);
	if (!t)
	{
		cout << "未找到此人" << endl;
		return;
	}
	cout << "==============================================================" << endl;
	cout << "开始修改成员信息" << endl;
	cout << "输入该成员的姓名：";
	cin >> t->info.name;
	cout << "输入该成员的生日" << endl;
	char data[12];
	int year, month, day;
	while (1)
	{
		cout << "输入年份：";
		cin >> year;
		if (year < 10000 && year >= 0)
			break;
		else
			cout << "格式错误!" << endl;
	}
	while (1)
	{
		cout << "输入月份：";
		cin >> month;
		if (month <= 12 && month >= 1)
			break;
		else
			cout << "格式错误!" << endl;
	}
	while (1)
	{
		cout << "输入日数：";
		cin >> day;
		if (day <= 31 && day >= 1)
			break;
		else
			cout << "格式错误!" << endl;
	}
	_itoa(year, data, 10);
	data[4] = '-';
	if (month / 10)
		_itoa(month, data + 5, 10);
	else
	{
		data[5] = '0';
		_itoa(month, data + 6, 10);
	}
	data[7] = '-';
	if (day / 10)
		_itoa(day, data + 8, 10);
	else
	{
		data[8] = '0';
		_itoa(day, data + 9, 10);
	}
	cout << "输入的生日为" << data << endl;
	strcpy(t->info.birth, data);
	cout << "是否已婚(Y/N)：";
	cin.ignore();
	c = getchar();
	if (c == 'y' || c == 'Y') t->info.isMarried = 1;
	else t->info.isMarried = 0;
	cout << "输入地址：";
	cin >> t->info.address;
	cout << "是否健在(Y/N)：";
	cin.ignore();
	c = getchar();
	if (c == 'y' || c == 'Y')
	{
		t->info.isdeath = 0;
	}
	else
	{
		t->info.isdeath = 1;
		char death[12];
		cout << "输入其死亡日期" << endl;
		while (1)
		{
			cout << "输入年份：";
			cin >> year;
			if (year < 10000 && year >= 0)
				break;
			else
				cout << "格式错误!" << endl;
		}
		while (1)
		{
			cout << "输入月份：";
			cin >> month;
			if (month <= 12 && month >= 1)
				break;
			else
				cout << "格式错误!" << endl;
		}
		while (1)
		{
			cout << "输入日数：";
			cin >> day;
			if (day <= 31 && day >= 1)
				break;
			else
				cout << "格式错误!" << endl;
		}
		_itoa(year, death, 10);
		death[4] = '-';
		if (month / 10)
			_itoa(month, death + 5, 10);
		else
		{
			death[5] = '0';
			_itoa(month, death + 6, 10);
		}
		death[7] = '-';
		if (day / 10)
			_itoa(day, death + 8, 10);
		else
		{
			death[8] = '0';
			_itoa(day, death + 9, 10);
		}
		cout << "输入的日期为" << death << endl;
		strcpy(t->info.death, death);
	}
	cout << "修改完毕" << endl;
}

int main()
{
	FT* A;
	A = (FT*)malloc(sizeof(FT));
	for (;;)
	{
		switch (menu_select())
		{
		case 1:
			printf("调用创建家谱函数\n");
			CreateFT(A);
			system("pause");
			break;
		case 2:
			printf("调用显示家谱函数\n");
			Print(A);
			system("pause");
			break;
		case 3:
			printf("调用显示第n代函数\n");
			PrintN(A);
			system("pause");
			break;
		case 4:
			printf("调用查询名字函数\n");
			SearchByName(A);
			system("pause");
			break;
		case 5:
			printf("调用查询生日函数\n");
			SearchByDate(A);
			system("pause");
			break;
		case 6:
			printf("调用关系函数\n");
			Relation(A);
			system("pause");
			break;
		case 7:
			printf("调用添加成员函数\n");
			Insert(A);
			system("pause");
			break;
		case 8:
			printf("调用删除成员函数\n");
			Delete(A);
			system("pause");
			break;
		case 9:
			printf("调用修改成员函数\n");
			Change(A);
			system("pause");
			break;
		case 0:
			printf("再见\n");
			Close(A);
			system("pause");
			exit(0);

		}
	}
	return 0;
}