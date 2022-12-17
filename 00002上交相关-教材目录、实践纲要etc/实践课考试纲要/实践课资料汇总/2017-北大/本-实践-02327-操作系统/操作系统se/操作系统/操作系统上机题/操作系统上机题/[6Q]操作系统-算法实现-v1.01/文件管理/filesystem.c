#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
#define MAX_STRLEN	256

#define ROOT_NAME		"ROOT"

//�ļ�����ö��
typedef enum
{
	T_FILE,
	T_DIR,
	T_ROOT,
}TYPE;

//�ļ��ڵ�
typedef struct _file_node
{
	char Name[MAX_STRLEN];				//�ļ���
	TYPE Type;										//�ļ����ͣ�Ŀ¼���ļ����߸�
	struct _file_node *Father;		//��Ŀ¼
	struct _file_node *Son;				//��Ŀ¼
	struct _file_node *Next;			//���ֵ�
	struct _file_node *Prev;			//���ֵ�
}FILE_NODE;


//�½��ļ��ڵ�
FILE_NODE *NewFileNode( const char *name, TYPE t)
{
	FILE_NODE *pN = (FILE_NODE*)malloc(sizeof(FILE_NODE));
	//��ʼ������
	pN->Next = NULL;
	pN->Prev = NULL;
	pN->Father = NULL;
	pN->Son = NULL;
	pN->Type = t;
	strcpy( pN->Name, name );

	return pN;
}

//�����ļ��ڵ�
void DelFileNode( FILE_NODE *pN )
{
	free( pN );
}

//�����ڵ�
//����ý���ֵܵĹ�ϵ��ͬʱ�����ֵ�֮���������
//����ýڵ�͸�Ŀ¼�Ĺ�ϵ��ͬʱ���֡���Ŀ¼���͡���Ŀ¼����Ŀ¼��֮��������
//ע�⣺����û�н�����ӽڵ�(.Sub)�Ĺ�ϵ
void Isolate( FILE_NODE *pN )
{
	//����ýڵ����丸Ŀ¼����Ŀ¼��ͷ�ڵ�
	//���ͷ�ڵ�ָ����
	if( pN->Father != NULL )
		if( pN->Father->Son == pN )
			pN->Father->Son = pN->Next;
	pN->Father = NULL;

	//�����ͬ���Ĺ�ϵ
	if( pN->Prev != NULL )
		pN->Prev->Next = pN->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN->Prev;
	pN->Prev = NULL;
	pN->Next = NULL;
}

//��*pP�����*pN
//����*pN��Ϊ*pP�����ֵ�
void InsertNext( FILE_NODE *pP, FILE_NODE *pN )
{
	//����ͬ����Ĺ�ϵ
	pN->Next = pP->Next;
	if( pN->Next != NULL )
		pN->Next->Prev = pN;
	pN->Prev = pP;
	pP->Next = pN;

	//�����͸�Ŀ¼�Ĺ�ϵ
	pN->Father = pP->Father;
}

//��*pF�в���*pC
//����*pC��Ϊ*pF���ӽڵ�
void InsertIn( FILE_NODE *pF, FILE_NODE *pC )
{
	if( pF->Son == NULL )
		pF->Son = pC;
	else
		InsertNext( pF->Son, pC );

	pC->Father = pF;
	//�����Կ��Ǹ���pC�����ֵܽڵ�ĸ�ָ��ΪpF���˴�����
}

//��ͬ���ڵ����
//�����ṩ���ļ���������Ѱ�ҽڵ�
//�ɹ����ظýڵ㣬ʧ�ܷ���NULL
FILE_NODE *FindFileNodeByNameType( const FILE_NODE *pN, const char *name, TYPE t )
{
	while( pN != NULL )
	{
		if( t == pN->Type && 0 == strcmp( pN->Name, name ) )
			break;
		pN = pN->Next;
	}
	return pN;
}


FILE_NODE g_Root;			//��Ŀ¼
FILE_NODE *g_pCD = NULL;	//��ǰĿ¼

//��ʼ����Ŀ¼
void InitRoot()
{
	strcpy( g_Root.Name, ROOT_NAME );
	g_Root.Next = NULL;
	g_Root.Prev = NULL;
	g_Root.Father = NULL;
	g_Root.Son = NULL;
	g_Root.Type = T_ROOT;
	g_pCD = &g_Root;
}

//MD
void MakeDir( const char* name )
{
	FILE_NODE *pN = FindFileNodeByNameType( g_pCD->Son, name, T_DIR );
	
	if( pN != NULL )
	{
		printf("����ʧ�ܡ�ԭ��ͬ��Ŀ¼�Ѿ����ڡ�\n");
		return;
	}
	
	pN = NewFileNode( name, T_DIR );
	InsertIn( g_pCD, pN );

	printf("�����ɹ���\n");
}

//RemoveDir�ĸ���������ɾ��������Ŀ¼�ڵ�
void DelAllSubs( FILE_NODE *pN )
{
	pN = pN->Son;

	while( pN != NULL)
	{
		FILE_NODE *pN1 = pN->Next;
		
		Isolate( pN );
		DelAllSubs( pN );
		DelFileNode( pN );
		
		pN = pN1;
	}
}

