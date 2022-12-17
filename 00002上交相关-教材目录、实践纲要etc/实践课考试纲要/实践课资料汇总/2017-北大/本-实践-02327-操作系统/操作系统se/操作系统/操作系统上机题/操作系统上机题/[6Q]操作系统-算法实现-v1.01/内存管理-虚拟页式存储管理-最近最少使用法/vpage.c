#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN				256
#define PAGE_FRAME_COUNT	3

//ҳ�ڵ�
typedef struct page_node
{
	int Number;
	int LastTime;
	struct page_node *Next;
	struct page_node *Prev;
}PAGE_NODE;

//�½�ҳ�ڵ�,�����뵽����
PAGE_NODE *NewPage( int n, PAGE_NODE *pNext, PAGE_NODE *pPrev )
{
	PAGE_NODE *pNew = NULL;
	pNew = (PAGE_NODE*)malloc( sizeof(PAGE_NODE) );
	pNew->Number = n;
	pNew->LastTime = 0;
	pNew->Next = pNext;
	pNew->Prev = pPrev;
	if( pNew->Next != NULL )
		pNew->Next->Prev = pNew;
	if( pNew->Prev != NULL )
		pNew->Prev->Next = pNew;
	return pNew;
}

//�����з��벢����ҳ�ڵ�
void DelPage( PAGE_NODE *pN )
{
	if( pN->Prev != NULL )
		pN->Prev->Next = pN->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN->Prev;
	free( pN );
}

typedef PAGE_NODE PAGE_LIST;

PAGE_LIST g_PList;
int				g_PageCount = 0;

//Ѱ��ҳ��nΪҳ��ţ�û�ҵ�����NULL
PAGE_NODE *FindPage( int n )
{
	PAGE_NODE *pN = g_PList.Next;
	
	while( pN != NULL )
	{
		if( pN->Number == n )
			break;
		pN = pN->Next;
	}
	return pN;
}

//Ѱ���������ʹ��ҳ
PAGE_NODE *FindLruPage( )
{
	PAGE_NODE *pN = g_PList.Next;
	PAGE_NODE *pN1 = g_PList.Next;
	
	while( pN != NULL )
	{
		if( pN->LastTime > pN1->LastTime )
			pN1 = pN;
		pN = pN->Next;
	}
	return pN1;
}

//��ʱ��
void Timmer()
{
	PAGE_NODE *pN = g_PList.Next;
	
	while( pN != NULL )
	{
		pN->LastTime ++;
		pN = pN->Next;
	}
}

void main()
{
	char fileName[MAX_STRLEN];
	FILE *pf = NULL;
	PAGE_NODE *pN = &g_PList;
	PAGE_NODE *pN1 = NULL;
	g_PList.Next = NULL;
	g_PList.Prev = NULL;
	
	//�������ļ�
	for(;;)
	{
		printf("�������ļ�����");
		scanf("%s",fileName);
		pf = fopen( fileName, "r" );
		if( NULL != pf )
			break;
		else
			printf("�ļ���ʧ�ܣ����������롣\n");
	}
	
	printf("===============================================\n");
	printf("              LRUҳ���û�˳���                \n");
	printf("-----------------------------------------------\n");
	printf("ҳ���� | ����ҳ�� | ����ҳ�� | ����ҳδ����ʱ��\n");
	//�������ļ���ȡ����
	while( !feof( pf ) )
	{
		int n;
		Timmer();
		
		fscanf( pf, "%i", &n );
		
		pN1 = FindPage(n);
		
		if( NULL != pN1 )//������ҳ���ڴ��д���
		{
				printf("%6i | %8c | %8c | \n",n,'*','*');
				pN1->LastTime = 0;//�������ʹ��ʱ��Ϊ0
		}
		else if( g_PageCount < PAGE_FRAME_COUNT )//ҳ��δ��
		{
			pN = NewPage( n, pN->Next, pN );//��ҳ�����ڴ�
			g_PageCount ++;									//ռ��һ��ҳ��
			printf("%6i | %8i | %8c | \n",n,n,'*');
		}
		else//ҳ������
		{
			pN1 = FindLruPage();//�ҵ��������ʹ��ҳ
			printf("%6i | %8i | %8i | %16i\n",n,n,pN1->Number,pN1->LastTime);
			pN = NewPage( n, pN->Next, pN );//��ҳ�����ڴ�
			DelPage( pN1 );		//�������ʹ��ҳ�����ڴ�
		}
			
	} 
	printf("===============================================\n");
}