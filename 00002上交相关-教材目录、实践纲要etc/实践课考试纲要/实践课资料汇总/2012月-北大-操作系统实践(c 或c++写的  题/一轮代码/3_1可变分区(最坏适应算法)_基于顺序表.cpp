/*
�ɱ������(���Ӧ�㷨)
 �⣺
1����������ʱ���Ƚ������룺�����������ļ������������У�ÿ���������������ʼ��ַ�����ȣ���Ϊ�����������������Զ��Ÿ�����
2������������������Ļ����ʾ��������������ݣ����������м�¼���ڴ��пɹ�����Ŀ�������ʼַ�ͳ��ȣ��ñ�־λָ���÷����Ƿ���δ����Ŀ�������
3�����û���������û���ʾ����һ���ڴ����룬��ʽΪ����ҵ��������ռ�Ĵ�С��
4����������������㷨ѡ��һ�����������ָ���䣬�޸���Ӧ�����ݽṹ��������������д�ڴ��ѷ���������ʼ��ַ�����ȡ���־λ�������б�־λ��һ��������ָ�������������ĸ���ҵ��
5���ظ�3��4��ֱ������Ϊ�����ַ���0����
6������Ļ����ʾ����µĿ���������ѷ�����������ݡ�

----����������
a
�½�3_1worst.txt:�����±�����
1001,30
2003,50
5006,10 
2���г��򣺰�Ҫ�����뼴��
(���û�����:a.exe 40  b.txt 20
*/

#include <stdio.h>   
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int maxNum=10;
//������
typedef struct  KongXianQu
{
  int sAddress;
  int kxqLength;
  int kxqFlag;
}kxq;

//�ڴ�����
typedef struct NeiCunFengPeiBiao
{
   int sAddress;
   int ncLength;
   string pName;
}NCFPB;

int readFile(kxq arrKxq[]);   //���������ļ�,���ؿ�������
void sort(kxq arr[],int num);  //��ѡ������
void showResult(kxq arrKxq[],int kxqNum,NCFPB nc[],int ncNum);
void new_line();  //ȥ��û�õ��ַ�


void main()
{
   kxq arrKxq[maxNum];
   NCFPB arrNcfpb[maxNum];
   int i=0,j=0,sAddress=0,kLength=0,proLength=0;
   int kxqNum=0,ncNum=0;
   char ch, pName[20];   

   cout<<"----------------���ܣ�ʵ�ֿɱ���������Ӧ�㷨---------------\n";

    //1:����������ļ�������
    kxqNum=readFile(arrKxq);

    //2:���������������
    cout<<"\n2:------------ϵͳ��ǰ������Ϊ:\n";
    cout<<"��ʼ��ַ   ����   ��־λ\n";
	for(i=0;i<kxqNum;i++)
	{
	    cout<<arrKxq[i].sAddress<<"\t";
		cout<<arrKxq[i].kxqLength<<"\t";
		cout<<arrKxq[i].kxqFlag<<"\n";
	}   

	 //(3)�����û�����
	 cout<<"3:--------��������ҵ��������ռ�Ĵ�С ����ڴ������\n";
     do
	 {
		 cout<<"��������������ڴ�:��ҵ��Ϊ\n";
		 //new_line();      //��cout���ʣ��û�õ��ַ����˵�
		 cin.getline(pName,20,'\n');
		 cout<<"����������ռ�Ĵ�С:\n";
		 cin>>proLength;    
     
	   //----��ʼ����----------
        //3_1�Կ��������򣺴Ӵ�С(����������㷨��ǰ��),
        sort(arrKxq,kxqNum);

		if(arrKxq[0].kxqFlag==0 || proLength>arrKxq[0].kxqLength )   //�����������û� �����ڴ�>��0��������,���޷�����
		{
		   cout<<"�޷������ڴ�\n";
		}
		else 
		{
			//b��д�ڴ��ѷ�������  
			arrNcfpb[ncNum].sAddress=arrKxq[0].sAddress;
			arrNcfpb[ncNum].ncLength=proLength;
			arrNcfpb[ncNum].pName=pName;
			++ncNum;

               //��  �޸Ŀ�������
			arrKxq[0].sAddress=arrKxq[0].sAddress+proLength; 		
			arrKxq[0].kxqLength=arrKxq[0].kxqLength-proLength;
			if(arrKxq[0].kxqLength==0)   //���������ĳ���Ϊ0ʱ����0 ��ʾ��������
			{
			   arrKxq[0].kxqFlag=0;   
			   //�Ѳ����õĿ�����ȥ��
               for(i=1;i<kxqNum;i++)
			   {
			      arrKxq[i-1]=arrKxq[i];
			   }
               kxqNum=kxqNum-1;
			}
			else
			{
			   arrKxq[0].kxqFlag=1;   
			} 			 
		} 
        cout<<"���������ڴ��������������(yes/no)\n";
        cin>>ch;
		new_line();		
	 }while( (ch!='N') && (ch!='n'));

      //6������
	  showResult(arrKxq,kxqNum,arrNcfpb,ncNum);	
}


int readFile(kxq arrKxq[])
{
	char fName[50];
	FILE *stream;
	int  kxqNum=0;
    cout<<"����������������ļ���\n";
    //new_line();
	cin.getline(fName,50,'\n');
	stream  = fopen( fName, "r" ); //���ļ�
	while(stream==NULL)
    {
       cout<<"�ļ�����·�����������������ļ���\n";
	   new_line();
	   cin.getline(fName,50,'\n');
       stream  = fopen( fName, "r" );
	}
    
	while(!feof(stream))
	{	
	    fscanf(stream,"%d,%d",&arrKxq[kxqNum].sAddress,&arrKxq[kxqNum].kxqLength);
        arrKxq[kxqNum].kxqFlag=1;  //1��ʾ����������,0��ʾ������
        //kxqNum++;
        kxqNum=kxqNum+1;
	}    
    fclose(stream);

	return kxqNum;
}

void sort(kxq arr[],int num)
{
   int i=0,j=0;
   kxq tem;
   for(i=0;i<num;i++)
   {	  
      for(j=i+1;j<num;j++)
	  {
	     if(arr[i].kxqLength < arr[j].kxqLength)
		 {   
			 tem=arr[i];
			 arr[i]=arr[j];
			 arr[j]=tem;		 
		 }	  
	  }  
   }
}

void showResult(kxq arrKxq[],int kxqNum,NCFPB nc[],int ncNum)
{
   int i=0,j=0;
    cout<<"4-----�µĿ�������Ϊ:\n";
    cout<<"��ʼ��ַ   ����   ��־λ(1��ʾ���ã�0��ʾ������)\n";
	for(i=0;i<kxqNum;i++)
	{
	    cout<<arrKxq[i].sAddress<<"\t";
		cout<<arrKxq[i].kxqLength<<"\t";
		cout<<arrKxq[i].kxqFlag<<"\n";
	}

    cout<<"\n--- -�ڴ��ѷ�������:\n";
    cout<<"---��ʼ��ַ   ����   ������(��־λ)\n";
    for(j=0;j<ncNum;j++)
	{
	    cout<<nc[j].sAddress<<"\t";
		cout<<nc[j].ncLength<<"\t";
		cout<<nc[j].pName<<"\n";
	}
}

void new_line()
{
    char symbol;
    do
	{
	   cin.get(symbol);
	}while(symbol!='\n');
}