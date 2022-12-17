#include "stdio.h"
#include "string.h"
#include "malloc.h"

#define maxStr 50
#define maxNum 10  //Ŀ¼�ļ����������޸�

struct NormalFile
{  
   char name[50]; /* �ļ��� */
   int type;/*0����Ŀ¼�ļ���1������ͨ�ļ�*/
   int size;/*�ļ���С*/
};
struct DirectoryNode
{
   int tag;      /*0����˽ڵ�հף�1����������*/
   char name[50];
   int type;  /*0����Ŀ¼�ļ���1������ͨ�ļ�*/
   union
   {
      struct NormalFile *p_normFile; /*����ָ����ͨ�ļ�*/
      struct DirectoryFile *p_dirFile;/*����ָ��Ŀ¼�ļ�*/
   }p_File;/*ע�⿴����ĳ�ʼ������*/
};
struct DirectoryFile
{/*Ŀ¼�ļ���һ���ڵ��������*/      	   
   struct DirectoryNode nodesArray[10];
};


struct DirectoryFile root;
struct DirectoryFile *curOpeDirFile; //curOpeDirFile ���浱ǰ·�������� 2�����ļ���5 ����Ŀ¼ 6ɾ��Ŀ¼����Ĭ��ֵΪroot; ����cd�������޸�
struct DirectoryNode *curOpeDirNode; 

void init();
//
int cd(char *dirName);
//
int create(char *fileName,int fileLength); /*�����ļ�*/
void create_file();
int  searchFile(struct DirectoryFile *curDirFile,char *fileName);  //�ж��ļ���Ψһ��
//
void delName();
int deleteFile(char *);/*ɾ���ļ�*/
//
void lsall();/*��ʾ����Ŀ¼���ļ�*/
void lsall_dirFile(struct DirectoryFile *curDirFile,int n);  //n���� ����ո���
//
void md_dirName();
int serchDirName(struct DirectoryFile *curDirFile,char *dirName);
int md(char *dirName);/*����Ŀ¼*/
//
void rd_dirName();
int rd_dirEmpty(struct DirectoryNode *curDirNode);  //����Ŀ¼���Ƿ��
int rd(char *dirName); /*ɾ��Ŀ¼*/
void rd_del(struct DirectoryFile  *curDirFile);
//
void new_line();       //������һ�еĿհ��ַ�

//int searchDir_cd(struct DirectoryFile *curDirFile,char *dirName);  
//int searchFile_del(struct DirectoryFile *curDirFile,char *fileName);

void main()
{
   int sel;
   char dirName[maxStr];

   init();
   curOpeDirFile=&root;   //���ó�ʼ�ĵ�ǰ·��   
   printf("\nģ���ļ�ϵͳ,ʵ������6��������\n");
   printf("\n �� 1 �ı�Ŀ¼(cd���2�����ļ�(create���3 ɾ���ļ�(del���4 ��ʾĿ¼(lstall���� ��5 ����Ŀ¼(md���6 ɾ��Ŀ¼(rd����; 7 �˳�ϵͳ\n");
   scanf("%d",&sel);
   while(sel!=7)
   {
	   switch(sel)
	   {
		   case 1:
		   {
			  printf("\n��ǰ·��Ϊ:root\\ \n");
			  printf("\n������Ҫ������Ŀ¼��\n");
			  new_line();
			  gets(dirName);
			  cd(dirName);
			  break;
		   }
		   case 2:
		   {
              create_file();
			  break;
		   }
		   case 3:
		   {			  
			  delName();			  
			  break;
		   }
			case 4:
		   {
			  lsall();
			  break;
		   }
		   case 5:
		   {
              md_dirName();
			  break;
		   }
		   case 6:
		   {
			  rd_dirName();
			  break;
		   }	   
	   }
      printf("\n �� 1 �ı�Ŀ¼(cd���2�����ļ�(create���3 ɾ���ļ�(del���4 ��ʾĿ¼(lstall���� ��5 ����Ŀ¼(md���6 ɾ��Ŀ¼(rd����; 7 �˳�ϵͳ\n");
	   scanf("%d",&sel);
   }   
}

