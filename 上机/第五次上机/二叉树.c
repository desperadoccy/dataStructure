////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ�����ö�������ʾ��������������в�����
//          1�����ݶ������������������д����������������ظ��ڵ�ָ�룻
//          2�����õݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          3�����÷ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          4�����õݹ��㷨��Ѱ�Ҿ�������ָ���ڵ㣨���಻Ϊ�Է������ȣ�����Ĺ�ͬ���ȣ����ظ�����ָ�룻
//          5������η�������������Ľڵ����ݣ�ÿ���㵥��һ����ʾ�������жϸö������Ƿ�Ϊ��ȫ������
//          6��������ָ���ڵ�Ϊ���ڵ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define N 30

typedef struct node
{
	char data;
	struct node *left,*right;	
}BT;

typedef struct
{
	BT *t[N];
	int top;
}ST;
char stack[N];
int top=0;
int menu_select();

BT *createtree(char *in,char *pre,int k);//���ݶ�������������������д�����������k��ʾ�ַ���in�ĳ���
void showtree(BT *T);//�����ŵ���ʽ���������
void getpath1(BT *T);//�ݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
void getpath2(BT *T);//�ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
BT *delsubtree(BT *T,char s);//�ҵ���������Ϊs�Ľڵ㣬��ɾ���Ըýڵ�Ϊ������������󷵻ظ��ڵ㣨��Ϊ���ɾ��Ҳ���ܻ�ɾ����������
BT *getcomances(BT *T,char s1,char s2);//Ѱ�Ҿ�������ָ���ڵ�s1��s2�����಻Ϊ�Է������ȣ�����Ĺ�ͬ���ȣ����ظ�����ָ��
int layervisit(BT *T);//��α�������������������ڵ����ݣ����жϸö������Ƿ�Ϊ��ȫ������������ǣ�����1�����򷵻�0





int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.����������\n");
		printf("2.��ʾ������\n");
		printf("3.������ڵ㵽����Ҷ�ӽڵ��·��\n");
		printf("4.Ѱ�Ҿ��������ڵ�����Ĺ�ͬ����\n");
		printf("5.��α���������\n");	
		printf("6.������ָ���ڵ�Ϊ���ڵ������\n");	
		printf("0.exit\n");
		printf("Please input index(0-6):");
		i=getchar();		
	}while(i<'0' || i>'6');
	return (i-'0');	
}



main()
{
	BT *T=NULL,*p=NULL;
	char in[]="GBEHDFAC",pre[]="ABGDEHFC";//��֪���������������������
	char s;
	int k=strlen(in);//k��ʾ�������г���
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
            T=createtree(in,pre,k);
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
				showtree(T);
			printf("\n");
			system("pause");				
			break;
		case 3:			    			
			printf("\n�ݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			top=0;
			getpath1(T);
			printf("\n�ǵݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			getpath2(T);
			system("pause");		
			break;
		case 4:			    
			p=getcomances(T,'H','F');//Ѱ�Ҿ���H��F�ڵ�����Ĺ�ͬ����
	        printf("\n���� H �� F ����Ĺ�ͬ�����ǣ� %c\n",p->data);//����ҵ������Ƚڵ����ݣ�Ӧ����D
	        p=getcomances(T,'H','G');//Ѱ�Ҿ���H��G�ڵ�����Ĺ�ͬ����
	        printf("\n���� H �� G ����Ĺ�ͬ�����ǣ� %c\n",p->data);//����ҵ������Ƚڵ����ݣ�Ӧ����B
			system("pause");
			break;
		case 5:	
			printf("\n��������α��������\n");
			if(layervisit(T))
				printf("�ö���������ȫ������\n");
			else
				printf("�ö�����������ȫ������\n");
			system("pause");
			break;
		case 6:	
			T=delsubtree(T,'D');//ɾ����D��Ϊ���ڵ������
			printf("\nɾ����DΪ���ڵ������������Ϊ:\n",s);
			if(!T)
				printf("��Ϊ��\n");
			else
	            showtree(T);//��ʾɾ�������
			system("pause");
			break;		
		case 0:
			 printf("GOOD BYE\n");
			 system("pause");
				exit(0);
		}
	}
}


