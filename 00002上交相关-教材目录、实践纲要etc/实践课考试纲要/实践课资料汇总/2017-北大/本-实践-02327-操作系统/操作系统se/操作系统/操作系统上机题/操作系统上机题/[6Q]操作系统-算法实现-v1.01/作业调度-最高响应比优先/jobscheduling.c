#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN	256

//��ҵ�ڵ�
typedef struct _job_node
{
	char		Name[MAX_STRLEN];
	int			EnterTime;				//��ҵ�������뾮��ʱ�䣬�Ǵ�0:00�����ķ�����
	int			SchemeRunTime;		//��ҵԤ������ʱ��
	int			IsFinished;				//��ҵ�Ƿ����
	int			WaitTime;					//��ҵ�ȴ�ʱ��
	double	Rate;							//��ҵ��Ӧ��
	struct _job_node	*Next;
	struct _job_node	*Prev;
}JOB_NODE;

//�½���ҵ�ڵ�
JOB_NODE *NewJobNode( const char *name, int et, int srt )
{
	JOB_NODE *pN = (JOB_NODE*)malloc( sizeof( JOB_NODE ) );
	pN->EnterTime = et;
	pN->SchemeRunTime = srt;
	pN->IsFinished = FALSE;
	pN->Rate = 1;
	pN->WaitTime = 0;
	strcpy( pN->Name, name );
	pN->Next = NULL;
	pN->Prev = NULL;
}

//��*pP�����*pN
void InsertAt( JOB_NODE *pP, JOB_NODE *pN )
{
	pN->Next = pP->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN;
		
	pP->Next = pN;
	pN->Prev = pP;
}

//���ý������ж�������
void Isolate( JOB_NODE *pN )
{
	if( pN->Next!= NULL )
		pN->Next->Prev = pN->Prev;
	if( pN->Prev != NULL )
		pN->Prev->Next = pN->Next;
		
	pN->Next = NULL;
	pN->Prev = NULL;
}

//���ٽڵ�
void DelJobNode( JOB_NODE *pN )
{
	free( pN );
}

//��ҵ����
typedef JOB_NODE JOB_LIST;

JOB_LIST	g_JList;					//������뾮�е�������ҵ
int				g_Time = 0;				//ϵͳʱ�䣬�Ǵ�0:00�����ķ�����
int				g_StartTime = 0;	//ϵͳ��ʼ������ҵ��ʱ�䣬�Ǵ�0:00�����ķ�����


//���������Ӧ�����ȵ�ԭ���ҵ���һ��δ������ҵ
//�����ҵ��������򷵻�NULL
JOB_NODE *FindNextJob()
{
	JOB_NODE *pN = g_JList.Next;
	JOB_NODE *pMaxRate = NULL;
	
	while( pN != NULL )
	{
		if( (!pN->IsFinished) && ( pMaxRate == NULL ||( pN->Rate > pMaxRate->Rate ) ))
		{
			pMaxRate = pN;
		}
		pN = pN->Next;
	}
	return pMaxRate;
}

//������ҵ
//���н����󣬸���ϵͳʱ��
void DoJobAndUpdateTime( JOB_NODE *pN )
{
	//��ɹ���
	pN->IsFinished = TRUE;
	
	//����ϵͳʱ��
	g_Time += pN->SchemeRunTime;
}

//����ÿ����ҵ�ĵȴ�ʱ�����Ӧ��
void UpdateJobs()
{
	JOB_NODE *pN = g_JList.Next;
	
	while( pN != NULL )
	{
		if( ! pN->IsFinished )
		{
			pN->WaitTime = g_Time - pN->EnterTime;
			pN->Rate = (pN->WaitTime + pN->SchemeRunTime)/pN->SchemeRunTime;
		}
		pN = pN->Next;
	}
}

//�����û�������ļ���������ҵ��
void BuildJListByUserInput()
{
	char 			fileName[MAX_STRLEN];
	FILE 			*pF = NULL;
	JOB_NODE	*pN = NULL;
	char			jobName[MAX_STRLEN];
	int  			srt = 0;
	int  			et = 0;
	
	//�����û�����
	for(;;)
	{
		printf("�������ļ�����");
		scanf("%s",fileName);
		pF = fopen( fileName, "r");
		if( pF != NULL )
			break;
		printf("�޷��򿪸��ļ�����ȷ���ļ����Ƿ���ȷ��\n");
	}
	
	//���ļ���ȡ���ݳ�ʼ����ҵ��
	g_JList.Next = NULL;
	g_JList.Prev = NULL;
	pN = &g_JList;
	while( !feof( pF ) )
	{
		fscanf( pF,"%s %i %i",jobName,&et,&srt);
		InsertAt( pN, NewJobNode( jobName, et, srt ));
		pN = pN->Next;
		if( et > g_StartTime )//���һ����ҵ�������뾮��ʱ�̣�Ϊϵͳ��ʼ���ȵ�ʱ��
			g_StartTime = et;
	}
	
	g_Time = g_StartTime;
	//��ʼ����������ҵ�ĵȴ�ʱ�����Ӧ��
	UpdateJobs();
	
	fclose( pF );
}

//������ҵ��ͬʱ��Ļ��ӡ���ȱ�
void Schemduling()
{
	JOB_NODE *pN = FindNextJob();
	int jobCount = 0;
	int totalTime = 0;
	
	printf("==========================================================================\n");
	printf("                         ��ҵ���ȱ�-�����Ӧ������                        \n");
	printf("--------------------------------------------------------------------------\n");
	printf("��ҵ���� | ����ʱ�� | ��ʼʱ�� | ����ʱ�� | �ȴ�ʱ�� | ����ʱ�� | ��תʱ��\n");
	while( pN != NULL )
	{
		printf("%8s | %8i | %8i | ",pN->Name, pN->EnterTime, g_Time);
		DoJobAndUpdateTime( pN );
		printf("%8i | %8i | %8i | %8i\n",g_Time, pN->WaitTime, pN->SchemeRunTime, g_Time - pN->EnterTime, g_Time - pN->EnterTime);
		totalTime += (g_Time - pN->EnterTime);
		jobCount ++;
		UpdateJobs();
		pN = FindNextJob();
	}
	printf("--------------------------------------------------------------------------\n");
	printf("ƽ����תʱ�� | %i\n",totalTime / jobCount);
	printf("==========================================================================\n");
}

void main()
{
	BuildJListByUserInput();
	Schemduling();
}




