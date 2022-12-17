#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN	256


//�ɱ��������
typedef struct vp_node
{
	int StartAddress;
	int Capacity;
	BOOL IsFree;
	char User[MAX_STRLEN];
	struct vp_node *Next;
	struct vp_node *Prev;
}VP_NODE;

//�����������½�㣬����UserΪռ����ҵ������User==NULLʱ��Ϊ�÷���ΪFree
VP_NODE *NewNode( int sa, int c, char *user, VP_NODE *pNext ,VP_NODE *pPrev)
{
	VP_NODE *pN = (VP_NODE*)malloc( sizeof( VP_NODE ) );
	pN->StartAddress = sa;
	pN->Capacity = c;
	
	pN->Next = pNext;
	if( NULL != pNext )
		pNext->Prev = pN;
		
	pN->Prev = pPrev;
	if( NULL != pPrev )
		pPrev->Next = pN;
		
	if( user != NULL )
	{ 
		strcpy( pN->User,user);
		pN->IsFree = FALSE;
	}
	else
		pN->IsFree = TRUE;
		
	return pN;
}

//���벢���ٽ��
void DelNode( VP_NODE *pN )
{
	if( pN->Prev != NULL )
		pN->Prev->Next = pN->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN->Prev;
	free( pN );
}

//�ɱ������
typedef VP_NODE VP_LIST;

VP_LIST g_VpList;

void BuildListFromUserInput()
{
	char fileName[MAX_STRLEN];
	VP_NODE *pN = &g_VpList;
	FILE *pf = NULL;
	
	for(;;)
	{
		printf("�������ļ�����");
		scanf("%s",fileName);
		
		pf = fopen(fileName,"r");
		
		if( NULL == pf )
			printf("���ļ�ʧ�ܣ���ȷ�������Ƿ���ȷ��\n");
		else
			break;
	}
	
	while( !feof(pf) )
	{
		int sa;
		int c;
		fscanf( pf,"%i %i",&sa, &c);
		
		pN->Next = NewNode( sa, c, NULL, NULL, pN );
		pN = pN->Next;
	}
	fclose( pf );
}

//��Ļ��ӡ���з�����
void PrintFreeTable()
{
	VP_NODE *pN = g_VpList.Next;
	printf("===================\n");
	printf("    ���з�����     \n");
	printf("-------------------\n");
	printf("��ʼ��ַ | ��������\n");
	while( NULL != pN )
	{
		if( pN->IsFree )
		printf("%8i | %8i\n",pN->StartAddress, pN->Capacity);
		pN=pN->Next;
	}	
	printf("===================\n");
}

//��Ļ��ӡ�ѷ��������
void PrintUsedTable()
{
	VP_NODE *pN = g_VpList.Next;
	printf("==============================\n");
	printf("         �ѷ�������           \n");
	printf("------------------------------\n");
	printf("��ʼ��ַ | �������� | ��ҵ����\n");
	while( NULL != pN )
	{
		if(!pN->IsFree)
			printf("%8i | %8i | %8s\n",pN->StartAddress, pN->Capacity,pN->User);
		pN=pN->Next;
	}	
	printf("===============================\n");
}

//��Ļ��ӡ�ڴ�����
void PrintMemoryTable()
{
	VP_NODE *pN = g_VpList.Next;
	printf("==============================\n");
	printf("         �ڴ�����           \n");
	printf("------------------------------\n");
	printf("��ʼ��ַ | �������� | �������\n");
	while( NULL != pN )
	{
		printf("%8i | %8i | %8s\n",pN->StartAddress, pN->Capacity,pN->IsFree?"����":pN->User);
		pN=pN->Next;
	}	
	printf("===============================\n");
}

