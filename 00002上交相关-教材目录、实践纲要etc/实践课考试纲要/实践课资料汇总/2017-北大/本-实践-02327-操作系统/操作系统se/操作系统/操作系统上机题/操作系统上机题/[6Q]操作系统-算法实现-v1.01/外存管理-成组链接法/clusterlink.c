#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN	256

#define CLUSTER_SIZE			10								//ÿ�麬�еĿ���
#define BLOCK_SIZE				CLUSTER_SIZE + 1	//ÿ������ɵ��ֶ���
#define MAX_JOB_BLOCKS		256								//ÿ��ҵ�������̿���

typedef struct _job_node
{
	char	Name[MAX_STRLEN];					//��ҵ��
	int		BlockCount;								//��ҵռ���̿�����
	int		BlockIds[MAX_JOB_BLOCKS];	//��ҵռ�õ��̿��
	struct _job_node *Next;
	struct _job_node *Prev;
}JOB_NODE;

//�½���ҵ�ڵ�
JOB_NODE *NewJobNode( const char* name, const int *bIds, int count )
{
	JOB_NODE *pN = ( JOB_NODE * )malloc( sizeof( JOB_NODE ) );
	pN->Next = NULL;
	pN->Prev = NULL;
	strcpy( pN->Name, name );
	for( pN->BlockCount = 0; pN->BlockCount < count; pN->BlockCount++ )
		pN->BlockIds[ pN->BlockCount ] = bIds[ pN->BlockCount ];
	return pN;
}

//������ҵ�ڵ�
void DelJobNode( JOB_NODE *pN )
{
	free( pN );
}

//��*pP�����*pN
void InsertJobNodeAt( JOB_NODE *pP, JOB_NODE *pN )
{
	pN->Next = pP->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN;
	
	pN->Prev = pP;
	pP->Next = pN;
}

//�����ڵ㣬����ǰ���ͺ��ֱ������
void IsolateJobNode( JOB_NODE *pN )
{
	if( pN->Next != NULL )
		pN->Next->Prev = pN->Prev;
	if( pN->Prev != NULL )
		pN->Prev->Next = pN->Next;
	
	pN->Next = NULL;
	pN->Prev = NULL;
}

//��ҵ��
typedef JOB_NODE JOB_LIST;

JOB_LIST g_Jobs;//���ϵͳ��������ҵ

//������ҵ��������ҵ
//�ҵ����ظ���ҵ�ڵ��ָ�룬���򷵻�NULL
JOB_NODE *FindJobByName( const char * name )
{
	JOB_NODE *pN = g_Jobs.Next;
	while( pN != NULL )
	{
		if( strcmp( pN->Name, name ) == 0 )
			break;
		pN = pN->Next;
	}
	return pN;
}

typedef struct _block_node
{
	int	Id;								//�̿��
	int Data[BLOCK_SIZE];	//�����ÿ���׿�Ļ���Data[0]�д����һ����̿�����,��������һ�����п��Id
												//���������һ����ĩ�飬��Data[1]==0
	struct _block_node *Next;
	struct _block_node *Prev;
}BLOCK_NODE;

//����ڵ�
BLOCK_NODE *NewBlockNode( int id )
{
	BLOCK_NODE *pN = ( BLOCK_NODE * )malloc( sizeof( BLOCK_NODE ));
	pN->Id = id;
	pN->Data[0] = 0;
	pN->Next = NULL;
	pN->Prev = NULL;
	return pN;
}

//��*pS��Data���Ƹ�*pT
//����ֵ��pT��ͬ
BLOCK_NODE * CopyData( BLOCK_NODE *pT ,const BLOCK_NODE *pS )
{
	int i = 0;
	for( i = 0; i< BLOCK_SIZE ; i++ )
		pT->Data[i] = pS->Data[i];
	
	return pT;
}

//���ٿ�ڵ�
void DelBlockNode( BLOCK_NODE *pN )
{
	free( pN );
}

//��*pP�����*pN
void InsertBlockNodeAt( BLOCK_NODE *pP, BLOCK_NODE *pN )
{
	pN->Next = pP->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN;
	
	pP->Next = pN;
	pN->Prev = pP;
}

//������ڵ㣬����ǰ���ͺ��ֱ������
void IsolateBlockNode( BLOCK_NODE *pN )
{
	if( pN->Next != NULL )
		pN->Next->Prev = pN->Prev;
	if( pN->Prev != NULL )
		pN->Prev->Next = pN->Next;
	
	pN->Next = NULL;
	pN->Prev = NULL;
}

//�жϸÿ���ָ������Ƿ�Ϊ���һ��
BOOL IsLastCluster( BLOCK_NODE *pN )
{
	return pN->Data[1] == 0;
}

