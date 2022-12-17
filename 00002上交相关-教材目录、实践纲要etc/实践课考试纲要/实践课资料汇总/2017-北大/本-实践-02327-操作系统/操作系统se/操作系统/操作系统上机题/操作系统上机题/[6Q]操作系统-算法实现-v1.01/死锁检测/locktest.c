#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN	256

#define MAX_VERTEX	20
#define MAX_PATH		20
#define PATH_END		-1

//��������ö��
typedef enum
{
	Process,
	Resource
}V_TYPE;

//������Ϣ�ṹ
typedef struct _v_node
{
	char 		Name[MAX_STRLEN];	//���̻���Դ������
	int			Vertex;						//���̻���Դ��Ӧ�Ķ����
	V_TYPE	Type;							//�������ͣ����̻�����Դ
	struct	_v_node *Next;
	struct	_v_node *Prev;
}V_NODE;

//�½�������Ϣ�ڵ�
V_NODE *NewNode( const char *name, V_TYPE vType )
{
	static int __vCount = 0;
	
	V_NODE *pN = (V_NODE *)malloc( sizeof( V_NODE) );
	pN->Next = NULL;
	pN->Prev = NULL;
	pN->Type = vType;
	pN->Vertex = __vCount++;
	strcpy( pN->Name, name );
	return pN;
}

//��*pN���뵽*pP֮��
void InsertAt( V_NODE *pP, V_NODE *pN )
{
	if( pP->Next != NULL )
		pP->Next->Prev = pN;
	pN->Next = pP->Next;
	
	pN->Prev = pP;
	pP->Next = pN;
}

//������Ϣ����
typedef V_NODE V_LIST;

V_LIST g_VList;//�洢���н��̶������Դ����

//�����ṩ�Ķ���ţ����ض�����Ϣ�ṹ
//����ʧ�ܷ���NULL
V_NODE * FindNodeByVertex( int v )
{
	V_NODE *pN = g_VList.Next;
	while( pN != NULL )
	{
		if( pN->Vertex == v )
			break;
		pN = pN->Next;
	}
	return pN;
}

//�����ṩ�Ķ������ƺ����ͣ����ض�����Ϣ�ṹ
//����ʧ�ܷ���NULL
V_NODE * FindNodeByNameType( const char *name, V_TYPE type )
{
	V_NODE *pN = g_VList.Next;
	while( pN != NULL )
	{
		if( type == pN->Type && 0 == strcmp(pN->Name, name ) )
			break;
		pN = pN->Next;
	}
	return pN;
}

int g_Graph[MAX_VERTEX][MAX_VERTEX];//��Դ����ͼ

//������ȱ�����Դ����ͼ����ͼ�õ�һ����from����to��·��path
//�������·�����򷵻�TRUE�����򷵻�FALSE
BOOL DFS( int from, int to, int *path)
{
	static int __sd = 0;							//�ݹ�����
	static BOOL __visted[MAX_VERTEX];	//���ʱ�־
	
	int i = 0;
	
	//����ݹ����Ϊ�㣬˵�����κ�������Ϊ�û����ã���Ҫ������з��ʱ�־
	//���ݹ���ȴ�����ʱ��˵�����ε���Ϊ����ݹ飬��Ҫ�������ʱ�־
	if( __sd++ == 0)
		for( i=0; i<MAX_VERTEX; i++)
			__visted[i] = FALSE;
	
	__visted[from] = 1;	//��Ǹõ��Ѿ�������
	*path = from;				//��·���м�¼�õ�
		
	for( i = 0; i<MAX_VERTEX; i++ )
	{
		if( g_Graph[from][i] )
		{
			if( i == to )//����õ����to,�򷵻�TRUE
			{
				*(path+1) = i;//��·���м�¼�յ�
				*(path+2) = PATH_END;//����·��������־
				__sd--;
				return TRUE;
			}
			else if(!__visted[i])//��㻹û�б����ʹ�������ʸõ�
			{
				BOOL b = DFS(i, to ,path+1 );
				if( b == TRUE )//����Ѿ�����to���򷵻�TRUE�������������
				{
					__sd--;
					return TRUE;
				}
			}
		}
	}
	
	*(path+2) = PATH_END;//����·��������־
	__sd--;
	return FALSE;
}

