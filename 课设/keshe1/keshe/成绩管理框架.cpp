#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
char sbuf[1024];	//�洢����������

typedef struct student
{
	char name[20];
	char number[20];
	int score;
	struct student* next;
	struct student* pre;
}ST;

int menu_select();
void CreateST(ST* A, ST* B);
void Print(ST* A, ST *B);
void Search(ST* A, ST *B);
void Insert(ST* A, ST* B);
void Delete(ST* A, ST* B);
void Retest(ST* A, ST* B);
void close(ST* A, ST *B);

int menu_select()
{
	char i;
	do {
		system("cls");
		printf("1.������¼�����ļ����룩\n");
		printf("2.��ʾ���м�¼\n");
		printf("3.����һ����¼\n");
		printf("4.ɾ��һ����¼\n");
		printf("5.���벹���ɼ�\n");
		printf("6.��ѯ\n");
		printf("0.�˳�\n");
		printf("������ѡ�����(0-6):");
		i = getchar();
	} while (i<'0' || i>'6');
	return (i - '0');
}

void CreateST(ST* A, ST *B)
{
	A->next = NULL;
	B->next = NULL;
	ifstream infile;
	ST* t, * p, * p1;
	infile.open("01.txt");
	if (!infile)
	{
		cout << "error" << endl;
		system("pause");
		exit(0);
	}
	while (!infile.eof())
	{
		if (infile.fail()) break;
		char score[3], name[20], number[20];
		stringstream ss;
		t = (ST *)malloc(sizeof(ST));
		infile >> name;
		infile >> score;
		infile >> number;
		memcpy(t->name, name, 20);
		memcpy(t->number, number, 20);
		ss << score;	//���������ַ���תΪ����
		ss >> t->score;
		if (t->score >= 60) p = A;
		else p = B;
		while (p->next != NULL)
		{
			if (strcmp(t->name, p->next->name) < 0)
			{
				break;
			}
			else if (strcmp(t->name, p->next->name) == 0)
			{
				if (t->score < p->next->score)
				{
					break;
				}
				else if (t->score == p->next->score)
				{
					if (strcmp(t->number, p->number) < 0)
					{
						break;
					}
				}

			}
			p = p->next;
		}
		if (p->next == NULL)
		{
			p->next = t;
			t->pre = p;
			t->next = NULL;
		}
		else
		{
			p1 = p->next;
			p->next = t;
			t->pre = p;
			t->next = p1;
			p1->pre = t;
		}


		//cout << t->name << " " << t->score<<" "<<t->number<<endl;
	}
	infile.close();

	cout << "�����ɹ�" << endl;
	return;
}

void Print(ST* A, ST* B)
{
	int cnt = 0;
	ST* p1 = A->next, * p2 = B->next;
	if (p1 == NULL && p2 == NULL)
	{
		cout << "����Ϊ��" << endl;
		return;
	}
	printf("%8s\t%20s\t%8s\t%20s\n","���","����","�ɼ�","ѧ��");
	while (p1!= NULL)
	{
		cnt++;
		printf("%8d\t%20s\t%8d\t%20s\n", cnt, p1->name, p1->score, p1->number);
		p1 = p1->next;
		if (cnt % 10 == 0) system("pause");
	}
	while (p2 != NULL)
	{
		cnt++;
		printf("%8d\t%20s\t%8d\t%20s\n", cnt, p2->name, p2->score, p2->number);
		p2 = p2->next;
		if (cnt % 10 == 0) system("pause");
	}
}

void Search(ST* A, ST* B)
{
	char name[20];
	fgets(sbuf, 1024, stdin); //���������������
	cout << "����������ҵ�ѧ��������" << endl;
	cin.getline(name, 20);
	int cnt = 0;
	ST* p1 = A->next, * p2 = B->next;
	if (p1 == NULL && p2 == NULL)
	{
		cout << "����Ϊ��" << endl;
		return;
	}
	while (p1 != NULL)
	{
		if (strcmp(name, p1->name) == 0)
		{
			cnt++;
			if (cnt == 1)
			{
				printf("%8s\t%20s\t%8s\t%20s\n", "���", "����", "�ɼ�", "ѧ��");
			}
			printf("%8d\t%20s\t%8d\t%20s\n", cnt, p1->name, p1->score, p1->number);
			if (cnt % 10 == 0) system("pause");
		}
		p1 = p1->next;
	}
	while (p2 != NULL)
	{
		if (strcmp(name, p2->name) == 0)
		{
			cnt++;
			if (cnt == 1)
			{
				printf("%8s\t%20s\t%8s\t%20s\n", "���", "����", "�ɼ�", "ѧ��");
			}
			printf("%8d\t%20s\t%8d\t%20s\n", cnt, p2->name, p2->score, p2->number);
			if (cnt % 10 == 0) system("pause");
		}
		p2 = p2->next;
	}

	if (!cnt)
		cout << "δ�ҵ�����" << endl;
}