//�жϸÿ�ָ������Ƿ�����
BOOL IsClusterFull( BLOCK_NODE *pN )
{
	if( IsLastCluster( pN ) )
		return pN->Data[0] == ( CLUSTER_SIZE - 1 );
	else 
		return pN->Data[0] == CLUSTER_SIZE;
}

//����
typedef BLOCK_NODE BLOCK_LIST;

BLOCK_LIST	g_HeadBlocks;			//���ڴ�Ŵ�����ȫ���׿�
BLOCK_NODE	g_SpecialBlock;		//�ڴ��е�ר�ÿ飬�ڰ��������е�һ������п�Id
int					g_FreeBlockCount;	//���п�����

//����Id�����׿�
//�ɹ����ظ��׿�Ľڵ�ָ�룬���򷵻�NULL
BLOCK_NODE *FindHeadBlockById( int id )
{
	BLOCK_NODE *pN = g_HeadBlocks.Next;
	
	while( pN != NULL )
	{
		if( pN->Id == id )
			break;
		pN = pN->Next;
	}
	return pN;
}


//����һ�����п�
void FreeOne( int id )
{
	//���ר�ÿ�ָ��������п��У���ֱ���ÿ��п�Id��¼�ڸ���
	if( !IsClusterFull( &g_SpecialBlock ) )
	{
		if( IsLastCluster (&g_SpecialBlock) )//ע����������һ������,Խ��Data[0]���λ
		{
			g_SpecialBlock.Data[ g_SpecialBlock.Data[0] + 2 ] = id;
			g_SpecialBlock.Data[0]++;
		}
		else
		{
			g_SpecialBlock.Data[ g_SpecialBlock.Data[0] + 1 ] = id;
			g_SpecialBlock.Data[0]++;
		}
	}
	else//���ר�ÿ�ָ�������������ר�ÿ�����д�������Ŀ��п飬�����˿���Ϊ��һ����׿�,Ȼ��ר�ÿ�ָ������
	{
		BLOCK_NODE *pN = NewBlockNode( id );
		CopyData( pN, &g_SpecialBlock );
		InsertBlockNodeAt( &g_HeadBlocks, pN );
		g_SpecialBlock.Data[0] = 1;
		g_SpecialBlock.Data[1] = id;
	}
}

//����һ�����п�
//�ɹ����ش˿��Id��ʧ�ܷ���0
int AllocateOne( )
{
	int id = 0;
	if( g_SpecialBlock.Data[0] == 1 )//��������ʣһ��
		if( IsLastCluster( &g_SpecialBlock ) )//����������һ�飬�򽫽�ʣ��һ�����
		{
			id = g_SpecialBlock.Data[2];
			g_SpecialBlock.Data[0] = 0;
			return id;
		}
		else//������������һ�飬�򽫴˿����ݱ��ݵ�ר�ÿ죬Ȼ�����˿�
		{
			BLOCK_NODE *pN = NULL;
			id = g_SpecialBlock.Data[1];
			pN = FindHeadBlockById( id );
			CopyData( &g_SpecialBlock, pN );
			IsolateBlockNode( pN );
			DelBlockNode( pN );
			return id;
		}
	else//������黹ʣ��ֻһ�飬ֱ�ӷ���
		if( IsLastCluster( &g_SpecialBlock ) )//ע�����һ����������
		{
			id = g_SpecialBlock.Data[ g_SpecialBlock.Data[0] + 1 ];
			g_SpecialBlock.Data[0] --;
			return id;
		}
		else
		{
			id = g_SpecialBlock.Data[ g_SpecialBlock.Data[0]];
			g_SpecialBlock.Data[0] --;
			return id;
		}			
}

//���û�������ļ���ʼ��ר�ÿ졢�׿��������п�����
void InitBlocksFromUserInput()
{
	char fileName[MAX_STRLEN];
	FILE *pF = NULL;
	
	//�����û������ļ���
	for( ;; )
	{
		printf("�������ļ�����");
		scanf( "%s", fileName );
		pF = fopen( fileName, "r" );
		if( pF != NULL )
			break;
		printf("�޷��򿪸��ļ�������������ļ����Ƿ���ȷ��\n");
	}
	
	//���ļ���ȡ����
	g_FreeBlockCount = 0;
	g_SpecialBlock.Data[1] = 0;//��ǰ��Ϊ���һ��
	g_SpecialBlock.Data[0] = 0;//��ǰ�麬��0��
	g_HeadBlocks.Next = NULL;
	g_HeadBlocks.Prev = NULL;
	while( !feof( pF ) )
	{
		int id = 0;
		fscanf( pF, "%i",&id);
		FreeOne( id );
		g_FreeBlockCount ++;
	}
	fclose( pF );
}