/*��ʼ���ļ�ϵͳ*/
void init()
{
     //int i,j;/*j�����������Ӻ�������*/
     int i;
	 
     struct DirectoryFile *curDirFile;
     struct NormalFile *newNormFile;
//     struct DirectoryNode *newNode;
     struct DirectoryFile *newDirFile;
     
     
     for (i=0;i<10;i++)     /*initial a directory*/
       root.nodesArray[i].tag=0;
     
     newDirFile=(struct DirectoryFile *)malloc(1100);   //Ŀ¼A
     for(i=0;i<10;i++)
       newDirFile->nodesArray[i].tag=0;
      
      root.nodesArray[0].tag=1;            //����������                         
      strcpy(root.nodesArray[0].name,"A");
      root.nodesArray[0].type=0;
      root.nodesArray[0].p_File.p_dirFile=newDirFile;
      
     newDirFile=(struct DirectoryFile *)malloc(1100);    //Ŀ¼B
     for(i=0;i<10;i++)
       newDirFile->nodesArray[i].tag=0;
      
      root.nodesArray[1].tag=1;
      strcpy(root.nodesArray[1].name,"B");            
      root.nodesArray[1].type=0;                         
      root.nodesArray[1].p_File.p_dirFile=newDirFile; 

      
      newDirFile=(struct DirectoryFile *)malloc(1100);  //Ŀ¼c
      for(i=0;i<10;i++)
       newDirFile->nodesArray[i].tag=0;
      
      root.nodesArray[2].tag=1;
      strcpy(root.nodesArray[2].name,"C");
      root.nodesArray[2].type=0;                //
      root.nodesArray[2].p_File.p_dirFile=newDirFile;
      
      newNormFile=(struct NormalFile *)malloc(108);    //��ͨ�ļ�F1
      strcpy((*newNormFile).name,"F1");
      (*newNormFile).type=1;
      (*newNormFile).size=500;
      printf("%s\n",(*newNormFile).name);
      
      root.nodesArray[3].tag=1;
      strcpy(root.nodesArray[3].name,(*newNormFile).name);
      root.nodesArray[3].type=(*newNormFile).type;
      root.nodesArray[3].p_File.p_normFile=newNormFile;
      
      newNormFile=(struct NormalFile *)malloc(108);   //��ͨ�ļ�F2
      strcpy((*newNormFile).name,"F2");
      (*newNormFile).type=1; 
      (*newNormFile).size=50;
      printf("%s\n",(*newNormFile).name);
      
      root.nodesArray[4].tag=1;
      strcpy(root.nodesArray[4].name,(*newNormFile).name);
      root.nodesArray[4].type=(*newNormFile).type;
      root.nodesArray[4].p_File.p_normFile=newNormFile;

      newNormFile=(struct NormalFile *)malloc(108);    //��ͨ�ļ�F3
      strcpy((*newNormFile).name,"F3");
      (*newNormFile).type=1;
      (*newNormFile).size=5;
      printf("%s\n",(*newNormFile).name);
      
      root.nodesArray[5].tag=1;
      strcpy(root.nodesArray[5].name,(*newNormFile).name);
      root.nodesArray[5].type=(*newNormFile).type;
      root.nodesArray[5].p_File.p_normFile=newNormFile;  
      
      curDirFile=root.nodesArray[1].p_File.p_dirFile;    //Ŀ¼B�� ָ������Ŀ¼�ļ��� ָ��
      newNormFile=(struct NormalFile *)malloc(108);      //��ͨ�ļ�F4
      strcpy((*newNormFile).name,"F4");
      (*newNormFile).type=1;
      (*newNormFile).size=123;
      printf("%s\n",(*newNormFile).name);
      
      curDirFile->nodesArray[0].tag=1;
      strcpy(curDirFile->nodesArray[0].name,(*newNormFile).name);
      curDirFile->nodesArray[0].type=(*newNormFile).type;
      curDirFile->nodesArray[0].p_File.p_normFile=newNormFile;
      printf("%s\n",curDirFile->nodesArray[0].p_File.p_normFile->name);

      curDirFile=root.nodesArray[2].p_File.p_dirFile;
      newDirFile=(struct DirectoryFile *)malloc(1100);   //Ŀ¼�ļ�D
      for (i=0;i<10;i++)
          newDirFile->nodesArray[i].tag=0;
          
      curDirFile->nodesArray[0].tag=1;
      strcpy(curDirFile->nodesArray[0].name,"D");
      curDirFile->nodesArray[0].type=0;
      curDirFile->nodesArray[0].p_File.p_dirFile=newDirFile;
      
      newNormFile=(struct NormalFile *)malloc(108);    //��ͨ�ļ�F5
      strcpy((*newNormFile).name,"F5");
      (*newNormFile).type=1;
      (*newNormFile).size=321;
      printf("%s\n",(*newNormFile).name);
      
      curDirFile->nodesArray[1].tag=1;
      strcpy(curDirFile->nodesArray[1].name,(*newNormFile).name);
      curDirFile->nodesArray[1].type=(*newNormFile).type;
      curDirFile->nodesArray[1].p_File.p_normFile=newNormFile;

     //��������D�� ��Ŀ¼�ļ�ָ�룬���ڽ������µģ�Ŀ¼�ڵ�F6��FCB�� �� ��Ŀ¼�ڵ�F7��FCB��
      curDirFile=curDirFile->nodesArray[0].p_File.p_dirFile;  
      newNormFile=(struct NormalFile *)malloc(108);         //��ͨ�ļ�F6
      strcpy((*newNormFile).name,"F6");
      (*newNormFile).type=1;
      (*newNormFile).size=10;
      printf("%s\n",(*newNormFile).name);
      
      curDirFile->nodesArray[0].tag=1;
      strcpy(curDirFile->nodesArray[0].name,(*newNormFile).name);
      curDirFile->nodesArray[0].type=(*newNormFile).type;
      curDirFile->nodesArray[0].p_File.p_normFile=newNormFile;
      
      newNormFile=(struct NormalFile *)malloc(108);
      strcpy((*newNormFile).name,"F7");                 //��ͨ�ļ�F7
      (*newNormFile).type=1;
      (*newNormFile).size=70;
      printf("%s\n",(*newNormFile).name);
      
      curDirFile->nodesArray[1].tag=1;
      strcpy(curDirFile->nodesArray[1].name,(*newNormFile).name);
      curDirFile->nodesArray[1].type=(*newNormFile).type;
      curDirFile->nodesArray[1].p_File.p_normFile=newNormFile;	  
}