void Insert(ST* A, ST* B)
{
	fgets(sbuf, 1024, stdin); //���������������
	char name[20], score1[20], number[20];
	int score;
	bool flag = 0;
	
	//��������
	cout << "������ѧ��������" << endl;
	cin.getline(name,20);
	
	//����ɼ�
	while (1)
	{
		flag = 0;
		cout << "������ѧ���ɼ���" << endl;
		cin.getline(score1, 20);
		for (int i = 0; i < strlen(score1); i++)
		{
			if (score1[i] > '9' && score1[i] < '0')
			{
				flag = 1; 
				break;
			}
		}
		if (flag == 0)
		{
			stringstream ss;
			ss << score1; //���������������ʹ洢
			ss >> score;
			if (score <= 100 && score >= 0) break;
		}
		cout << "��ʽ����ӦΪ������100����Ȼ��" << endl;
	}
	

	//����ѧ��
	while (1)
	{
		flag = 0;
		cout << "������ѧ��ѧ�ţ�" << endl;
		cin.getline(number, 20);
		if (strlen(number) != 9)
		{
			cout << "��ʽ����" << endl;
			continue;
		}
		for (int i = 0; i < strlen(number); i++)
		{
			if (number[i] > '9' && number[i] < '0')
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0) break;
		cout << "��ʽ����ӦΪ9λ����" << endl;
	}
	
	//����
	ST* p1, * p;
	p1 = A, p = A->next;
	while (p != NULL)
	{
		if (strcmp(number, p->number) == 0)
		{
			//�ж��Ƿ���ͬѧ��
			cout << "����ʧ��,����ͬѧ����Ϣ" << endl;
			return;
		}
		p1 = p;
		p = p->next;
	}

	p1 = B, p = B->next;
	while (p != NULL)
	{
		if (strcmp(number, p->number) == 0)
		{
			//�ж��Ƿ���ͬѧ��
			cout << "����ʧ��,����ͬѧ����Ϣ" << endl;
			return;
		}
		p1 = p;
		p = p->next;
	}

	char c[20];
	cout << "�ɲ��룬�Ƿ����(y/n)" << endl;
	cin.getline(c, 20);
	if (c[0] == 'y' || c[0]=='Y')
	{
		ST* t = (ST*)malloc(sizeof(ST));
		memcpy(t->name, name, 20);
		memcpy(t->number, number, 20);
		t->score = score;
		if (score >= 60)
			p = A;
		else
			p = B;
		while (p->next != NULL)
		{
			if (strcmp(t->name, p->next->name) < 0)
			{
				break;
			}
			else if (strcmp(t->name, p->next->name) == 0)
			{
				if (t->score < p->next->score)
				{
					break;
				}
				else if (t->score == p->next->score)
				{
					if (strcmp(t->number, p->number) < 0)
					{
						break;
					}
				}

			}
			p = p->next;
		}
		p1 = p->next;
		p->next = t;
		t->pre = p;
		t->next = p1;
		if (p1 != NULL)
		{
			p1->pre = t;
		}
		cout << "����ɹ�" << endl;
	}
	else
	{
		return;
	}
}

void Delete(ST* A, ST* B)
{
	bool flag = 0;
	char name[20], ch[20];
	fgets(sbuf, 1024, stdin); //���������������
	cout << "�������ɾ����ѧ��������" << endl;
	cin.getline(name, 20);
	ST* p = A->next, * p1 = A;
	ST* pB = B->next, * p2 = B;

	if (p == NULL && pB == NULL)
	{
		cout << "����Ϊ��" << endl;
		return;
	}
	while (p != NULL)
	{
		if (strcmp(name, p->name) == 0)
		{
			flag = 1;
			cout << p->name << " " << p->score << " " << p->number << endl;
			cout << "������Ϣ�Ƿ�Ҫɾ����(y/n)" << endl;
			cin.getline(ch, 20);
			if (ch[0] == 'y' || ch[0] == 'Y')
			{
				p1->next = p->next;
				if(p->next != NULL)
					p->next->pre = p1;
				free(p);
				p = p1;
			}
		}
		p1 = p;
		p = p->next;
	}

	while (pB != NULL)
	{
		if (strcmp(name, pB->name) == 0)
		{
			flag = 1;
			cout << pB->name << " " << pB->score << " " << pB->number << endl;
			cout << "������Ϣ�Ƿ�Ҫɾ����(y/n)" << endl;
			cin.getline(ch, 20);
			if (ch[0] == 'y' || ch[0] == 'Y')
			{
				p2->next = pB->next;
				if(pB->next != NULL)
					pB->next->pre = p2;
				free(pB);
				pB = p2;
			}
		}
		p2 = pB;
		pB = pB->next;
	}
	if (!flag)
		cout << "δ�ҵ�����" << endl;
}

