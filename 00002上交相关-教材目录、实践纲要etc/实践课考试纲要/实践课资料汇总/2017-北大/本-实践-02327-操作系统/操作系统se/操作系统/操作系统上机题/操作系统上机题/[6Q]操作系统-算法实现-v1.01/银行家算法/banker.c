#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN	256

//������Դ����
#define TOTAL_A			10
#define TOTAL_B			5
#define TOTAL_C			7

//���̽ڵ�
typedef struct _p_node
{
	char Name[MAX_STRLEN];
	int MaxA;
	int MaxB;
	int MaxC;
	int UsingA;
	int UsingB;
	int UsingC;
	struct _p_node *Next;
	struct _p_node *Prev;
}P_NODE;

//�����б�
typedef P_NODE P_LIST;

//�½��ڵ�
P_NODE *NewNode( const char * name,int maxA, int maxB, int maxC )
{
	P_NODE *pN = NULL;
	pN = (P_NODE*)malloc( sizeof( P_NODE ) );
	strcpy( pN->Name, name );
	pN->Next = NULL;
	pN->Prev = NULL;
	pN->UsingA = 0;
	pN->UsingB = 0;
	pN->UsingC = 0;
	pN->MaxA = maxA;
	pN->MaxB = maxB;
	pN->MaxC = maxC;
	return pN;
}

//���ٽڵ�
void DelNode( P_NODE *pN )
{
	free( pN );
}

//����ڵ㣬��*pP�����*pN
void InsertAt( P_NODE *pP, P_NODE *pN )
{
	if( pP->Next != NULL )
		pP->Next->Prev = pN;
	pN->Prev = pP;
	pN->Next = pP->Next;
	pP->Next = pN;
}

//����ڵ�
void Isolate( P_NODE *pN )
{
	if( pN->Prev != NULL )
		pN->Prev->Next = pN->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN->Prev;
		
	pN->Next = NULL;
	pN->Prev = NULL;
}

P_LIST	g_PList;
int			g_UsingA = 0;
int			g_UsingB = 0;
int			g_UsingC = 0;

//���ݽ�����Ѱ�ҽڵ�
//�ɹ����ؽ��ָ�룬ʧ�ܷ���NULL
P_NODE *FindNodeByName( const char *name )
{
	P_NODE *pN = g_PList.Next;
	while( pN !=  NULL )
	{
		if( 0 == strcmp( pN->Name, name ) )
			break;
		pN = pN->Next;
	}
	return pN;
}

//��Ļ��ӡ��Դ�����
void PrintResourceTable()
{
	P_NODE *pN = g_PList.Next;
	
	printf("================================================\n");
	printf("                  ��Դ�����                    \n");
	printf("------------------------------------------------\n");
	printf("          | Ŀǰռ���� | ��������� | ����Ҫ�� \n");
	printf(" �������� |------------+------------+-----------\n");
	printf("          | A | B | C  | A | B | C  | A | B | C \n");
	printf("----------+------------+------------+-----------\n");
	while( pN != NULL )
	{
		printf(" %8s |%3i|%3i|%3i |%3i|%3i|%3i |%3i|%3i|%3i\n",
			pN->Name,pN->UsingA,pN->UsingB,pN->UsingC,pN->MaxA,pN->MaxB,pN->MaxC,
			pN->MaxA-pN->UsingA,pN->MaxB-pN->UsingB,pN->MaxC-pN->UsingC );
		pN = pN->Next;
	}
	printf("================================================\n");
	printf(" ��Դ���� |     A      |     B      |     C    \n");
	printf("----------+------------+------------+-----------\n");
	printf(" ��Դ���� |%6i      |%6i      |%6i    \n",TOTAL_A,TOTAL_B,TOTAL_C );
	printf("----------+------------+------------+-----------\n");
	printf(" ռ������ |%6i      |%6i      |%6i    \n",g_UsingA,g_UsingB,g_UsingC);
	printf("----------+------------+------------+-----------\n");
	printf(" ʣ������ |%6i      |%6i      |%6i    \n",TOTAL_A-g_UsingA,TOTAL_B-g_UsingB,TOTAL_C-g_UsingC);
	printf("================================================\n");
}