BT *createtree(char *in,char *pre,int k)//���ݶ�������������������д�����������k��ʾ�ַ���in�ĳ���
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(k<=0) return NULL;
	BT *node = (BT *)malloc(sizeof(BT));
	node->data = pre[0];
	if(k==1)
	{
	 node->left = NULL;
	 node->right = NULL;
	 return node; 
	}
	int i;
	for(i=0;i<k;i++)
	{
		if(in[i]==pre[0])
			break;
	}
	node->left = createtree(in,pre+1,i);
	node->right = createtree(in+i+1,pre+i+1,k-i-1);
	return node;
}

void showtree(BT *T)//�����ŵ���ʽ���������
{
	if(T)
	{
		printf("%c",T->data);
		if(T->left||T->right)
		{
			printf("(");
			showtree(T->left);
			printf(",");
			showtree(T->right);
			printf(")");
		}
	}
}


int layervisit(BT *T)//��α�������������������ڵ����ݣ����жϸö������Ƿ�Ϊ��ȫ������������ǣ�����1�����򷵻�0
{

////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	int head=0,tail=0;
	int ans=1,flag=0;
	BT queue[2*N];
	queue[tail++]=*T;
	while(head!=tail)
	{
		BT t = queue[head++];
		printf("%c ",t.data);
		flag=1;
		if(t.left)
		{
			queue[tail++]=*t.left;
		}
		else
		{
			flag = -1;
		}
		if(t.right)
		{
			queue[tail++]=*t.right;
		}
		else
		{
			flag *=-1;
		}
		if(flag==-1) ans = 0;
	}
	return ans;
}


void getpath1(BT *T)//�ݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(T->left==NULL&&T->right==NULL)
	{
		int i;
		for(i=0;i<top;i++)
			printf("%c->",stack[i]);
		printf("%c\n",T->data);
		return;
	}
	stack[top++] = T->data;
	if(T->left)
	{
		getpath1(T->left);
	}
	if(T->right)
	{
		getpath1(T->right);
	}
	top--;
}

void getpath2(BT *T)//�ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	ST stack1;
	stack1.top=0;
	int flag=0;
	BT *p,*p1=NULL;
	int i;
	p=T;
	do
	{
		while(p!=NULL)
		{
			stack1.t[stack1.top++]=p;
			p=p->left;
		}
		p1=NULL;
		flag=1;
		while(stack1.top&&flag)
		{
			p=stack1.t[stack1.top-1];
			if(p->right==p1)
			{
				if(p->left==NULL&&p->right==NULL)
				{
					for(i=0;i<stack1.top-1;i++)
						printf("%c->",stack1.t[i]->data);
					printf("%c\n",stack1.t[stack1.top-1]->data);
				
				}
				stack1.top--;
				p1=p;
			}
			else
			{
				p=p->right;
				flag=0;
			}
		}
	}while(stack1.top);
	
}


BT *deltree(BT *T)
{
	if(!T) return NULL;
	T->left=deltree(T->left);
	T->right=deltree(T->right);
	free(T);
	return NULL;
 } 
BT *delsubtree(BT *T,char s)//�ҵ���������Ϊs�Ľڵ㣬��ɾ���Ըýڵ�Ϊ������������󷵻ظ��ڵ㣨��Ϊ���ɾ��Ҳ���ܻ�ɾ����������
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(T->data==s) return deltree(T);
	if(T->left)
		T->left = delsubtree(T->left,s);
	if(T->right)
		T->right = delsubtree(T->right,s);
	return T;	
}


int Finds(BT *T,char s)
{
	if(!T) return 0;
	if(T->data == s)
		return 1;
	return Finds(T->left,s) | Finds(T->right,s);
}

BT *getcomances(BT *T,char s1,char s2)//Ѱ�Ҿ�������ָ���ڵ�s1��s2�����಻Ϊ�Է������ȣ�����Ĺ�ͬ���ȣ����ظ�����ָ��
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
	if(T->data==s1||T->data==s2) return T;
	int pos1 = Finds(T->left,s1);
	int pos2 = Finds(T->left,s2);
	if(pos1+pos2==0)
	{
		return getcomances(T->right,s1,s2);
	}
	else if(pos1+pos2==1)
	{
		return T;
	}
	else
	{
		return getcomances(T->left,s1,s2);
	}
}







