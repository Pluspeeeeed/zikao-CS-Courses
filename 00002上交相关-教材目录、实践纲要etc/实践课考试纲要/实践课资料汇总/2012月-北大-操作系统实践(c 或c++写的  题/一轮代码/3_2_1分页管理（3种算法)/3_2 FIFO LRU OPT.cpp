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

  �������: FIFO,LRU,OPT
*/
#include <stdio.h>
#include <iostream>            

using namespace std;

const int pageFrameNum=3;
const int arrNum=30;

typedef struct pageFrame
{
   int page;
   int tag;
}pFrame;   //ҳ��

int readFile(int request[arrNum]);  //
void new_line();  //ȥ��û�õ��ַ�

void showRPage(int requestP[arrNum],int rPageNum);
void FIFO(int requestP[arrNum],int rPageNum);
void LRU(int requestP[arrNum],int rPageNum);
void OPT(int requestP[arrNum],int rPageNum);
int  maxNum(pFrame pF[pageFrameNum],int pNum);  //������㷨����̭ҳ��λ��


void main()
{
   int request[arrNum];  //���������ҳ���
   int rPNum;   
   cout<<"��ҳ�����㷨:FIFO,LRU OPT \n";
   rPNum=readFile(request);
   showRPage(request,rPNum);

   FIFO(request,rPNum);
   LRU(request,rPNum);
   OPT(request,rPNum);  
}


int readFile(int request[arrNum])
{
    char fName[50];
	FILE *stream;
	int  rPNum=0;

    cout<<"\n������ҳ�����ļ����ļ���\n";
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
  //---- һ ��ʼʱ��ҳ��Ϊ�գ�ֱ�ӵ�������ҳ��
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

   //-- ��  ��ҳ����ʱ������FIFO�㷨�����滻
   cout<<"\n\n����FIFO�㷨����̭��ҳ�������Ϊ:\n";
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
				k=(k+1)%pageFrameNum;   //����һ���滻��ʶ
				pF[k].tag=1; 
			 }
		  }
	   }  
   }

   //����жϴ���
   cout<<"\n\n"<<"����FIFO���жϴ���Ϊ"<<count<<endl;
}

void LRU(int requestP[arrNum],int rPageNum)
{
    int pFrame[pageFrameNum];
    int i,j,k,flag,count=0;

	//��ʼҳ��Ϊ�գ�����ҳֱ�ӵ���
	for(i=0;i<pageFrameNum;i++)
	{
	   pFrame[i]=requestP[i];
       ++count;
	}
	cout<<"\n\n����LRU�㷨 ����̭��ҳ�������Ϊ:\n";

    //��ҳ����ʱ    
	for(j=i;j<rPageNum;j++)
	{
	   //flag���ڱ�ʶ����ҳ�Ƿ����ڴ棻������flag=1;
	   flag=0;    
	   for(k=0;k<pageFrameNum;k++)
	   {
	      if(requestP[j]==pFrame[k])
		  {
		      flag=1;
			  cout<<"*   ";
		  }	   
	   }
       if(flag==0)
	   {
	       cout<<pFrame[0]<<"  ";
            ++count;		   
	   }

       //
	   for(k=0;k<pageFrameNum-1;k++)
	   {
		  pFrame[k]=pFrame[k+1];
	   }
	   pFrame[pageFrameNum-1]=requestP[j];

	}
    //���жϴ���
    cout<<"\n\n"<<"����LRU����Ϊ"<<count<<endl;
}

/*
  
	pFrame:page�ŵ����ڴ�ҳ�� tag����δ�������ʵ�λ��
*/
void OPT(int requestP[arrNum],int rPageNum)
{
   int i,j,k,m,flag,pos;
   int count=0;
   pFrame pF[pageFrameNum];
   //��ʼʱ������ҳֱ��װ���ڴ棨����ҳ��
    for(i=0;i<pageFrameNum;i++)
	{
	   pF[i].page=requestP[i];
	   pF[i].tag=-1;       
	   ++count;
	}

	 cout<<"\n\n����OPT�㷨�û�ʱ������̭��ҳ������Ϊ:\n";
   //�� ��ҳ����ʱ��
   for(j=i;j<rPageNum;j++)
   {
      flag=0;
	  for(k=0;k<pageFrameNum;k++)
	  {
	     if(requestP[j]==pF[k].page)
		 {
		    flag=1;
			cout<<"*  ";
			break;
		 }	  
	  }
	  if(flag==0)
	  {
	     //����ҳ����ҳ�� ����ҳ�����е�λ��

         for(m=0;m<pageFrameNum;m++)    //����ϴεĽ��
		 {
		     pF[m].tag=-1;   
		 }

		 for(m=0;m<pageFrameNum;m++)
		 {
		    for(k=j;k<rPageNum;k++) 
			{
			   if(requestP[k]==pF[m].page)
			   {
			      pF[m].tag=k;
				  break;
			   }
			}

		 }

		 //�ҵ� λ��ֵ���� ҳ����ҳλ��
          pos=maxNum(pF,pageFrameNum);

		 //�û�
         cout<<pF[pos].page<<"  ";
		 ++count;

		 pF[pos].page=requestP[j];
		 pF[pos].tag=-1;
         
	  }//if end 

   }//for end

   //�жϴ���
   cout<<"\n����OPT�㷨�û�ʱ���жϴ���Ϊ:"<<count<<endl;
}


int  maxNum(pFrame pF[pageFrameNum],int pNum)
{
   int  maxN,i,pos;

   maxN=pF[0].tag;
   pos=0;

   for(i=1;i<pNum;i++)
   {
	  if(pF[i].tag==-1)   //��ʾ��ҳ���ڵ�ҳ�� δ�������������в����ڣ���������������
	  {
	     pos=i;
		 break;
	  }
      else if(maxN<pF[i].tag) // ���ҳ���ڵ�ҳ ��δ�������������д���ʱ�����������λ��
	  {
	     maxN=pF[i].tag;
		 pos=i;
	  }
   }

   return pos;
}