//�����û������ʼ�������б�
void BuildPListFromUserInput()
{
	char fileName[MAX_STRLEN];
	FILE *pF = NULL;
	P_NODE *pN = &g_PList;
	
	g_UsingA = 0;
  g_UsingB = 0;
  g_UsingC = 0;
	
	//���������ļ�
	for(;;)
	{
		printf("�������ļ�����");
		scanf( "%s", fileName );
		pF = fopen( fileName, "r" );
		if( pF != NULL )
			break;
		printf("�޷��򿪸��ļ�����ȷ��������ļ����Ƿ���ȷ��\n");
	}
	
	//�������ļ���ȡ���ݳ�ʼ�������б�
	while( !feof( pF ) )
	{
		
		P_NODE *pN1 = NewNode(" ",0,0,0);
		fscanf( pF, "%s %i %i %i", pN1->Name, &pN1->MaxA, &pN1->MaxB, &pN1->MaxC );
		InsertAt( pN, pN1 );
		pN = pN1;
	}
	
	fclose( pF );
}

void PrintUserMenu()
{
	printf("==================================\n");
	printf("           ����˵�               \n");
	printf("----------------------------------\n");
	printf("1|������Դ 2|��ʾ��Դ����� 0|�˳�\n");
	printf("==================================\n");
	printf("��ѡ��");
}

//�����û������������Դ
//�����м��㷨�ж��Ƿ���Է���
void AllocateResource()
{
	char	name[MAX_STRLEN];
	int		a = 0;
	int		b = 0;
	int		c = 0;
	P_NODE *pN = NULL;
	
	printf("�������������");
	scanf("%s",name);
	pN = FindNodeByName( name );
	if( pN == NULL )
	{
		printf("��Դ����ʧ�ܡ�\n");
		printf("ԭ�򣺲�������Ϊ%s���̡�\n",name);
		return;
	}
	
	printf("����������A��������");
	scanf("%i",&a);
	if( (a + pN->UsingA) > pN->MaxA )
	{
		printf("��Դ����ʧ�ܡ�\n");
		printf("ԭ�򣺱��������A + %s��ռ�õ�A > %s��A�������������\n",
			pN->Name,pN->Name);
		return;
	}
	if( (pN->MaxA - pN->UsingA) > (TOTAL_A - g_UsingA) )
	{
		printf("��Դ����ʧ�ܡ�\n");
		printf("ԭ��%s����Ҫ��A > ϵͳ��A��ʣ��������\n",
			pN->Name);
		return;
	}
	
	printf("����������B��������");
	scanf("%i",&b);
	if( (b + pN->UsingB) > pN->MaxB )
	{
		printf("��Դ����ʧ�ܡ�\n");
		printf("ԭ�򣺱��������B + %s��ռ�õ�B > %s��B�������������\n",
			pN->Name,pN->Name);
		return;
	}
	if( (pN->MaxB - pN->UsingB) > (TOTAL_B - g_UsingB) )
	{
		printf("��Դ����ʧ�ܡ�\n");
		printf("ԭ��%s����Ҫ��B > ϵͳ��B��ʣ��������\n",
			pN->Name);
		return;
	}
	
	printf("����������C��������");
	scanf("%i",&c);
	if( (c + pN->UsingC) > pN->MaxC )
	{
		printf("��Դ����ʧ�ܡ�\n");
		printf("ԭ�򣺱��������C + %s��ռ�õ�C > %s��C�������������\n",
			pN->Name,pN->Name);
		return;
	}
	if( (pN->MaxC - pN->UsingC) > (TOTAL_C - g_UsingC) )
	{
		printf("��Դ����ʧ�ܡ�\n");
		printf("ԭ��%s����Ҫ��C > ϵͳ��C��ʣ��������\n",
			pN->Name);
		return;
	}
	
	printf("��Դ����ɹ���\n");
	g_UsingA += a;
	g_UsingB += b;
	g_UsingC += c;
	pN->UsingA += a;
	pN->UsingB += b;
	pN->UsingC += c;
}

//��ʾ�˵��������û�ѡ�񣬲�ִ��
void ExecUserCommand()
{
	char command[MAX_STRLEN];
	
	for(;;)
	{
		PrintUserMenu();
		scanf("%s",command);
		switch( command[0] )
		{
			case '1':AllocateResource();break;
			case '2':PrintResourceTable();break;
			case '0':exit(0);
			default:printf("�������ѡ����ڣ�������ѡ��\n");
		}
	}
}

void main()
{
	BuildPListFromUserInput();
	PrintResourceTable();
	ExecUserCommand();
}