void Retest(ST* A, ST* B)
{
	fgets(sbuf, 1024, stdin); //���������������
	char name[20], score1[20], number[20];
	int score;
	bool flag = 0;

	//��������
	cout << "�����벹��ѧ��������" << endl;
	cin.getline(name, 20);

	//����ɼ�
	while (1)
	{
		flag = 0;
		cout << "�����벹��ѧ���ɼ���" << endl;
		cin.getline(score1, 20);
		for (int i = 0; i < strlen(score1); i++)
		{
			if (score1[i] > '9' && score1[i] < '0')
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			stringstream ss;
			ss << score1; //���������������ʹ洢
			ss >> score;
			if (score <= 100 && score >= 0) break;
		}
		cout << "��ʽ����ӦΪ������100����Ȼ��" << endl;
	}


	//����ѧ��
	while (1)
	{
		flag = 0;
		cout << "�����벹��ѧ��ѧ�ţ�" << endl;
		cin.getline(number, 20);
		if (strlen(number) != 9)
		{
			cout << "��ʽ����" << endl;
			continue;
		}
		for (int i = 0; i < strlen(number); i++)
		{
			if (number[i] > '9' && number[i] < '0')
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0) break;
		cout << "��ʽ����ӦΪ9λ����" << endl;
	}

	ST* pa, * pb, * t;

	//���в���
	flag = 0;
	pb = B->next;
	while (pb != NULL)
	{
		if (strcmp(pb->name, name) == 0 && strcmp(pb->number, number) == 0)
		{
			flag = 1;
			break;
		}
		pb = pb->next;
	}
	t = pb;
	t->score = score;
	//���Ĳ���
	if (flag)
	{
		//����ͨ����ɾ������Ϣ
		if (score >= 60)
		{
			ST* pb1;
			pb1 = pb->pre;
			pb1->next = pb->next;
			if (pb->next != NULL)
				pb->next->pre = pb1;
			//��A�����и���
			pa = A;
			while (pa->next != NULL)
			{
				if (strcmp(t->name, pa->next->name) < 0)
				{
					break;
				}
				else if (strcmp(t->name, pa->next->name) == 0)
				{
					if (t->score < pa->next->score)
					{
						break;
					}
					else if (t->score == pa->next->score)
					{
						if (strcmp(t->number, pa->number) < 0)
						{
							break;
						}
					}

				}
				pa = pa->next;
			}
			ST* p1 = pa->next;
			pa->next = t;
			t->pre = pa;
			t->next = p1;
			if (p1 != NULL)
			{
				p1->pre = t;
			}
		}
		cout << "�޸ĳɹ�" << endl;
	}
	else
	{
		cout << "δ���貹����Ա���ҵ�����" << endl;
		return;
	}
}

void close(ST* A, ST* B)
{
	//�Բ������д洢
	ST* p = A->next, * p2 = B->next;
	ofstream outfile;
	outfile.open("01.txt");
	while (p->next != NULL)
	{
		outfile << p->name << " " << p->score << " " << p->number << endl;
		p = p->next;
	}
	outfile << p->name << " " << p->score << " " << p->number;
	if (p2 != NULL)
		outfile << endl;
	while (p2->next != NULL)
	{
		outfile << p2->name << " " << p2->score << " " << p2->number << endl;
		p2 = p2->next;
	}
	outfile << p2->name << " " << p2->score << " " << p2->number;
	free(A); 
	free(B);
	outfile.close(); 
}

int main()
{
	ST* A, * B;
	A = (ST*)malloc(sizeof(ST));
	B = (ST*)malloc(sizeof(ST));
	A->next = B->next = NULL;
	for (;;)
	{
		switch (menu_select())
		{
		case 1:
			printf("���ô���������\n");
			CreateST(A, B);
			system("pause");
			break;
		case 2:
			printf("������ʾ����\n");
			Print(A, B);
			system("pause");
			break;
		case 3:
			printf("���ò��뺯��\n");
			Insert(A, B);
			system("pause");
			break;
		case 4:
			printf("����ɾ������ :\n");
			Delete(A, B);
			system("pause");
			break;
		case 5:
			printf("�������벹���ɼ�����:\n");
			Retest(A, B);
			system("pause");
			break;
		case 6:
			printf("���ò��Һ��� :\n");
			Search(A, B);
			system("pause");
			break;
		case 0:
			printf("�ټ�\n");
			close(A, B);
			system("pause");
			exit(0);

		}
	}
	return 0;
}
