#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN	256

#define PAGE_SIZE				1024	//�ڴ�ҳ�ߴ�(Byte)
#define	WORD_SIZE 			32		//λͼ���ֳ�
#define MAX_WORDS_COUNT	1024	//λͼ��������

#define BITMAP_TITLE		"λʾͼ"

//λͼ�ṹ
typedef struct
{
	int Bits[WORD_SIZE][MAX_WORDS_COUNT];
	int FreeBitsCount;
	int BitsCount;
}BITMAP;

BITMAP g_Bitmap;

int GetAt( int i )
{
	return ((int *)(g_Bitmap.Bits))[i];
}

void SetAt( int i, int bit)
{
	((int *)(g_Bitmap.Bits))[i] = bit;
}

//�жϵ�i���ڴ��Ƿ�δ��ռ��
BOOL IsFree( int i )
{
	return (GetAt( i ) == 0);
}

//�ͷŵ�i���ڴ�
void Free( int i )
{
	if( !IsFree( i ) )
	{
		SetAt( i, 0);
		g_Bitmap.FreeBitsCount ++;
	}
}

//��ͼռ�øõ�i���ڴ�
//���ÿ��Ѿ���ռ�÷���FALSE��ռ�óɹ�����TRUE
BOOL Allocate( int i )
{
	if( IsFree( i ) )
	{
		SetAt( i, 1);
		g_Bitmap.FreeBitsCount --;
		return TRUE;
	}
	return FALSE;
}

//���û�������ļ���ȡ��Ϣ�����λͼ
void FillBitmapFromUserInput()
{
	char fileName[MAX_STRLEN];
	FILE *pF = NULL;
	
	g_Bitmap.BitsCount = 0;
	g_Bitmap.FreeBitsCount = 0;
	
	//�����ļ���������
	for(;;)
	{
		printf("�������ļ�����");
		scanf("%s",fileName);
		pF = fopen( fileName, "r" );
		if( NULL != pF )
			break;
		printf("�޷��򿪸��ļ�����ȷ���ļ����Ƿ���ȷ��\n");
	}
	
	//���ļ���ȡλͼ��Ϣ
	while( !feof( pF ) )
	{
		char c = fgetc(pF);
		switch( c )
		{
			case '1':
				SetAt(g_Bitmap.BitsCount,1);
				g_Bitmap.BitsCount++;
				break;
			case '0':
				SetAt(g_Bitmap.BitsCount,0);
				g_Bitmap.BitsCount++;
				g_Bitmap.FreeBitsCount++;
				break;
			default:break;
		}
		//��ֹ���
		if( g_Bitmap.BitsCount == MAX_WORDS_COUNT*WORD_SIZE )
			break;
	}
	
	fclose( pF );
}

//��Ļ��ӡλͼ
void PrintBitmap()
{
	int i = 0;
	int j = 0;
	
	for( i=0; i<WORD_SIZE; i++ )
		printf("=");
	printf("\n");
	
	for( i=0; i<(WORD_SIZE - sizeof(BITMAP_TITLE))/2; i++ )
		printf(" ");
	printf("%s\n",BITMAP_TITLE);
	
	
	
	for( i=0; i<WORD_SIZE; i++ )
		printf("-");
	printf("\n");
	
	for( i = 0; i<g_Bitmap.BitsCount; )
	{
		printf("%i",GetAt(i));
		
		if( ++i%WORD_SIZE == 0 || i == g_Bitmap.BitsCount)
		{
			printf("\n");
		}
	}
	
	for( i=0; i<WORD_SIZE; i++ )
		printf("-");
	printf("\n");
	
	printf("���п�����%i\n",g_Bitmap.FreeBitsCount);
	
	for( i=0; i<WORD_SIZE; i++ )
		printf("-");
	printf("\n");
	
	printf("��ߴ磺%i Byte\n",PAGE_SIZE);
	
	for( i=0; i<WORD_SIZE; i++ )
		printf("-");
	printf("\n");
	
	printf("�����ڴ棺%i Byte\n",PAGE_SIZE*g_Bitmap.FreeBitsCount);
	
	for( i=0; i<WORD_SIZE; i++ )
		printf("=");
	printf("\n");
	
}

//�����û���������ڴ棬����Ļ��ӡҳ��
void PrintPageTable( )
{
	int i = 0;
	int j = 0;
	int	mSize = 0;
	int pageCount = 0;
	
	printf("��������Ҫ������ڴ�(Byte)��");
	scanf("%i",&mSize);
	
	if( mSize <= 0 )
	{
		printf("�����������Ч��\n");
		return;
	}
	
	pageCount = (mSize%PAGE_SIZE == 0) ? (mSize/PAGE_SIZE) : (mSize/PAGE_SIZE + 1);
	
	if( pageCount > g_Bitmap.FreeBitsCount )
	{
		printf("�޷������㹻�ڴ档\n");
		return;
	}
		
	printf("���ι�����%iҳ�ڴ棬ҳ�����£�\n",pageCount);
	printf("===========\n");
	printf("ҳ�� | ���\n");
	printf("-----------\n");
	i = 0;
	for( j = 0; j<g_Bitmap.BitsCount; j++)
	{
		if( Allocate(j) )
		{
			printf("%4i | %4i\n",i,j);
			if( ++i == pageCount )
				break;
		}
	}
	printf("===========\n");
}

//��Ļ��ӡ�û��˵�
void PrintUserMenu()
{
	printf("==============================\n");
	printf("          ����˵�            \n");
	printf("------------------------------\n");
	printf("1|�����ڴ� 2|��ʾλʾͼ 0|�˳�\n");
	printf("==============================\n");
	printf("��ѡ��");
}

//�����û������ִ��
void ExecUserCommand()
{
	char command[MAX_STRLEN];//�������ַ�������������ԳԵ��س���������Ч�ַ��������Ը���
	
	for(;;)
	{
		PrintUserMenu();
		scanf("%s",command);
		switch( command[0] )
		{
			case '1':PrintPageTable();break;
			case '2':PrintBitmap();break;
			case '0':exit(0);
			default:printf("���������ѡ�����,������ѡ��");break;
		}
	}
}

void main()
{
	FillBitmapFromUserInput();
	PrintBitmap();
	ExecUserCommand();
}