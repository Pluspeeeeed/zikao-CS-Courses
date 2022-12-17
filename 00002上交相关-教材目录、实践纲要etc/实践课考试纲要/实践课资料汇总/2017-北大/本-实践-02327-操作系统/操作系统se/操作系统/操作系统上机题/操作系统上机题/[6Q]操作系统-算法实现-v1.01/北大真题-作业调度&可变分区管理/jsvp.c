#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN	256

#define MEMORY_SIZE 	100 //�ڴ�����(K)
#define MEMORY_START	0 	//�ڴ���ʼ��ַ

//ʱ��ת����������ʱ��ת��Ϊ���Ӽ���
int T2M( int i)
{
	return (i/100)*60 + i%100;
}
//ʱ��ת�������������Ӽ���ת��Ϊʱ��
int M2T( int i)
{
	return (i/60)*100 + i%60;
}

//�ɱ�����ڵ�
typedef struct _vp_node
{
	int Start;					//��ʼ��ַ
	int End;						//������ַ
	int Size;						//������С
	BOOL IsFree;				//�Ƿ����
	struct _vp_node *Next;
	struct _vp_node *Prev;
}VP_NODE;

//�½��ɱ�����ڵ�
VP_NODE *NewVpNode( int start, int size, BOOL isFree )
{
	VP_NODE *pN = ( VP_NODE * )malloc( sizeof( VP_NODE ) );
	
	pN->Next = NULL;
	pN->Prev = NULL;
	pN->Start = start;
	pN->Size = size;
	pN->End = pN->Start + size;
	pN->IsFree = isFree;
	
	return pN;
}
//���ٿɱ�����ڵ�
void DelVpNode( VP_NODE *pN )
{
	free( pN );
}

//��*pP�����*pN
void InsertVpNodeAt( VP_NODE *pP, VP_NODE *pN )
{
	pN->Next = pP->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN;
		
	pN->Prev = pP;
	pP->Next = pN;
}

//�����ڵ㣬����ǰ�����ֱ������
void IsolateVpNode( VP_NODE *pN )
{
	if( pN->Next != NULL )
		pN->Next->Prev = pN->Prev;
	if( pN->Prev != NULL )
		pN->Prev->Next = pN->Next;
	
	pN->Next = NULL;
	pN->Prev = NULL;
}

//�ɱ������
typedef VP_NODE VP_LIST;

VP_LIST g_Vps;//�洢ϵͳ�����пɱ����

//�����ڴ�Ĵ�С��ʼ���ɱ����
void InitVps()
{
	g_Vps.Next = NULL;
	g_Vps.Prev = NULL;
	InsertVpNodeAt( &g_Vps, NewVpNode( MEMORY_START, MEMORY_SIZE,TRUE ) );
}

//������ʼ��ַ���ҿ��÷����ڵ�
//�ɹ����ظ÷�����ʧ�ܷ���NULL
VP_NODE *FindFreeVpByStart( int start )
{
	VP_NODE *pN = g_Vps.Next;
	
	while( pN )
	{
		if( pN->IsFree && pN->Start == start )
			break;
		pN = pN->Next;
	}
	return pN;
}

//���ݽ�����ַ���ҿ��÷����ڵ�
//�ɹ����ظ÷�����ʧ�ܷ���NULL
VP_NODE *FindFreeVpByEnd( int end )
{
	VP_NODE *pN = g_Vps.Next;
	
	while( pN )
	{
		if( pN->IsFree && pN->End == end )
			break;
		pN = pN->Next;
	}
	return pN;
}

//�ͷŷ���
void FreeVp( VP_NODE *pN )
{
	VP_NODE *pN1 = FindFreeVpByEnd( pN->Start );//���ڷ���
	VP_NODE *pN2 = FindFreeVpByStart( pN->End );//���ڷ���
	
	if( pN1 != NULL )//�������ں�
	{
		pN1->Size = pN1->Size + pN->Size;
		pN1->End = pN->End;
		IsolateVpNode( pN );
		DelVpNode( pN );
		pN = pN1;
	}
	if( pN2 != NULL )//�����ھ��ں�
	{
		pN->Size = pN->Size + pN2->Size;
		pN->End = pN2->End;
		IsolateVpNode( pN2 );
		DelVpNode( pN2 );
	}
	pN->IsFree = TRUE;
}

//��ҵ�ڵ�
typedef struct _job_node
{
	char	Name[MAX_STRLEN];	//��ҵ��
	int		RunTime;					//��ҵ����ʱ��
	int		EnterBufTime;			//��ҵ�������뾮��ʱ��
	int		EnterMemTime;			//��ҵ�����ڴ��ʱ��
	int		StartTime;				//��ҵ��ʼ���е�ʱ��
	int		FinishTime;				//��ҵ��ɵ�ʱ��
	int		MemSize;					//��ҵռ���ڴ��С
	BOOL	IsFinished;				//�Ƿ����
	VP_NODE *Vp;						//��ҵռ�õ��ڴ�ɱ����
	struct _job_node *Next;
	struct _job_node *Prev;
}JOB_NODE;