//RD
void RemoveDir( const char* name )
{
	char command[MAX_STRLEN];
	FILE_NODE *pN = FindFileNodeByNameType( g_pCD->Son, name, T_DIR );
	
	if( pN == NULL )//�ļ���������
	{
		printf("ɾ��ʧ�ܡ�ԭ��ָ��Ŀ¼�����ڡ�\n");
		return;
	}
	else if ( pN->Son == NULL )//��������Ŀ¼��ֱ��ɾ��
	{
		Isolate( pN );
		DelFileNode( pN );
		printf("ɾ���ɹ���\n");
		return;
	}
	
	for(;;)
	{
		printf("��ʾ����ͼɾ����Ŀ¼������Ŀ¼��ȷ��ɾ����<y/n>\n");
		scanf( "%s", command );
		strupr( command );
		switch( command[0] )
		{
			case 'Y':
				{
					Isolate( pN );
					DelAllSubs( pN );
					DelFileNode( pN );
					printf("ɾ���ɹ���\n");
					return;
				}
			case 'N':
				{
					printf("ɾ���������û�ȡ����\n");
					return;
				}
			default:break;
		}
	}	
}

//MF
void CreateFile( const char* name )
{
	FILE_NODE *pN = FindFileNodeByNameType( g_pCD->Son, name, T_FILE );
	
	if( pN != NULL )
	{
		printf("����ʧ�ܡ�ԭ��ͬ���ļ��Ѿ����ڡ�\n");
		return;
	}
	
	pN = NewFileNode( name, T_FILE );
	InsertIn( g_pCD,pN );

	printf("�����ɹ���\n");
}

//DEL
void DeleteFile( const char* name )
{
	FILE_NODE *pN = FindFileNodeByNameType( g_pCD->Son, name, T_FILE );
	
	if( pN == NULL )
	{
		printf("ɾ��ʧ�ܡ�ԭ��ָ���ļ������ڡ�\n");
		return;
	}

	Isolate( pN );
	DelFileNode( pN );
	printf("ɾ���ɹ���\n");
	return;
}

//CD
void CurrentDir( const char* name )
{
	FILE_NODE *pN = FindFileNodeByNameType( g_pCD->Son, name, T_DIR );
	if( pN != NULL)
	{
		g_pCD = pN;
		return;
	}
	else if( 0 == strcmp("..", name ) )
	{
		if( g_pCD->Type != T_ROOT )
			g_pCD = g_pCD->Father;
		return;
	}else if( 0 == strcmp("\\", name ) )
	{
		g_pCD = &g_Root;
		return;
	}
	printf("Ŀ¼ת��ʧ�ܡ�ԭ�򣺲�����ָ��Ŀ¼��\n");
}

//�õ�·��
char* GetPath( FILE_NODE *pCD,char *path )
{	
	char path2[MAX_STRLEN] = "";
	FILE_NODE *pN = pCD;

	while( pN->Type != T_ROOT )
	{
		sprintf( path,"%s\\%s", pN->Name, path2 );
		strcpy( path2,path );
		pN = pN->Father;
	}
	sprintf( path,"%s\\%s", g_Root.Name, path2 );
	return path;
}

//DIR
void Dir( FILE_NODE *pCD )
{
	int i = 0;
	char path[MAX_STRLEN];
	int pathLen = strlen( GetPath( pCD, path ) );
	FILE_NODE *pN = pCD->Son;
	
	while( pN != NULL )
	{
		for( i = 0; i != pathLen; i++ )
			printf(" ");
		if( pN->Type == T_FILE )
		{
			printf("|-%s\n",pN->Name );
		}
		else
		{
			printf("|-[+]%s\n",pN->Name );
			Dir( pN );
		}
		pN = pN->Next;
	}
}

//��Ļ��ӡ������Ϣ
void PrintHelp()
{	
	printf("============================\n");
	printf("     �����ļ�����ϵͳ       \n");
	printf("----------------------------\n");
	printf("   ���� |     ����          \n");
	printf(" CD     | ���ĵ�ǰĿ¼      \n");
	printf(" DIR    | ��ʾ�ļ�����Ŀ¼  \n");
	printf(" DEL    | ɾ���ļ�          \n");
	printf(" EXIT   | �˳�ϵͳ          \n");
	printf(" MD     | ����Ŀ¼          \n");
	printf(" MF     | �����ļ�          \n");
	printf(" HELP   | ��ʾ��������      \n");
	printf(" RD     | ɾ��Ŀ¼          \n");
	printf("============================\n");

}

main()
{
	char command[MAX_STRLEN];
	char parameter[MAX_STRLEN];
	char path[MAX_STRLEN];
	
	InitRoot();
	PrintHelp();

	for(;;)
	{
		printf( "%s>",GetPath( g_pCD,path ) );
		scanf( "%s", command);
		strupr( command );
		if( 0 == strcmp("CD", command ) )
		{
			scanf( "%s", parameter);
			CurrentDir( parameter );
		}else	if( 0 == strcmp("CD..", command ) )
		{
			CurrentDir( ".." );
		}else if( 0 == strcmp("CD\\", command ) )
		{
			CurrentDir( "\\" );
		}
		else if( 0 == strcmp("DIR", command ) )
			Dir( g_pCD );
		else if( 0 == strcmp("MD", command ) )
		{
			scanf( "%s", parameter);
			MakeDir( parameter );
		}
		else if( 0 == strcmp("RD", command ) )
		{
			scanf( "%s", parameter);
			RemoveDir( parameter );
		}
		else if( 0 == strcmp("MF", command ) )
		{
			scanf( "%s", parameter);
			CreateFile( parameter );
		}
		else if( 0 == strcmp("DEL", command ) )
		{
			scanf( "%s", parameter);
			DeleteFile( parameter );
		}
		else if( 0 == strcmp("EXIT", command ) )
			exit(0);
		else if( 0 == strcmp("HELP", command ) )
			PrintHelp();
		else
			printf("%s������Ч����������\n",command);
	}
}