//�����û������������ҵ���������
void Allocate( )
{
	char	jobName[MAX_STRLEN];
	int 	blockCount = 0;
	int		ids[MAX_JOB_BLOCKS];
	int		i = 0;
	JOB_NODE *pJN = NULL;
	
	printf("��������ҵ����");
	scanf("%s",jobName);
	
	printf("���������Ŀ�����");
	scanf("%i",&blockCount);
	if( blockCount > g_FreeBlockCount )
	{
		printf("����ʧ�ܣ�ԭ�򣺴��̿ռ䲻�㡣\n");
		return;
	}
	else
		g_FreeBlockCount -= blockCount;
	
	pJN = FindJobByName( jobName );
	
	for( i = 0; i < blockCount; i++ )
		ids[i] = AllocateOne();
	
	if( pJN != NULL )
	{
		for( i = 0; i<blockCount; i++ )
			pJN->BlockIds[ pJN->BlockCount++ ];
		printf("����ɹ�������ҵ%s׷����%i�����̿顣\n", pJN->Name, blockCount);
	}
	else
	{
		pJN = NewJobNode( jobName, ids, blockCount );
		InsertJobNodeAt( &g_Jobs, pJN );
		printf("����ɹ����½���ҵ%s����Ϊ�������%i�����̿顣\n",pJN->Name, blockCount);
	}	
	
}

//������ҵ
void FinishJob()
{
	char jobName[MAX_STRLEN];
	JOB_NODE *pJN = NULL;
	
	printf("��������ҵ����");
	scanf("%s",jobName);
	
	pJN = FindJobByName( jobName );
	if( pJN == NULL )
		printf("����ʧ�ܣ��������ҵ�������ڡ�\n");
	else
	{
		printf("�����ɹ������ͷ�%i�����̿顣\n",pJN->BlockCount);
		
		g_FreeBlockCount += g_FreeBlockCount;
		
		while( pJN->BlockCount-- > 0 )
			FreeOne( pJN->BlockIds[pJN->BlockCount] );
			
		IsolateJobNode( pJN );
		DelJobNode( pJN );
	}
	
}

//��Ļ��ӡ����������õĴ��̿����
void PrintJobsTable()
{
	JOB_NODE *pJN = g_Jobs.Next;
	int i = 0;
	printf("===============================================================\n");
	printf("                           ������                            \n");
	printf("---------------------------------------------------------------\n");
	while( pJN != NULL )
	{
		printf("%6s |",pJN->Name);
		for( i = 0; i< pJN->BlockCount; i++ )
			printf("[%i] ", pJN->BlockIds[i]);
		printf("\n");
		pJN = pJN->Next;
	}
	printf("===============================================================\n");
}

//��Ļ��ӡ����Ŀ��п�
void PrintClustersTable()
{
	BLOCK_NODE *pBN = g_HeadBlocks.Next;
	int i = 0;
	int j = 0;
	
	printf("===============================================================\n");
	printf("                           ���п��                            \n");
	printf("---------------------------------------------------------------\n");
	printf("%4i�� | ", ++j);
	if( IsLastCluster( &g_SpecialBlock ) )
		for( i = 0; i< g_SpecialBlock.Data[0]; i++ )
			printf("[%i] ", g_SpecialBlock.Data[i+2]);
	else
		for( i = 0; i< g_SpecialBlock.Data[0]; i++ )
			printf("[%i] ", g_SpecialBlock.Data[i+1]);
	printf("\n");
	
	while( pBN != NULL )
	{
		printf("%4i�� | ", ++j);
		if( IsLastCluster( pBN ) )
			for( i = 0; i< pBN->Data[0]; i++ )
				printf("[%i] ", pBN->Data[i+2]);
		else
			for( i = 0; i< pBN->Data[0]; i++ )
				printf("[%i] ", pBN->Data[i+1]);
		printf("\n");
		
		pBN = pBN->Next;
	}
	printf("===============================================================\n");
	
}

//��Ļ��ӡ�û��˵�
void PrintUserMenu()
{
	printf("===============================================================\n");
	printf("                           ����˵�                            \n");
	printf("---------------------------------------------------------------\n");
	printf("1|������̿ռ� 2|������ҵ 3|�鿴������ 4|�鿴���п�� 0|�˳� \n");
	printf("===============================================================\n");
	printf("��ѡ��");
}

//ִ���û����������
void ExecUserCommand()
{
	char command[MAX_STRLEN];
	for(;;)
	{
		PrintUserMenu();
		scanf("%s",command);
		switch( command[0] )
		{
			case '0':exit(0);
			case '1':Allocate();break;
			case '2':FinishJob();break;
			case '3':PrintJobsTable();break;
			case '4':PrintClustersTable();break;
			default:printf("�������ѡ����ڣ�������ѡ��\n");
		}
	}
}

void main()
{
	InitBlocksFromUserInput();
	ExecUserCommand();
}