//�����Ӧ����
VP_NODE *WorstFitAllocate( char *jobName,int size )
{
	VP_NODE *pMax = NULL;
	VP_NODE *pN = g_VpList.Next;
	VP_NODE *pNew = NULL;
	
	//�ҵ����Ŀ��з���
	while( NULL != pN )
	{
		if( pN->IsFree && ( NULL == pMax || pMax->Capacity < pN->Capacity ) )
			pMax = pN;
		pN=pN->Next;
	}
	
	if( NULL==pMax || pMax->Capacity < size )
		return NULL;
	
	pNew = NewNode( pMax->StartAddress,
		size,
		jobName,
		pMax,
		pMax->Prev);
		
	pMax->Capacity -= size;
	pMax->StartAddress += size;
	
	if( 0 == pMax->Capacity )
		DelNode( pMax );
		
	return pNew;
}

//���շ���
void Free( VP_NODE *pN )
{
	VP_NODE *pN1 = g_VpList.Next;
	
	pN->IsFree = TRUE;
	strcpy(pN->User,"\0");
	
	//Ѱ�����ڣ��ϲ�
	while( pN1 != NULL )
	{
		if( pN1->IsFree && (pN1->StartAddress + pN1->Capacity ) == pN->StartAddress )
		{
			pN1->Capacity += pN->Capacity;
			DelNode( pN );
			pN = pN1;
			break;
		}
		pN1 = pN1->Next;
	}
	
	//Ѱ�����ڣ��ϲ�
	pN1 = g_VpList.Next;
	while( pN1 != NULL )
	{
		if( pN1->IsFree && (pN->StartAddress + pN->Capacity) == pN1->StartAddress )
		{
			pN->Capacity += pN1->Capacity;
			DelNode( pN1 );
			break;
		}
		pN1 = pN1->Next;
	}
}

//�����û����룬Ϊ��ҵ�����ڴ�
void NewJob()
{
	char jobName[MAX_STRLEN];
	int size = 0;
	VP_NODE *pN = NULL;
	
	printf("��������ҵ����");
	scanf("%s",jobName);
	printf("����������ռ��С��");
	scanf("%i",&size);
	
	pN = WorstFitAllocate( jobName, size );
	if( NULL == pN )
		printf("����ʧ��!");
	else
	{
		printf("==============================\n");
		printf("           ����ɹ�           \n");
		printf("------------------------------\n");
		printf("��ʼ��ַ | �������� | ��ҵ����\n");
		printf("%8i | %8i | %8s\n",
			pN->StartAddress,
			pN->Capacity,
			pN->User);
		printf("==============================\n");
	}
}

//�����û����룬������ҵ�������ڴ�
void DelJob( )
{
	char jobName[MAX_STRLEN];
	VP_NODE *pN = g_VpList.Next;
	
	printf("��������ҵ����");
	scanf("%s",jobName);
	
	//�ҵ�Ҫ��������ҵ
	while( NULL != pN )
	{
		if( 0 == strcmp(pN->User, jobName) )
			break;
		pN=pN->Next;
	}
	
	if( NULL==pN )
		printf("�Բ�����Ҫ��������ҵ�����ڡ�\n");
	else
	{
		Free( pN );
		printf("��ҵ�����ɹ���\n");
	}
}

void main()
{
	char command[MAX_STRLEN];
	BuildListFromUserInput();
	PrintFreeTable();
	for(;;)
	{
		printf("============================================================================\n");
		printf("                                   ����˵�                                 \n");
		printf("----------------------------------------------------------------------------\n");
		printf("1|����ռ�  2|������ҵ  3|��ʾ���б�  4|��ʾ�ѷ����  5|�鿴ȫ���ڴ�  0|�˳�\n");
		printf("============================================================================\n");
		printf("��ѡ��");
		scanf("%s",command);
		switch( command[0] )
		{
			case '1':NewJob();break;
			case '2':DelJob();break;
			case '3':PrintFreeTable();break;
			case '4':PrintUsedTable();break;
			case '5':PrintMemoryTable();break;
			case '0':exit(0);
			default:printf("�������ѡ����ڣ�������ѡ��\n");
		}
	}
}