/*�ı䵱ǰĿ¼*/
int cd(char *dirName)
{	
    int i;  
	int dirFlag=0;
	for(i=0;i<maxNum;i++)
	{
		if(root.nodesArray[i].tag==0) {continue;}
		if(root.nodesArray[i].tag==1)
		{
		   if(root.nodesArray[i].type==1) {continue;}
		   else if(!strcmp(root.nodesArray[i].name,dirName) && root.nodesArray[i].type==0)
		   {
			    dirFlag=1;
				printf("\n����Ŀ¼���л��� root:\\%s\n",dirName);
				curOpeDirFile=root.nodesArray[i].p_File.p_dirFile;  //�����µ�ǰ·��				
				break;
		   }		   
		}
	}	
	if(dirFlag==0)
	{
	   printf("\n%s��û��û��Ŀ¼%s\n","root",dirName);
	}
	return 0;
}

//----------����create����
int create(char *fileName,int fileLength)
{
	int i;
	struct NormalFile *newNormFile;
	//Ϊ�ļ������ڴ棬����ֵ
    newNormFile=(struct NormalFile *)malloc(108);
    strcpy(newNormFile->name,fileName);
    newNormFile->type=1;
    newNormFile->size=fileLength;	

    //�ҵ�ǰ·���¿յ�FcB�����ļ�   
   
	for(i=0;i<maxNum;i++)
	{
	   if(curOpeDirFile->nodesArray[i].tag==0)
	   {
		  curOpeDirFile->nodesArray[i].tag=1;
		  strcpy(curOpeDirFile->nodesArray[i].name,newNormFile->name);
          curOpeDirFile->nodesArray[i].type=1;
		  curOpeDirFile->nodesArray[i].p_File.p_normFile=newNormFile;
		  break;
	   }
	} 
	printf("\n�ļ�%s�����ɹ���\n",fileName);
	return 0;
}