//�½���ҵ�ڵ�
//�½�����ҵ�ڵ㣬Ĭ��Ϊδ��ɣ�δ�����ڴ�
JOB_NODE *NewJobNode( const char *name, int et, int rt, int ms )
{
	JOB_NODE *pN = ( JOB_NODE * )malloc( sizeof( JOB_NODE ) );
	pN->Next = NULL;
	pN->Prev = NULL;
	pN->RunTime = rt;
	pN->EnterBufTime = et;
	pN->MemSize = ms;
	pN->IsFinished = FALSE;
	pN->Vp = NULL;
	pN->StartTime = 0;
	pN->EnterMemTime = 0;
	strcpy( pN->Name, name );
	return pN;
}

//������ҵ�ڵ�
void DelJobNode( JOB_NODE *pN )
{
	free( pN );
}

//��*pP֮�����*pN
void InsertJobNodeAt( JOB_NODE *pP, JOB_NODE *pN )
{
	pN->Next = pP->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN;
	
	pN->Prev = pP;
	pP->Next = pN;
}

//�����ڵ㣬����ǰ�����ֱ������
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

JOB_LIST	g_OuterJobs;			//�ȴ��������뾮����ҵ
JOB_LIST	g_BufJobs;				//���뾮�е���ҵ
JOB_LIST	g_MemJobs;				//�ڴ��е���ҵ
JOB_LIST	g_FinishedJobs;		//��������ҵ
int				g_Time;						//ϵͳʱ��

//δ�������뾮����ҵ���������뾮��ʱ������
void SortOuterJobsByEnterBufTime( )
{
	JOB_NODE *pN = NULL;
	
	int f = 0;
	
	for(;;)
	{
		pN = g_OuterJobs.Next;
		f = 0;
		while( pN->Next != NULL )
		{
			if( pN->Next->EnterBufTime < pN->EnterBufTime )
			{
				JOB_NODE *pN1 = pN->Next;
				IsolateJobNode( pN );
				InsertJobNodeAt( pN1, pN );
				f++;
				continue;
			}
			pN = pN->Next;
		}
		if( f == 0 )
			break;
	}	
}


//���뾮�е���ҵ��������ʱ�����򣬶���ҵ��ǰ
void SortBufJobsByRunTime()
{
	JOB_NODE *pN = NULL;
	
	int f = 0;
	
	for(;;)
	{
		pN = g_BufJobs.Next;
		f = 0;
		while( pN->Next != NULL )
		{
			if( pN->Next->RunTime < pN->RunTime )
			{
				JOB_NODE *pN1 = pN->Next;
				IsolateJobNode( pN );
				InsertJobNodeAt( pN1, pN );
				f++;
				continue;
			}
			pN = pN->Next;
		}
		if( f == 0 )
			break;
	}
}
//�����û��������ļ�����ʼ��g_OuterJobs
void BuildOuterJobsFromUserInput()
{
	char fileName[MAX_STRLEN];
	FILE *pF = NULL;
	JOB_NODE *pJN = NULL;
	
	for(;;)
	{
		printf("�������ļ�����");
		scanf("%s",fileName);
		pF = fopen( fileName, "r" );
		if( pF != NULL )
			break;
		printf("�޷��򿪸��ļ�������������ļ����Ƿ���ȷ��");
	}
	
	g_OuterJobs.Next = NULL;
	g_OuterJobs.Prev = NULL;
	pJN = &g_OuterJobs;
	while( !feof( pF ) )
	{
		char jobName[MAX_STRLEN];
		int et,rt,ms;
		fscanf( pF, "%s %i %i %i", jobName,&et, &rt, &ms );
		InsertJobNodeAt( pJN, NewJobNode( jobName, T2M(et), rt, ms ) );
		pJN = pJN->Next;
	}
	fclose( pF );
}

//���Ե�ǰ�ڴ��Ƿ����������ҵ������
BOOL TestAllocateMemForJob( JOB_NODE * pJN )
{
	VP_NODE *pVN = g_Vps.Next;
	
	while( pVN != NULL )
	{
		if( pVN->Size >= pJN->MemSize && pVN->IsFree == TRUE )
			return TRUE;
		
		pVN = pVN->Next;
	}
	return FALSE;
}
//Ϊ��ҵ�����ڴ�
BOOL AllocateMemForJob( JOB_NODE * pJN )
{
	VP_NODE *pVN = g_Vps.Next;
	
	while( pVN != NULL )
	{
		if( pVN->Size == pJN->MemSize && pVN->IsFree == TRUE )
		{
			pJN->Vp = pVN;
			pVN->IsFree = FALSE;
			return TRUE;
		}
		if( pVN->Size > pJN->MemSize && pVN->IsFree == TRUE )
		{
			VP_NODE *pVN1 = NewVpNode( pVN->Start + pJN->MemSize , pVN->Size - pJN->MemSize,TRUE );
			pVN->End = pVN1->Start;
			pVN->Size = pJN->MemSize;
			InsertVpNodeAt( pVN, pVN1 );
			pJN->Vp = pVN;
			pVN->IsFree = FALSE;
			return TRUE;
		}
		pVN = pVN->Next;
	}
	return FALSE;
}

