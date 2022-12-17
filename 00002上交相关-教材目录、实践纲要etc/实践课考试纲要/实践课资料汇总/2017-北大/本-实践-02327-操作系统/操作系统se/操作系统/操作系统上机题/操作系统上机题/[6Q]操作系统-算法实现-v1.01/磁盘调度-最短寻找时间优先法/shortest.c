#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN			256
#define MAX_TRACK_COUNT	256
#define STR_TITLE				"���̵���-���Ѱ��ʱ������"


typedef struct
{
	int		Track;
	BOOL	IsVisted;
	int		Order;
}REQUEST;

REQUEST g_Requests[MAX_TRACK_COUNT];
int			g_RequestsCount = 0;
int			g_StartTrack = 0;

//�������棬�õ�������*pIndex
//���ҳɹ�����TRUE,����ʧ�ܷ���FALSE
BOOL FindTrack( int track , int *pIndex)
{
	int i = 0;
	for( i=0; i<g_RequestsCount; i++ )
	{
		if( g_Requests[i].Track == track )
		{
			*pIndex = i;
			return TRUE;
		}
	}
	return FALSE;
}

//��Ļ��ӡ��������������
void PrintRequests()
{
	int i=0;
	for( i=0; i<g_RequestsCount; i++ )
		printf("====");
	printf("\n");
	
	for( i=0; i<(g_RequestsCount*4 - strlen("����������"))/2; i++ )
		printf(" ");
	printf("����������\n");
	
	for( i=0; i<g_RequestsCount; i++ )
		printf("----");
	printf("\n");
	
	for( i=0; i<g_RequestsCount; i++ )
		printf("%3i|",g_Requests[i].Track);
	printf("\n");
	
	for( i=0; i<g_RequestsCount; i++ )
		printf("----");
	printf("\n");
}

//���û�������ļ���ȡ�������������Ҫ���û����뵱ǰ����
void InitRequestsFromUserInput()
{
	char	fileName[MAX_STRLEN];
	int		i = 0;
	FILE	*fp = NULL;
	
	//���������ļ���
	for(;;)
	{
		printf("�������ļ�����");
		scanf("%s",fileName);
		fp = fopen( fileName,"r");
		if( fp == NULL )
			printf("�޷��򿪸��ļ������������롣\n");
		else
			break;
	}
	
	//���ļ���ȡ���������
	g_RequestsCount = 0;
	while( !feof(fp) )
	{
		fscanf(fp,"%i",&(g_Requests[g_RequestsCount].Track));
		g_Requests[g_RequestsCount].IsVisted = FALSE;
		g_Requests[g_RequestsCount].Order = g_RequestsCount;
		g_RequestsCount ++;
	}
	
	//����ѡ��ǰ����
	PrintRequests();
	printf("��ѡ��ǰ���棺");
	scanf("%i", &g_StartTrack );
	while( !FindTrack(g_StartTrack,&i) )
	{
		printf("����������治���ڣ�������ѡ��");
		scanf("%i", &g_StartTrack );
	}
}

//������С��������
void SortByTrack()
{
	int i = 0;
	int j = 1;
	REQUEST r;
	
	while( j>0 )
	{
		j = 0;
		for( i=1; i<g_RequestsCount; i++ )
		{
			if( g_Requests[i-1].Track >g_Requests[i].Track )
			{
				r = g_Requests[i];
				g_Requests[i] = g_Requests[i-1];
				g_Requests[i-1] = r;
				j++;
			}
		}
	}
}

//��Ļ��ӡ��ͷ
void PrintHead()
{
	int i = 0;
	int titleAt = (g_RequestsCount*5 - strlen(STR_TITLE))/2;
	
	for( i=0; i<g_RequestsCount; i++ )
		printf("=====");
	printf("\n");
	
	for( i=0; i<titleAt; i++ )
		printf(" ");
	printf("%s\n",STR_TITLE);
	
	for( i=0; i<g_RequestsCount; i++ )
		printf("--+--");
	printf("\n");
	
	for( i=0; i<g_RequestsCount; i++ )
		printf("[%3i]",g_Requests[i].Track);
	printf("\n");
	
	for( i=0; i<g_RequestsCount; i++ )
		printf("--+--",g_Requests[i].Track);
	printf("\n");
}
//��Ļ��ӡ��β
void PrintBottom()
{
	int len = g_RequestsCount*5;
	int i = 0;
	for( i=0; i<len; i++ )
		printf("=");
	printf("\n");
}

//��Ļ��ӡ���еļ�ͷ
//iFrom��iTo�ֱ��ǳ�������������ͽ������������
void PrintCursor(int iFrom, int iTo)
{
	int i = 0;
	if( iFrom < iTo )
	{
		for( i=0; i<iFrom; i++ )
			printf("     ");
		printf("  |--");
		for( i=iFrom; i<iTo-1; i++ )
			printf("-----");
		printf("->|");
	}
	else
	{
		for( i=0; i<iTo; i++ )
			printf("     ");
		printf("  |<-");
		for( i=iTo; i<iFrom-1; i++ )
			printf("-----");
		printf("--|");
	}
	printf("\n");
}

//Ѱ����һ��û�б����ʵ����棬�õ�������*pITo
//���ȫ�����涼�Ѿ������ʣ�����FALSE
//���������Ѱ��ʱ�䷨
BOOL GetNext( int iFrom , int *pITo)
{
	//������̬�������ֱ��¼��ǰ���Ⱥ�Ѱ�ҵ���Զλ��
	static int __front = -100;
	static int __next;
	
	if( __front == -100 )//���__front==100˵���ǵ�һ�ε��øú��������ʼ��
	{
		__front = iFrom - 1;
		__next = iFrom + 1;
	}
	
	if( __next == g_RequestsCount && __front<0 )
  	return FALSE;
  if( __next == g_RequestsCount )
  {
		*pITo = __front;
		__front--;
	}
 else if( __front<0 )
 {
 		*pITo = __next;
		__next++;
 }
 else
  *pITo = (g_Requests[iFrom].Track - g_Requests[__front].Track ) <(g_Requests[__next].Track - g_Requests[iFrom].Track ) ? __front-- : __next++;
  
 return TRUE;

}

void main()
{
	int iFrom = 3;
	int iTo = 0;
	
	InitRequestsFromUserInput();
	SortByTrack();
	PrintHead();
	
	FindTrack( g_StartTrack, &iFrom);
	g_Requests[iFrom].IsVisted = TRUE;
	while( GetNext( iFrom, &iTo) )
	{
		PrintCursor(iFrom,iTo);
		g_Requests[iTo].IsVisted = TRUE;
		iFrom = iTo;
	}
	PrintBottom();
}