//�����ļ�ʱ��Ҫ��֤�ļ����ڵ�ǰ·���� Ψһ
void create_file()
{
	char fileName[maxStr];
	int fileFlag=0,fileLength;
	
	//---- һ Ҫ��֤�ļ����ڵ�ǰ·���� Ψһ
    printf("\n�������ļ���\n");
	new_line();
	gets(fileName);    
    
	/*20130422 �Լ�Ū�����ˣ���ֻҪ�� �ڵ�ǰ·����
	//------------���ļ�����Ψһ���ļ��Ĳ���λ�ã��±�ֻ���ܲ��� ��root.nodesArray[i]��ĳ��Ŀ¼�ļ��У�
	for(i=0;i<maxNum;i++)
	{
	   if(root.nodesArray[i].tag==1 && root.nodesArray[i].type==0)
	   {
	        curDirFile=root.nodesArray[i].p_File.p_dirFile;
		    //
            fileFlag=searchFile(curDirFile,dirName); 
		    if(fileFlag==0)   //������Ŀ¼�ļ��£����ļ���Ψһ
			{
			    break;
			} 
	   }
	}
	*/

    fileFlag=searchFile(curOpeDirFile,fileName);  //ֻ�ڵ�ǰ·���¿��ļ����Ƿ�Ψһ 
	while(fileFlag==1)
	{
	    printf("\n��ǰ·�����Ѵ����ļ���%s\n",fileName);
        printf("\n������������ �ļ���\n");
		new_line();
		gets(fileName);
		fileFlag=searchFile(curOpeDirFile,fileName); 
	}	 
	//-------��
	printf("\n��������ļ��ĳ���\n");
	scanf("%d",&fileLength);
	create(fileName,fileLength);

}

//ȷ���ļ�����ĳһ��Ŀ¼��Ψһ���ļ������ڣ���fileFlag=1 ���أ�
int  searchFile(struct DirectoryFile *curDirFile,char *fileName)
{
	int fileFlag=0,i;
    //����
    for(i=0;i<maxNum;i++)
	{
	    if(curDirFile->nodesArray[i].tag==1 && curDirFile->nodesArray[i].type==1 && !strcmp(curDirFile->nodesArray[i].name,fileName))
		{
		   fileFlag=1;
           curOpeDirNode=&curDirFile->nodesArray[i];   //���� ɾ���ļ�����
		   break;
		}
	}
    return fileFlag;
}


//------/*ɾ���ļ�*/
void delName()
{
	int fileFlag=0;
    char fileName[maxStr];
	printf("\n������Ҫɾ�����ļ���\n");
	new_line();
	gets(fileName);
    fileFlag=searchFile(curOpeDirFile,fileName);
	if(fileFlag==1)
	{
	   deleteFile(fileName);
	}
	else
	{
	   printf("\nϵͳ�Ҳ����ļ�%s\n",fileName);
	}

}
int deleteFile(char *fileName)
{

   free(curOpeDirNode->p_File.p_normFile);
   curOpeDirNode->tag=0;
   printf("\n�ɹ�ɾ���ļ�%s��\n",fileName); 
   return 0;
}

//--------
void lsall()
{
    int i;
	struct DirectoryFile *curDirFile;
    printf("\n/  \n");
	for(i=0;i<maxNum;i++)
	{
		if(root.nodesArray[i].tag==0) {continue;}
		else if(root.nodesArray[i].tag==1)
		{
		    if(root.nodesArray[i].type==0)  //���Ŀ¼�ļ�
			{
			   printf("%5s%5c\n",root.nodesArray[i].name,'d'); 
			   //�����µ�Ŀ¼�ļ�
               curDirFile=root.nodesArray[i].p_File.p_dirFile;
               lsall_dirFile(curDirFile,5);
			}
			else if(root.nodesArray[i].type==1)  //��ͨ�ļ�
			{
			   printf("%5s%5c%5d\n",root.nodesArray[i].name,'f',root.nodesArray[i].p_File.p_normFile->size); 
			}
		}
	   
	}
}


void lsall_dirFile(struct DirectoryFile *curDirFile,int n)
{   
	int i,k;
	n=n+5;  
   	for(i=0;i<maxNum;i++)
	{
		if(curDirFile->nodesArray[i].tag==0) {continue;}
		else if(curDirFile->nodesArray[i].tag==1)
		{			
		    if(curDirFile->nodesArray[i].type==0)  //���Ŀ¼�ļ�
			{
			   for(k=0;k<n;k++){printf(" ");}
			   printf("%s%5c\n",curDirFile->nodesArray[i].name,'d'); 
			   //�����µ�Ŀ¼�ļ�			   
               lsall_dirFile(curDirFile->nodesArray[i].p_File.p_dirFile,n);
			}
			else if(curDirFile->nodesArray[i].type==1)  //��ͨ�ļ�
			{  			  
			   for( k=0;k<n;k++){printf(" ");}
			   printf("%s%5c%5d\n",curDirFile->nodesArray[i].name,'f',curDirFile->nodesArray[i].p_File.p_normFile->size); 
			}
		}
	   
	}
}