//�����뾮���ҵ���һ�������ڵ�ǰ�ڴ�״�������еĳ���
JOB_NODE *FindExecutableJobFromBuf( )
{
	JOB_NODE *pN = g_BufJobs.Next;
	
	while( pN != NULL )
	{
		if( TestAllocateMemForJob( pN ) )
			return pN;
		pN = pN->Next;
	}
	return NULL;
}

//��ҵ�������뾮
void EnterBuf( JOB_NODE *pJN )
{
	JOB_NODE *pJN1 = &g_BufJobs;
	IsolateJobNode( pJN );
	while( pJN1->Next != NULL )
		pJN1 = pJN1->Next;
	InsertJobNodeAt( pJN1,pJN );
}

//��ҵ�����ڴ�
void EnterMem( JOB_NODE *pJN )
{
	JOB_NODE *pJN1 = &g_MemJobs;
	IsolateJobNode( pJN );
	pJN->EnterMemTime = g_Time;
	
	//�����ʱ�ڴ���û����ҵ��������ڴ漴��ʼ�������ҵ
	if( pJN1->Next == NULL )
		pJN->StartTime = g_Time;
	
	//�ӵ��ڴ����β��
	while( pJN1->Next != NULL )
		pJN1 = pJN1->Next;
	InsertJobNodeAt( pJN1,pJN );

	//�����ڴ����
	AllocateMemForJob( pJN );
}

//�鿴�ڴ�����ҵ����
int CountMemJobs( )
{
	int i=0;
	JOB_NODE *pJN = g_MemJobs.Next;
	
	while( pJN != NULL )
	{
		i++;
		pJN = pJN->Next;
	}
	return i;
}

//�����ҵ
void FinishJob( JOB_NODE *pJN )
{
	JOB_NODE *pJN1 = &g_FinishedJobs;
	IsolateJobNode( pJN );
	pJN->FinishTime = g_Time;

	//���뵽��ɶ���β
	while( pJN1->Next != NULL )
		pJN1 = pJN1->Next;
	InsertJobNodeAt( pJN1,pJN );

	//�ͷ��ڴ����
	FreeVp( pJN->Vp );
	pJN->Vp = NULL;
}

//ִ����ҵ
void DoJobs()
{
	//����ڴ��е�һ����ҵ������ʱ�������������һ����ҵ����ʼ����ڶ�����ҵ
	if( g_MemJobs.Next != NULL &&  g_Time == (g_MemJobs.Next->StartTime + g_MemJobs.Next->RunTime))
	{
		FinishJob( g_MemJobs.Next );//������һ����ҵ
		if( g_MemJobs.Next != NULL )//��ʼ����ڶ�����ҵ
			g_MemJobs.Next->StartTime = g_Time;
	}
}

//��Ļ��ӡ��ҵ���ȱ�
void PrintFinishedJobs()
{
	JOB_NODE *pJN = g_FinishedJobs.Next;
	int totalTime = 0;
	int jobCount = 0;
	
	printf("=======================================================================\n");
	printf("                            ��ҵ���ȱ�                                 \n");
	printf("-----------------------------------------------------------------------\n");
	printf("��ҵ�� | �������뾮 | �����ڴ� | ��ʼִ�� | ��� | ����ʱ�� | ��תʱ��\n");
	
	while( pJN != NULL )
	{
		printf("%6s | %10i | %8i | %8i | %4i | %8i | %8i\n",
			pJN->Name,
			M2T( pJN->EnterBufTime ),
			M2T( pJN->EnterMemTime ),
			M2T( pJN->StartTime ),
			M2T( pJN->FinishTime ),
			pJN->RunTime,
			pJN->FinishTime - pJN->EnterBufTime);

		totalTime += (pJN->FinishTime - pJN->EnterBufTime);
		jobCount ++;
		pJN = pJN->Next;
	}
	printf("-----------------------------------------------------------------------\n");
	printf("ƽ����תʱ�������ӣ�| %i\n",totalTime/jobCount );
	printf("=======================================================================\n");
}


void main()
{
	
	InitVps();
	BuildOuterJobsFromUserInput();
	SortOuterJobsByEnterBufTime();
	
	for(g_Time=0;g_Time<24*60; g_Time++)//��ʱ
	{
		//ִ���ڴ��е���ҵ
		DoJobs();

		//����Ⱥ�������뾮����ҵ��Ϊ�գ���ĳ����ҵ�������뾮��ʱ�䵽�������ҵ�������뾮
		if( g_OuterJobs.Next != NULL && g_Time == g_OuterJobs.Next->EnterBufTime )
		{
			EnterBuf( g_OuterJobs.Next );
			//������ҵ�������򣬶���ҵ��ǰ
			SortBufJobsByRunTime();
		}
		
		//���뾮��Ϊ�գ����ڴ��е���ҵ������2������ҵ�����뾮�����ڴ�
		if( g_BufJobs.Next != NULL && CountMemJobs() < 2 )
		{
			JOB_NODE *pN = FindExecutableJobFromBuf();
			if( pN != NULL)
				EnterMem( pN );
		}
	}

	PrintFinishedJobs();
}