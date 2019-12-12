////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ�����ú���-�ֵܷ���ʾ����������в�����
//          
//          1�������ŵ���ʽ��ʾ����A(B(E,F),C,D(G(H,I,J)))
//          2�����õݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          3�����÷ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          4���������ĸ߶ȣ�
//          5��ͳ������Ҷ�ӽڵ��������
//          6����α��������������������εĽڵ㣬���������Ŀ�ȣ��������ڵ�Ĳ����ʵ�ʰ����Ľڵ��������Ŀ�ȣ�
//          7�����õݹ��㷨Ϊÿ���ڵ��paָ�븳ֵ��ָ��ýڵ�ĸ��ڵ�
//          8������һ�������һģһ�������������ظ������ĸ��ڵ�ָ��            
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define N 30

typedef struct node
{
	char data;
	struct node *fir,*sib;
	struct node *pa;
}TR;


int menu_select();
TR *createtree(char *pre,int *k);//���������������У������ո񣩴�����������*k��ʾ��ǰ���������еĵ�*k��λ�ã���λ����
                                 //����ǿո��򷵻�һ����ָ�룬�����һ��ȷ�����ַ����򴴽�һ���ڵ㣬�ýڵ�����Ϊ
                                 //pre[*k]��Ȼ���(*k)++,�ݹ�Ĵ����ýڵ�ĺ��ӷ�֧��Ȼ���(*k)++,�ٵݹ�Ĵ��������ֵܷ�֧��
                                 //��󷵻ظýڵ�ָ�롣��ע���ڸù����в�Ҫ��paָ�븳ֵ����

void showtree(TR *T);//�����ŵ���ʽ�����
void getpath1(TR *T);//��Ƶݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
void getpath2(TR *T);//��Ʒǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
int heighttree(TR *T);///���㲢�������ĸ߶�
int leaftree(TR *T);//���㲢��������Ҷ�ӽڵ������
int layervisit(TR *T);//���������������εĽڵ�,���������Ŀ��
void getpa(TR *T);//Ϊÿ���ڵ��paָ�븳ֵ��ָ��ýڵ�ĸ��ڵ㣬���ڵ��paָ��NULL
void showpa(TR *T);//��ʾÿ���ڵ㼰�丸�ڵ�
TR *copytree(TR *T,TR *pa);//����һ�������һģһ�������������ظ��Ƶ����ĸ��ڵ�ָ��
TR *deltree(TR *T);//������




int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.��������-�ֵܶ�����\n");
		printf("2.��ʾ��\n");
		printf("3.������ڵ㵽����Ҷ�ӽڵ��·��\n");
		printf("4.���ĸ߶Ⱥ�Ҷ�ӽڵ�����\n");
		printf("5.��α�����\n");	
		printf("6.��ȡpaָ��\n");
		printf("7.������\n");
		printf("0.exit\n");
		printf("Please input index(0-7):");
		i=getchar();		
	}while(i<'0' || i>'7');
	return (i-'0');	
}



main()
{
	char pre[]="ABE F  C DGH I J     ";//��֪������������(�ո��Ӧ��ָ��)
	TR *T=NULL,*R=NULL;
	int k;
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
			k=0;
            T=createtree(pre,&k);//������
			if(T)
				printf("�����ɹ�\n");
			else
				printf("�������ɹ�\n");
			system("pause");
			break;
		case 2:
			if(!T)
				printf("���ǿ���\n");
			else
				showtree(T);//��ʾ��
			printf("\n");
			system("pause");				
			break;
		case 3:			    			
			printf("\n�ݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			getpath1(T);//�ݹ��㷨��·��
			printf("\n�ǵݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			getpath2(T);//�ǵݹ��㷨��·��
			system("pause");		
			break;
		case 4:			    
			printf("\n���ĸ߶�=%d ,���а��� %d ƬҶ��\n",heighttree(T),leaftree(T));//ͳ�����ĸ߶Ⱥ�Ҷ�ӽڵ�����
	        system("pause");
			break;
		case 5:	
			printf("\n���Ĳ�α��������\n");
			k=layervisit(T);//������ʾ������εĽڵ㣬���������Ŀ��
			printf("\n���Ŀ��Ϊ��%d\n",k);
			system("pause");
			break;
		case 6:	
			getpa(T);//��ÿ���ڵ��paָ�븳ֵ
			printf("\n���Ľڵ㼰���Ӧ���ڵ�:\n");			
	        showpa(T);//��ʾ�������нڵ㼰���Ӧ���ڵ�
			system("pause");
			break;	
		case 7:
			R=copytree(T, NULL);//����һ��������ΪT����һģһ�����������������ĸ��ڵ�ָ�򷵻ظ�ֵ��R
			T=deltree(T);//����ԭ��
			printf("\n���Ƶ�����\n");
			showtree(R);//��ʾ���Ƶ���R
			printf("\n");
			R=deltree(R);//���ٸ��Ƶ���
			system("pause");
			break;	
		case 0:
			 printf("GOOD BYE\n");
			 system("pause");
				exit(0);
		}
	}
}


