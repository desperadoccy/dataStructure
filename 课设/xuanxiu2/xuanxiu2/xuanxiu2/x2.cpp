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
		printf("1.����������ף����ļ����룩\n");
		printf("2.��ӡ����\n");
		printf("3.��ʾ��n�������м�¼\n");
		printf("4.��������ѯ��Ա��Ϣ\n");
		printf("5.���������ڲ�ѯ��Ա��Ϣ\n");
		printf("6.��ѯ���˹�ϵ\n");
		printf("7.Ϊ��Ա��Ӻ���\n");
		printf("8.ɾ��ĳ��Ա\n");
		printf("9.�޸�ĳ��Ա��Ϣ\n");
		printf("0.�˳�\n");
		printf("������ѡ�����(0-9):");
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
	cout << "�������ļ�����";
	cin >> filename;
	fstream file(filename);
	if (!file)
	{
		cout << "�ļ���ʧ��" << endl;
		exit(1);
	}
	//�ݹ齨��
	create(A, NULL, NULL, file);
	file.close();
	cout << "�����ɹ�" << endl;
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
	//�ݹ�洢
	//�������
	save(A, file);
	file.close();
}

void subPrint(FT* A, widget* data, int* cnt)
{
	//��ջ���
	cleardevice();
	*cnt = 0;
	wchar_t name[20];

	//�����˳���ť
	RECT r_exit = { 535,405,600,440 };
	rectangle(535, 405, 600, 440);
	drawtext(_T("�˳�"), &r_exit, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//�������ذ�ť
	RECT r_return = { 430, 405, 495, 440 };
	rectangle(430, 405, 495, 440);
	drawtext(_T("����"), &r_return, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//�������׽��
	RECT r_pa = { 260,100,380,150 };
	rectangle(260, 100, 380, 150);
	//��Ϣת����utf-8תΪUnicode��charתΪwchar
	int nRet = MultiByteToWideChar(CP_ACP, 0, A->info.name, 20, name, 20);
	drawtext(name, &r_pa, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//���������ӽ��
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
		cout << "δ�����ʼ����" << endl;
		return;
	}
	// ���������������
	srand((unsigned)time(NULL));

	// ��ʼ��ͼ��ģʽ
	initgraph(640, 480);

	// ��������
	settextstyle(16, 8, _T("Courier"));

	// ������ɫ
	COLORREF color = RGB(252, 253, 248);
	setbkcolor(color);
	settextcolor(BLACK);
	setlinecolor(BLACK);

	// ����������
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
			//�˳�
			if (m.x <= 600 && m.x >= 535 && m.y >= 405 && m.y <= 440)
			{
				break;
			}
			//����
			if (m.x <= 495 && m.x >= 430 && m.y >= 405 && m.y <= 440)
			{
				if (tree->fa != NULL)
				{
					subPrint(tree->fa, data, &cnt);
					tree = tree->fa;
				}
			}
			//ѡ���ӽ��
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

	// �ر�ͼ��ģʽ
	closegraph();

}

void printInfo(FT* A)
{
	cout << "������" << A->info.name << endl;
	cout << "���գ�" << A->info.birth << endl;
	cout << "���";
	if (A->info.isMarried)
	{
		cout << "��" << endl;
	}
	else
	{
		cout << "��" << endl;
	}
	cout << "��ַ��" << A->info.address << endl;
	cout << "���ڷ�";
	if (A->info.isdeath)
	{
		cout << "��" << endl;
		cout << "�������ڣ�" << A->info.death << endl;
	}
	else
	{
		cout << "��" << endl;
	}
	cout << endl;
}

void PrintN(FT* A)
{
	if (!strlen(filename))
	{
		cout << "δ�����ʼ����" << endl;
		return;
	}
	int n;
	cout << "������Ҫ��ѯ�Ĵ���n��";
	cin >> n;
	if (n == 0)
	{
		cout << "n��Ϊ0��" << endl;
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
		cout << "���ˣ�" << endl;
		printInfo(A);
		cout << "�丸�ף�" << endl;
		if (A->fa)
			printInfo(A->fa);
		else
			cout << "���������丸����Ϣ" << endl;
		cout << "�亢�ӣ�" << endl;
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
			cout << "���������亢����Ϣ" << endl;
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
		cout << "δ�����ʼ����" << endl;
		return;
	}
	char name[20];
	cout << "������Ҫ��ѯ�ĳ�Ա������";
	cin >> name;
	dfsSearchByName(A, name);
	cout << "��ѯ���" << endl;
}

void dfsSearchByDate(FT* A, char* name)
{
	if (!strcmp(A->info.birth, name))
	{
		cout << "���ˣ�" << endl;
		printInfo(A);
		cout << "�丸�ף�" << endl;
		if (A->fa)
			printInfo(A->fa);
		else
			cout << "���������丸����Ϣ" << endl;
		cout << "�亢�ӣ�" << endl;
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
			cout << "���������亢����Ϣ" << endl;
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
		cout << "δ�����ʼ����" << endl;
		return;
	}
	char data[12];
	int year, month, day;
	cout << "������Ҫ��ѯ�ĳ������ڣ�";
	while (1)
	{
		cout << "������ݣ�";
		cin >> year;
		if (year < 10000 && year >= 0)
			break;
		else
			cout << "��ʽ����!" << endl;
	}
	while (1)
	{
		cout << "�����·ݣ�";
		cin >> month;
		if (month <= 12 && month >= 1)
			break;
		else
			cout << "��ʽ����!" << endl;
	}
	while (1)
	{
		cout << "����������";
		cin >> day;
		if (day <= 31 && day >= 1)
			break;
		else
			cout << "��ʽ����!" << endl;
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
	cout << "��ѯ������Ϊ" << data << endl;
	dfsSearchByDate(A, data);
	cout << "��ѯ���" << endl;
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
		cout << "�Ƿ�Ϊ��ѯ����(Y/N):";
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
		cout << "δ�����ʼ����" << endl;
		return;
	}
	char Seniority[8][20] = { "�ֵ�","����","�游","����","����","����","̫��","Ԫ��" };
	char name1[20], name2[20];
	FT* T1, * T2,*fa=A;
	cout << "������Ҫ���ҵ���������" << endl;
	cout << "�����һ���˵�������";
	cin.ignore();
	cin >> name1;
	T1=dfsRelation(A, name1);
	if (!T1)
	{
		cout << "���޴���" << endl;
		return;
	}
	cout << "����ڶ����˵�������";
	cin.ignore();
	cin >> name2;
	T2 = dfsRelation(A, name2);
	if (!T2)
	{
		cout << "���޴���" << endl;
		return;
	}
	cout << "=========================================" << endl;
	cout << "�������" << endl;
	int ans= LCA(A, T1, T2, fa);
	cout << "�������" << abs(ans) << "��" << endl;
	if (!ans)
	{
		cout << T1->info.name << "��" << T2->info.name << "���ֵܹ�ϵ" << endl;
	}
	else if (ans < 0)
	{
		ans = -1 * ans;
		int i = ans > 7 ? 7 : ans;
		cout << T1->info.name << "��" << T2->info.name << "��" << Seniority[i]<<"��"<< endl;
	}
	else
	{
		int i = ans > 7 ? 7 : ans;
		cout << T2->info.name << "��" << T1->info.name << "��" << Seniority[i] << "��" << endl;
	}
}

FT* dfsInsert(FT* A, char* name)
{
	if (!strcmp(A->info.name, name))
	{
		printInfo(A);
		cout << "�Ƿ�Ϊ�������(Y/N):";
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
		cout << "δ�����ʼ����" << endl;
		return;
	}
	char name[20];
	cout << "����Ҫ���뺢�ӵĳ�Ա���֣�";
	cin >> name;
	FT* fa = dfsInsert(A, name);
	if (!fa)
	{
		cout << "δ�ҵ�����" << endl;
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
	cout << "��ʼ����³�Ա" << endl;
	cout << "����ó�Ա��������";
	cin >> t->info.name;
	cout << "����ó�Ա������" << endl;
	char data[12];
	int year, month, day;
	while (1)
	{
		cout << "������ݣ�";
		cin >> year;
		if (year < 10000 && year >= 0)
			break;
		else
			cout << "��ʽ����!" << endl;
	}
	while (1)
	{
		cout << "�����·ݣ�";
		cin >> month;
		if (month <= 12 && month >= 1)
			break;
		else
			cout << "��ʽ����!" << endl;
	}
	while (1)
	{
		cout << "����������";
		cin >> day;
		if (day <= 31 && day >= 1)
			break;
		else
			cout << "��ʽ����!" << endl;
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
	cout << "���������Ϊ" << data << endl;
	strcpy(t->info.birth, data);
	cout << "�Ƿ��ѻ�(Y/N)��";
	cin.ignore();
	c = getchar();
	if (c == 'y' || c == 'Y') t->info.isMarried = 1;
	else t->info.isMarried = 0;
	cout << "�����ַ��";
	cin >> t->info.address;
	cout << "�Ƿ���(Y/N)��";
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
		cout << "��������������" << endl;
		while (1)
		{
			cout << "������ݣ�";
			cin >> year;
			if (year < 10000 && year >= 0)
				break;
			else
				cout << "��ʽ����!" << endl;
		}
		while (1)
		{
			cout << "�����·ݣ�";
			cin >> month;
			if (month <= 12 && month >= 1)
				break;
			else
				cout << "��ʽ����!" << endl;
		}
		while (1)
		{
			cout << "����������";
			cin >> day;
			if (day <= 31 && day >= 1)
				break;
			else
				cout << "��ʽ����!" << endl;
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
		cout << "���������Ϊ" << death << endl;
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
		cout << "�Ƿ�Ϊɾ������(Y/N):";
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
		cout << "δ�����ʼ����" << endl;
		return;
	}
	char name[20];
	cout << "����Ҫɾ���ĳ�Ա������";
	cin >> name;
	dfsdelete(A, name);
	cout << "ɾ�����" << endl;
}

FT* dfschange(FT* A, char* name)
{
	if (!strcmp(A->info.name, name))
	{
		printInfo(A);
		cout << "�Ƿ�Ϊ�޸Ķ���(Y/N):";
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
		cout << "δ�����ʼ����" << endl;
		return;
	}
	char name[20];
	cout << "����Ҫ�޸ĵĳ�Ա������";
	cin >> name;
	FT* t = dfschange(A, name);
	if (!t)
	{
		cout << "δ�ҵ�����" << endl;
		return;
	}
	cout << "==============================================================" << endl;
	cout << "��ʼ�޸ĳ�Ա��Ϣ" << endl;
	cout << "����ó�Ա��������";
	cin >> t->info.name;
	cout << "����ó�Ա������" << endl;
	char data[12];
	int year, month, day;
	while (1)
	{
		cout << "������ݣ�";
		cin >> year;
		if (year < 10000 && year >= 0)
			break;
		else
			cout << "��ʽ����!" << endl;
	}
	while (1)
	{
		cout << "�����·ݣ�";
		cin >> month;
		if (month <= 12 && month >= 1)
			break;
		else
			cout << "��ʽ����!" << endl;
	}
	while (1)
	{
		cout << "����������";
		cin >> day;
		if (day <= 31 && day >= 1)
			break;
		else
			cout << "��ʽ����!" << endl;
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
	cout << "���������Ϊ" << data << endl;
	strcpy(t->info.birth, data);
	cout << "�Ƿ��ѻ�(Y/N)��";
	cin.ignore();
	c = getchar();
	if (c == 'y' || c == 'Y') t->info.isMarried = 1;
	else t->info.isMarried = 0;
	cout << "�����ַ��";
	cin >> t->info.address;
	cout << "�Ƿ���(Y/N)��";
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
		cout << "��������������" << endl;
		while (1)
		{
			cout << "������ݣ�";
			cin >> year;
			if (year < 10000 && year >= 0)
				break;
			else
				cout << "��ʽ����!" << endl;
		}
		while (1)
		{
			cout << "�����·ݣ�";
			cin >> month;
			if (month <= 12 && month >= 1)
				break;
			else
				cout << "��ʽ����!" << endl;
		}
		while (1)
		{
			cout << "����������";
			cin >> day;
			if (day <= 31 && day >= 1)
				break;
			else
				cout << "��ʽ����!" << endl;
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
		cout << "���������Ϊ" << death << endl;
		strcpy(t->info.death, death);
	}
	cout << "�޸����" << endl;
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
			printf("���ô������׺���\n");
			CreateFT(A);
			system("pause");
			break;
		case 2:
			printf("������ʾ���׺���\n");
			Print(A);
			system("pause");
			break;
		case 3:
			printf("������ʾ��n������\n");
			PrintN(A);
			system("pause");
			break;
		case 4:
			printf("���ò�ѯ���ֺ���\n");
			SearchByName(A);
			system("pause");
			break;
		case 5:
			printf("���ò�ѯ���պ���\n");
			SearchByDate(A);
			system("pause");
			break;
		case 6:
			printf("���ù�ϵ����\n");
			Relation(A);
			system("pause");
			break;
		case 7:
			printf("������ӳ�Ա����\n");
			Insert(A);
			system("pause");
			break;
		case 8:
			printf("����ɾ����Ա����\n");
			Delete(A);
			system("pause");
			break;
		case 9:
			printf("�����޸ĳ�Ա����\n");
			Change(A);
			system("pause");
			break;
		case 0:
			printf("�ټ�\n");
			Close(A);
			system("pause");
			exit(0);

		}
	}
	return 0;
}