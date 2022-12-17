#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN	256

#define TIME_SLICE	3		//ʱ��Ƭ����

typedef struct _process_node
{
	char		Name[MAX_STRLEN];	//������
	int			SchemeRunTime;		//Ԥ������ʱ��
	int			RunTime;					//������ʱ��
	int			WaitTime;					//�ѵȴ�ʱ��
	BOOL		IsFinished;				//�Ƿ����
	struct _process_node *Next;
	struct _process_node *Prev;
}P_NODE;

//�½��ڵ�
P_NODE *NewPNode( const char *name, int srt )
{
	P_NODE *pN = (P_NODE*)malloc( sizeof(P_NODE) );
	pN->Next = NULL;
	pN->Prev = NULL;
	pN->IsFinished = FALSE;
	pN->RunTime = 0;
	pN->WaitTime = 0;
	pN->SchemeRunTime = srt;
	strcpy( pN->Name, name );
	return pN;
}

//���ٽڵ�
void DelPNode( P_NODE *pN )
{
	free( pN );
}

//����ڵ�
//����ýڵ�ͬǰ�򡢺�̵Ĺ�ϵ����ǰ����ֱ������
void Isolate( P_NODE *pN )
{
	if( pN->Next != NULL )
		pN->Next->Prev = pN->Prev;
		
	if( pN->Prev != NULL )
		pN->Prev->Next = pN->Next;
}

//��*pP�����*pN
void InsertAt( P_NODE *pP, P_NODE *pN )
{
	pN->Next = pP->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN;

	pN->Prev = pP;
	pP->Next = pN;
}

//��������
typedef P_NODE P_LIST;

P_LIST g_PList;//���ϵͳ��ȫ������

//��ʼ���������̶���
void InitQuene()
{
	g_PList.Next = NULL;
	g_PList.Prev = NULL;
}

//���
void EnQuene( P_NODE *pN )
{
	P_NODE *pRear = &g_PList;
	
	while( pRear->Next != NULL )
		pRear = pRear->Next;
	
	InsertAt( pRear, pN );
}

//����
//�����п�ʱ����NULL
P_NODE *DeQuene( )
{
	P_NODE *pN = g_PList.Next;
	
	if( pN != NULL )
		Isolate( g_PList.Next );
	
	return pN;
}


//�����û��ṩ�������ļ�����ʼ����������
void BuildPListFromUserInput()
{
	char fileName[MAX_STRLEN];
	char procName[MAX_STRLEN];
	int  srt = 0;
	FILE *pF = NULL;
	
	//�����û�����
	for( ;; )
	{
		printf("�������ļ���:");
		scanf("%s", fileName );
		pF = fopen( fileName, "r");
		if( pF != NULL )
			break;
		printf("�޷��򿪸��ļ�����ȷ��������ļ����Ƿ���ȷ��\n");
	}
	
	//��ȡ�ļ�
	InitQuene();
	while( !feof( pF ) )
	{
		fscanf( pF,"%s %i",procName, &srt );
		EnQuene( NewPNode( procName, srt ) );
	}	
	fclose( pF );
}

void PrintScheduingTable()
{
	int			totalWaitTime = 0;
	int			totalProc     = 0;
	int			timeslice			= 0; //ÿ��ʵ�ʷ����ʱ��
	P_NODE *pN = DeQuene();
	
	printf("==============================================================\n");
	printf("                    ���̵��ȱ�-ʱ��Ƭ��ת��                   \n");
	printf("--------------------------------------------------------------\n");
	printf("������ | ��������ʱ�� | �ۼ�����ʱ�� | �ۼƵȴ�ʱ�� | �Ƿ����\n");
	
	while( pN != NULL )
	{
		if( g_PList.Next == NULL )//��������һ������,�����ý�������ʣ��ʱ��
			timeslice =  pN->SchemeRunTime - pN->RunTime;
		else//���ʣ������ʱ��С��ʱ��Ƭ���򱾴�ֻ��������ʣ��ʱ��
			timeslice = (pN->SchemeRunTime - pN->RunTime) < TIME_SLICE ? (pN->SchemeRunTime - pN->RunTime) : TIME_SLICE;
		
		pN->RunTime += timeslice;//��������ʱ��
		
		if( pN->RunTime >= pN->SchemeRunTime )
			pN->IsFinished = TRUE;
		
		printf("%6s | %12i | %12i | %12i | %8s\n",pN->Name, timeslice, pN->RunTime, pN->WaitTime,pN->IsFinished?"���":"δ���" );
		
		
		{ //���¶��������½��̵ĵȴ�ʱ��
			P_NODE *pN1 = g_PList.Next;
			while( pN1 != NULL )
			{
				pN1->WaitTime += timeslice;
				pN1 = pN1->Next;
			}
		}
		
		//��δ��ɽ����β,����ɾͲ������
		if( !pN->IsFinished )
			EnQuene(pN);
		else
		{
			totalWaitTime += pN->WaitTime;
			totalProc ++;
			DelPNode( pN );
		}
		
		//��һ�����̳���
		pN = DeQuene();
	}
	
	printf("--------------------------------------------------------------\n");
	printf("ÿ����ƽ���ۼƵȴ�ʱ�� | %i\n",totalWaitTime/totalProc);
	printf("==============================================================\n");
}

void main()
{
	BuildPListFromUserInput();
	PrintScheduingTable();
}