//
void md_dirName()
{
	char dirName[maxStr];
	int dirFlag=0;
    printf("\n������Ŀ¼��\n");
	new_line();
	gets(dirName);   
	
    dirFlag=serchDirName(curOpeDirFile,dirName);
	if(dirFlag==1)
	{
	    printf("\nĿ¼����%s�Ѵ���\n",dirName);
	}
	else
	{
	    md(dirName);
		printf("\nĿ¼%s�����ɹ���\n",dirName);
	}

}

int serchDirName(struct DirectoryFile *curDirFile,char *dirName)
{ 
    int dirFlag=0,i;
    //����
    for(i=0;i<maxNum;i++)
	{
	    if(curDirFile->nodesArray[i].tag==1 && curDirFile->nodesArray[i].type==0 && !strcmp(curDirFile->nodesArray[i].name,dirName))
		{
		   dirFlag=1;
           curOpeDirNode=&curDirFile->nodesArray[i];   //���� ɾ��Ŀ¼����
		   break;
		}
	}
    return dirFlag;
}

int md(char *dirName) /*����Ŀ¼*/
{
	int i;
	struct DirectoryFile *newDirFile;

    newDirFile=(struct DirectoryFile *)malloc(1100);  
	for(i=0;i<maxNum;i++)
	{ newDirFile->nodesArray[i].tag=0; }
	
    //�ҵ�ǰ·���¿յ�FcB�����ļ�    
   
	for(i=0;i<maxNum;i++)
	{
	   if(curOpeDirFile->nodesArray[i].tag==0)
	   {
		  curOpeDirFile->nodesArray[i].tag=1;
		  strcpy(curOpeDirFile->nodesArray[i].name,dirName);
          curOpeDirFile->nodesArray[i].type=0;
		  curOpeDirFile->nodesArray[i].p_File.p_dirFile=newDirFile;
		  break;
	   }
	}
	
	return 0;
}
//
void rd_dirName()
{
    char dirName[maxStr];
	int dirFlag=0,dirEmpty=0,delFlag;
    printf("\n������Ҫɾ���� Ŀ¼��\n");
	new_line();
	gets(dirName);   
	
    dirFlag=serchDirName(curOpeDirFile,dirName);
	if(dirFlag==0)
	{
	    printf("\nĿ¼����%s������\n",dirName);
	}
	else
	{
	    dirEmpty=rd_dirEmpty(curOpeDirNode);  //����ǰĿ¼���Ƿ��
        if(dirEmpty==0)
		{
		   
			free(curOpeDirNode->p_File.p_dirFile);  //�ͷ��ڴ�( 
			curOpeDirNode->tag=0;	
			printf("\nĿ¼%sɾ���ɹ���\n",dirName);
		}
		else
		{
		   //����ɾĿ¼�ǿ�ʱ��
		   printf("\nĿ¼%s�ǿգ�ȷ��Ҫɾ���𣿰� 1 ɾ��.\n",dirName);
           scanf("%d",&delFlag);
           if(delFlag==1)
		   {              
              rd(dirName);  // 
		      printf("\nĿ¼%sɾ���ɹ���\n",dirName);
		   }
		}

		
	}
}

//����Ŀ¼���Ƿ��
int rd_dirEmpty(struct DirectoryNode *curDirNode)
{
     int dirEmpty=0;   //Ĭ��Ϊ��
	 int i;
	 for(i=0;i<maxNum;i++)
	 {
	     if(curDirNode->p_File.p_dirFile->nodesArray[i].tag==1)
		 {
		     dirEmpty=1;
			 break;
		 }
	 }
     return dirEmpty;
}