TR *createtree(char *pre,int *k)//���������������д���������
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	TR *p;
	if(pre[*k]==' ')
	{
		(*k)++;
		return NULL;
	}
	else
	{
		p=(TR *)malloc(sizeof(TR));
		p->data=pre[*k];
		(*k)++;
		p->fir=createtree(pre,k);
		p->sib=createtree(pre,k);
		return p;
	}		
}

void showtree(TR *T)//�����ŵ���ʽ���������
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	printf("%c",T->data);
	if(T->fir)
	{
		printf("(");
		showtree(T->fir);
		printf(")");
	}
	if(T->sib)
	{
		printf(",");
		showtree(T->sib);
	}
}

TR *a[N];
int top = 0;
void getpath1(TR *T)//�ݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T->fir)
	{
		int i;
		for(i = 0; i < top; i++)
			printf("%c ", a[i]->data);
		printf("%c\n", T->data);
	}
	else
	{
		a[top++] = T;
		getpath1(T->fir);
		top--;
	}
	if(T->sib)
		getpath1(T->sib);
}



TR *b[N];
int top2 = 0;
void getpath2(TR *T)//�ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return;
	TR *p = T;
	int i;
	while(p || top2)
	{
		while(p)
		{
			b[top2++] = p;
			p = p->fir;
		}
		if(top2)
		{
			p = b[--top2];
			if(!p->fir)
			{
				for(i = 0; i < top2; i++)
					printf("%c ", b[i]->data);
				printf("%c\n", p->data);
			}
			p = p->sib;
		}
	}
}

int max(int a,int b)
{
	if(a > b) return a;
	else return b;
}
int heighttree(TR *T)///���㲢�������ĸ߶�
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return 0;
	int height=1;
	if(T->fir)
	{
		height = max(heighttree(T->fir)+1,height);
	}
	if(T->sib)
	{
		height = max(heighttree(T->sib),height);
	}
	return height;
}

int leaftree(TR *T)//���㲢��������Ҷ�ӽڵ������
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return 0;
	int num=0;
	if(T->fir)
	{
		num = num + leaftree(T->fir);
	}
	else
	{
		num = 1;
	}
	if(T->sib)
	{
		num = num + leaftree(T->sib);
	}
	return num;
}

typedef struct node3
{
	TR *node;
	int	deep;
}QUE;
int layervisit(TR *T)//����������ĸ�����Σ����������Ŀ��
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	int ans = 0;
	int width = 0,pos = 0;
	int head = 0,tail = 0;
	QUE c[N];
	c[tail].node = T;
	c[tail++].deep = 1; 
	while(head != tail)
	{
		QUE t = c[head++];
		if(t.deep != pos)
		{
			ans = max(ans,width);
			pos = t.deep;
			width = 1;
		}
		else
		{
			width++;
		}
		printf("%c", t.node->data);
		TR *tmp = t.node;
		if(t.node->fir)
		{
			c[tail].node = t.node->fir;
			c[tail++].deep = t.deep+1;
		}
		while(tmp->sib)
		{
			tmp = tmp->sib;
			width++;
			printf("%c",tmp->data);
			if(tmp->fir)
			{
				c[tail].node = tmp->fir;
				c[tail++].deep = t.deep+1;
			}
		}
	}
	return ans;
}





void getpa(TR *T)//Ϊÿ���ڵ��paָ�븳ֵ��ָ��ýڵ�ĸ��ڵ㣬���ڵ��paָ��NULL
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return;
	if(T->fir)
	{
		T->fir->pa = T;
		getpa(T->fir);
		T->fir->pa = T;
	}
	if(T->sib)
	{
		T->sib->pa = T->pa;
		getpa(T->sib);
		T->sib->pa = T->pa;
	}
	T->pa = NULL;
}




void showpa(TR *T)//��ʾÿ���ڵ㼰�丸�ڵ�
{
	if(T)
	{
		if(T->pa)
			printf("%c---%c\n",T->data,T->pa->data);
		else
			printf("%c---NULL\n",T->data);
		showpa(T->fir);
		showpa(T->sib);
	}
}

TR *copytree(TR *T, TR *pa)//������
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(!T) return NULL;
	TR *t;
	t = (TR *)malloc(sizeof(TR));
	t->data = T->data;
	t->pa = pa;
	t->fir = copytree(T->fir, t);
	t->sib = copytree(T->sib, t);
	return t;
}

TR *deltree(TR *T)//������
{
	if(T)
	{
		T->fir=deltree(T->fir);
		T->sib=deltree(T->sib);
		free(T);
		return NULL;
	}
	else
		return NULL;
}