//������Դ������ļ��������ļ����ݽ�����Դ�����̵ĳ���
void _1_BuildGraphFromUserInput()
{
	char fileName[MAX_STRLEN];
	char proName[MAX_STRLEN];
	char resName[MAX_STRLEN];
	FILE *pF = NULL;
	V_NODE *pN = &g_VList;
	
	for( ;; )
	{
		printf("��������Դ������ļ�:");
		scanf( "%s",fileName );
		pF = fopen( fileName, "r");
		if( pF != NULL )
			break;
		printf("�޷��򿪸��ļ�����ȷ��������ļ����Ƿ���ȷ��\n");
	}
	
	printf("================\n");
	printf("   ��Դ�����   \n");
	printf("----------------\n");
	printf("��Դ�� | ������ \n");
	printf("----------------\n");
	while( !feof( pF ) )
	{
		int from = 0;
		int to = 0;
		V_NODE *pN1 = NULL;
		
		fscanf(pF, "%s %s", resName, proName);
		printf("%6s | %6s\n",resName, proName);
		
		//���������Ϣ���в���������Դ��������Դ
		pN1 = FindNodeByNameType( resName, Resource );
		if( NULL == pN1 )
		{
			pN1 = NewNode( resName, Resource );
			InsertAt( pN, pN1);
			pN = pN->Next;
		}
		from = pN1->Vertex;
		
		//���������Ϣ���в������ý��������ý���
		pN1 = FindNodeByNameType( proName, Process );
		if( NULL == pN1 )
		{
			pN1 = NewNode( proName, Process );
			InsertAt( pN, pN1);
			pN = pN->Next;
		}
		to = pN1->Vertex;
		
		//����Դ����ͼ����ͨ����������
		g_Graph[from][to] = 1;
	}
	printf("================\n");
	fclose( pF );
}

//������̵ȴ����ļ��������ļ����ݽ������̵���Դ�ĳ���
void _2_BuildGraphFromUserInput()
{
	char fileName[MAX_STRLEN];
	char proName[MAX_STRLEN];
	char resName[MAX_STRLEN];
	FILE *pF = NULL;
	V_NODE *pN = &g_VList;
	
	for( ;; )
	{
		printf("��������̵ȴ����ļ�:");
		scanf( "%s",fileName );
		pF = fopen( fileName, "r");
		if( pF != NULL )
			break;
		printf("�޷��򿪸��ļ�����ȷ��������ļ����Ƿ���ȷ��\n");
	}
	
	printf("================\n");
	printf("   ���̵ȴ���   \n");
	printf("----------------\n");
	printf("������ | ��Դ�� \n");
	printf("----------------\n");
	
	while( !feof( pF ) )
	{
		int from = 0;
		int to = 0;
		V_NODE *pN1 = NULL;
		
		fscanf( pF, "%s %s",proName, resName);
		printf("%6s | %6s\n",proName, resName);
		
		//���������Ϣ���в������ý��������ý���
		pN1 = FindNodeByNameType( proName, Process );
		if( NULL == pN1 )
		{
			pN1 = NewNode( proName, Process );
			InsertAt( pN, pN1);
			pN = pN->Next;
		}
		from = pN1->Vertex;
		
		//���������Ϣ���в���������Դ��������Դ
		pN1 = FindNodeByNameType( resName, Resource );
		if( NULL == pN1 )
		{
			pN1 = NewNode( resName, Resource );
			InsertAt( pN, pN1);
			pN = pN->Next;
		}
		to = pN1->Vertex;
		
		//����Դ����ͼ����ͨ����������
		g_Graph[from][to] = 1;
	}
	
	printf("================\n");
	fclose( pF );
}

//�����û����룬������Դ����ͼ
void BuildGraphFromUserInput()
{
	int i = 0;
	int j = 0;
	for( j=0; j<MAX_VERTEX; j++ )
		for( i=0; i<MAX_VERTEX; i++)
			g_Graph[i][j] = 0;
	
	g_VList.Next = NULL;
	g_VList.Prev = NULL;
	
	_1_BuildGraphFromUserInput();
	_2_BuildGraphFromUserInput();
}

//��Ļ��ӡ·��
void PrintPath( int *path )
{
	int i = 0;
	V_NODE *pN = NULL;
	printf("======================================================================\n");
	printf("                          ������·ʾ��ͼ                              \n");
	printf("----------------------------------------------------------------------\n");
	for( i=0; path[i]!= PATH_END; i++)
	{
		pN = FindNodeByVertex(path[i]);
		if( pN->Type == Process )
			if( path[i+1] == PATH_END )
				printf("(%s)",pN->Name);
			else
				printf("(%s)-w->",pN->Name);
		else
			if( path[i+1] == PATH_END )
					printf("[%s]",pN->Name);
			else
				printf("[%s]-h->",pN->Name);
	}
	printf("\n");
	printf("----------------------------------------------------------------------\n");
	printf("��������:|  ()����  |  []��Դ  |  -w->�ȴ�  |  -h->��ռ��             \n");
	printf("======================================================================\n");
}

void main()
{
	int i = 0;
	int path[MAX_PATH];
		
	BuildGraphFromUserInput();
	
	//��ÿ�������������ͼ�ҵ���·
	for( i = 0; i<MAX_VERTEX; i++ )
	{
		//�����i�������Ե���i����˵�����ڻ�·
		if( DFS(i,i,path) )
		{
			printf("��������,������·���£�\n");
			PrintPath( path );
			return;
		}
	}
	
	printf("������ϣ�������������");
}