//
int rd(char *dirName)   /*ɾ��Ŀ¼*/
{
	rd_del(curOpeDirNode->p_File.p_dirFile);   //����ֻ�����������ϸã����Ծ���д�˸�����rd_del
    curOpeDirNode->tag=0;
	return 0;
}
//�ݹ�ɾ��
void rd_del(struct DirectoryFile  *curDirFile)
{
   int i;
   for(i=0;i<maxNum;i++)
	{  	   
	   //tag=0;  �����û�з����ڴ棬��ȻҲ�Ͳ����ͷ�
	   if(curDirFile->nodesArray[i].tag==1 && curDirFile->nodesArray[i].type==1)  //�ļ���FCB
		{
		    free(curDirFile->nodesArray[i].p_File.p_normFile);   
            curDirFile->nodesArray[i].tag=0;
		}
		else if(curDirFile->nodesArray[i].tag==1 && curDirFile->nodesArray[i].type==0)  //FCB�¼��зǿ�Ŀ¼FCB�������ļ��ļ���FCB
		{
		    //
            rd_del(curDirFile->nodesArray[i].p_File.p_dirFile);   //��Ϊ���վ�2�������ҪôFCB��գ�Ҫô�±�Ϊ�ļ���FCB
			//
			curDirFile->nodesArray[i].tag=0;
		}
	} 
}

//-------------
void new_line()
{
    char ch;
	do
	{
	   ch=getchar();
	}while(ch!='\n');
}

/*int searchDir_cd(struct DirectoryFile *curDirFile,char *dirName)   //���ز��ҳɹ�����־
{
	int i;
	int flag=0;
	for(i=0;i<maxNum;i++)
	{
		if(curDirFile->nodesArray[i].tag==0) {continue;}
		if(curDirFile->nodesArray[i].tag==1)
		{
		   if(curDirFile->nodesArray[i].type==1) {continue;}
		   else if(!strcmp(curDirFile->nodesArray[i].name,dirName) && curDirFile->nodesArray[i].type==0)
		   {
				flag=1;	
			    curOpeDirFile=curDirFile->nodesArray[i].p_File.p_dirFile;	
				break;
		   }
		   else
		   {
			    curDirFile=curDirFile->nodesArray[i].p_File.p_dirFile;
                flag=searchDir_cd(curDirFile,dirName);
		   }
		}
	}

	return flag;
}		
*/


/*20130422�� �������⣬�˷�ʱ�侫�����±�ע�͵��ľ��� 
int deleteFile(char *fileName)
{
    int i;
    int flag=0;       //ɾ���ɹ�����־
	struct DirectoryFile *curDirFile;  
  
	for(i=0;i<maxNum;i++)
	{	
		if(root.nodesArray[i].tag==0) {continue;}
		if(root.nodesArray[i].tag==1)  // FCB������Ϊ�ļ���FCB ���ļ���--
		{
		   if(root.nodesArray[i].type==0) {continue;}
		   else if(root.nodesArray[i].type==1 && !strcmp(root.nodesArray[i].name,fileName))
		   {
				flag=1;	
				//�ҵ����ͷ��ļ�ռ���ڴ��� FCB���
				free(root.nodesArray[i].p_File.p_normFile);
				root.nodesArray[i].tag=0;
                printf("\n�ɹ�ɾ���ļ�%s��\n",fileName);
				break;
		   }
		   else
		   {
			    curDirFile=root.nodesArray[i].p_File.p_dirFile; 
                flag=searchFile_del(curDirFile,fileName);
		   }
		}
	}
    //���flag���� root�����޴��ļ��ı�ʶ
	if(flag==0)
	{
	   printf("\nû���ҵ��ļ�%s��\n",fileName);
	}
	
	return 0;
}

int searchFile_del(struct DirectoryFile *curDirFile,char *fileName)
{
    int i;
	int flag=0;
	for(i=0;i<maxNum;i++)
	{
		if(curDirFile->nodesArray[i].tag==0) {continue;}
		if(curDirFile->nodesArray[i].tag==1)
		{
		   if(curDirFile->nodesArray[i].type==0) {continue;}
		   else if(curDirFile->nodesArray[i].type==1 && !strcmp(curDirFile->nodesArray[i].name,fileName))
		   {
				flag=1;	
			    free(curDirFile->nodesArray[i].p_File.p_normFile);
				curDirFile->nodesArray[i].tag=0;
                printf("\n�ɹ�ɾ���ļ�%s��\n",fileName);
				break;
		   }
		   else
		   {
			    curDirFile=curDirFile->nodesArray[i].p_File.p_dirFile;
                flag=searchFile_del(curDirFile,fileName);
		   }
		}
	}
    //�����ʶ����curDirFile�£����޴��ļ�
	if(flag==0)
	{
	   printf("\nû���ҵ��ļ�%s��\n",fileName);
	}
	return flag;
}
*/