/*
���� ����洢��������ҳ�����
1�� ���룺
ҳ�����ļ������д洢����һϵ��ҳ��ţ�ҳ�����������ʾ���ÿո���Ϊ�ָ�����������ģ��������ҳ�档
������һ��ʾ�⣺
1 2 3 4 1 2 5 1 2 3 4 5
2�� ����Ҫ��
��������ʱ��������ʾ"������ҳ�����ļ����ļ�����"������һ���ļ����󣬳��򽫶�����ļ��е��й����ݡ�
��ʼ��������������ҳ�򣬳�ʼʱ��Ϊ��
3�� ���Ҫ��
ÿ����һ��ҳ�棨����ÿ����һ��ҳ��ţ����ж��Ƿ���ҳ����Ҫ�����������У��ѱ�������ҳ����������Ļ�ϣ�
��û�У������һ��"*"�š�
4�� �ļ���Լ��
�ύ��Դ�������֣�sourceXXX.c����sourceXXX.cpp��������������ȷ����
�����ļ����֣������û�ָ��
���У�XXXΪ�˺š�
*/
#include <stdio.h>
#include <iostream>            

using namespace std;

const int pageFrameNum=3;
const int arrNum=12;

typedef struct pageFrame
{
   int page;
   int tag;
}pFrame;   //ҳ��



int readFile(int request[arrNum]);  //
void new_line();  //ȥ��û�õ��ַ�

void showRPage(int requestP[arrNum],int rPageNum);
void FIFO(int requestP[arrNum],int rPageNum);

void main()
{
   int request[arrNum];  //���������ҳ���
   int rPNum;   
   rPNum=readFile(request);
   showRPage(request,rPNum);
   FIFO(request,rPNum);
}


int readFile(int request[arrNum])
{
    char fName[50];
	FILE *stream;
	int  rPNum=0;

    cout<<"������ҳ�����ļ����ļ���\n";
	cin.getline(fName,50,'\n');
	stream  = fopen( fName, "r" ); //���ļ�
	while(stream==NULL)
    {
       cout<<"�ļ�����·�����������������ļ���\n";
	   //new_line();
	   cin.getline(fName,50,'\n');
       stream  = fopen( fName, "r" );
	}

	while(!feof(stream))
	{	
	    fscanf(stream,"%d",&request[rPNum]);
        ++rPNum;
	}   
   
    fclose(stream);	

    return rPNum;  
}

void new_line()   //ȥ��û���ַ�
{
    char symbol;
    do
	{
	   cin.get(symbol);
	}while(symbol!='\n');
}

void showRPage(int requestP[arrNum],int rPageNum)
{
   cout<<"\n�����ҳ���Ϊ:\n";
   for(int i=0;i<rPageNum;i++)
   {
       cout<<requestP[i]<<"  ";
   }
}

void FIFO(int requestP[arrNum],int rPageNum)
{  
   pFrame pF[pageFrameNum];
   int i,j,k,exist,count=0;
  //��ʼʱ��ҳ��Ϊ�գ�ֱ�ӵ�������ҳ��
   for(i=0;i<pageFrameNum;i++)
   {
	   pF[i].page=requestP[i];
	   if(i==0)
	   {
	      pF[i].tag=1;   //�滻��־
	   }
	   else
	   {
	      pF[i].tag=0;
	   }  
	   ++count;     //�жϴ�����1
	   
   }

   //��ҳ����ʱ������FIFO�㷨�����滻
   cout<<"\n\n����̭��ҳ�������Ϊ:";
   for(j=i;j<rPageNum;j++)
   {
       exist=0;   //������ҳ�Ƿ����ڴ���
	   for(k=0;k<pageFrameNum;k++)
	   {
	      if(requestP[j]==pF[k].page)
		  {
			  cout<<"*   ";
		      exist=1;
			  break;
		  }
	   }
	   if(exist==0)
	   {
          for(k=0;k<pageFrameNum;k++)
		  {
		     if(pF[k].tag==1)
			 {
			    cout<<pF[k].page<<"  ";
                ++count;
				//��������ҳ
				pF[k].page=requestP[j];
				pF[k].tag=0;
				//���µ��滻��ʶ
				k=(k+1)%pageFrameNum;
				pF[k].tag=1;
			 }
		  }
	   }  
   }
   //����жϴ���
   cout<<"\n\n"<<"����FIFO���жϴ���Ϊ"<<count<<endl;
}

