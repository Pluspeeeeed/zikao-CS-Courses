/*
�ɱ������(�״���Ӧ�㷨/������㷨/��������㷨)
 �⣺
1����������ʱ���Ƚ������룺�����������ļ������������У�ÿ���������������ʼ��ַ�����ȣ���Ϊ�����������������Զ��Ÿ�����
2������������������Ļ����ʾ��������������ݣ����������м�¼���ڴ��пɹ�����Ŀ�������ʼַ�ͳ��ȣ��ñ�־λָ���÷����Ƿ���δ����Ŀ�������
3�����û���������û���ʾ����һ���ڴ����룬��ʽΪ����ҵ��������ռ�Ĵ�С��
4������ �״�(����) �����㷨ѡ��һ�����������ָ���䣬�޸���Ӧ�����ݽṹ��������������д�ڴ��ѷ���������ʼ��ַ�����ȡ���־λ�������б�־λ��һ��������ָ�������������ĸ���ҵ��
5���ظ�3��4��ֱ������Ϊ�����ַ���0����
6������Ļ����ʾ����µĿ���������ѷ�����������ݡ�

----����������

�״���Ӧ�㷨  3_1first.txt
������㷨  3_1worst.txt
��������㷨  3_1best.txt

*/
#include <stdio.h>   
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int maxNum=10;
int kxqNum=0,ncNum=0;   

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

void first(kxq arrKxq[],NCFPB arrNcfpb[]);  //�״���Ӧ�㷨
void worst(kxq arrKxq[],NCFPB arrNcfpb[]);  //�����Ӧ�㷨
void best(kxq arrKxq[],NCFPB arrNcfpb[]);   //��������㷨

void sortFirst(kxq arr[]);  //����������ַ ��С������
void sortWorst(kxq arr[]);  //������������ �Ӵ�С
void sortBest(kxq arr[]);    //������������ ��С����

int readFile(kxq arrKxq[]);
void showResult(kxq arrKxq[],NCFPB nc[]);
void outKxq(kxq arrKxq[]);

void new_line();  //ȥ��û�õ��ַ�


void main()
{
    kxq arrKxq[maxNum];
    NCFPB arrNcfpb[maxNum]; 
    int selNum=0,flag=1;;
	cout<<"----------------���ܣ�ʵ�ֿɱ���������㷨---------------\n";

	kxqNum=readFile(arrKxq);
	//2:���������������
	outKxq(arrKxq);
	//(3)�����û�����   
	while(flag!=0)
	{
		cout<<"��������㷨�����ڴ�ķ���,��ѡ�� 1:�״���Ӧ�㷨; 2:�����Ӧ�㷨; 3:��������㷨��0:�����ڴ����� \n";
	    cin>>selNum;
		switch(selNum)
		{
		   case 1:
			   {
				 first(arrKxq,arrNcfpb);
				 break;
			   }
		   case 2:
			   {
				 worst(arrKxq,arrNcfpb);
				 break;
			   }
		   case 3:
			   {
			     best(arrKxq,arrNcfpb); 
				 break;
			   }
		   case 0:
			   {
				 flag=0;
				 break;
			   }
		   default:
			   {
				   cout<<"ѡ�����\n";
				   break;		   
			   }	
		}
	}
	//��ʾ���
	showResult(arrKxq,arrNcfpb);	

}


void first(kxq arrKxq[],NCFPB arrNcfpb[])
{
	 int i=0,j=0,sAddress=0,kLength=0,proLength=0;
     int pos=0;
     char ch,pName[20];   
     
    // cout<<"3:---��������ҵ��������ռ�Ĵ�С ����ڴ������\n";
    do
	{
		 cout<<"----------------���ܣ�ʵ��������Ӧ�㷨---------------\n";
		 cout<<"��������������ڴ�:��ҵ��Ϊ\n";	
		 new_line();
		 cin.getline(pName,20,'\n');
		 cout<<"����������ռ�Ĵ�С:\n";
		 cin>>proLength;    

		//----��ʼ����----------
		//3_2�Կ�������ַ���򣺴�С����
		sortFirst(arrKxq);

		for(i=0;i<kxqNum;i++)
		{
		   if( arrKxq[i].kxqLength>=proLength )
		   {
			  pos=i;
			  break;
		   }
		}

		//b��д�ڴ��ѷ�������  
		arrNcfpb[ncNum].sAddress=arrKxq[pos].sAddress;
		arrNcfpb[ncNum].ncLength=proLength;
		arrNcfpb[ncNum].pName=pName;
		++ncNum;

		//��  �޸Ŀ�������
		arrKxq[pos].sAddress=arrKxq[pos].sAddress+proLength; 		
		arrKxq[pos].kxqLength=arrKxq[pos].kxqLength-proLength;
		if(arrKxq[pos].kxqLength==0)   //���������ĳ���Ϊ0ʱ����0 ��ʾ��������
		{
		   arrKxq[pos].kxqFlag=0;   
		   //�Ѳ����õĿ�����ȥ��
		   for(i=pos;i<kxqNum-1;i++)
		   {
			  arrKxq[i]=arrKxq[i+1];
		   }
		   kxqNum=kxqNum-1;
		}
		else
		{
		   arrKxq[pos].kxqFlag=1;   
		} 
	 cout<<"�������� ���������㷨 �����ڴ�������������(yes/no)\n";
     cin>>ch;
     new_line();		
	 }while( (ch!='N') && (ch!='n'));
}

void worst(kxq arrKxq[],NCFPB arrNcfpb[])
{   
   int i=0,j=0,sAddress=0,kLength=0,proLength=0;   
   char ch, pName[20];   

     cout<<"----------------���ܣ�ʵ�����Ӧ�㷨---------------\n";

	 //(3)�����û�����
     do
	 {
		 cout<<"��������������ڴ�:��ҵ��Ϊ\n";	
		 new_line();
		 cin.getline(pName,20,'\n');
		 cout<<"����������ռ�Ĵ�С:\n";
		 cin>>proLength;    
     
	   //----��ʼ����----------
        //����������С���򣺴Ӵ�С(����������㷨��ǰ��),
        sortWorst(arrKxq);

		if( proLength>arrKxq[0].kxqLength )   // �����ڴ�>��0��������,���޷�����
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
        cout<<"�������� ��������㷨 �����ڴ�������������(yes/no)\n";
        cin>>ch;
		new_line();		
	 }while( (ch!='N') && (ch!='n'));
	 
}


void best(kxq arrKxq[],NCFPB arrNcfpb[])
{
    int i=0,j=0,sAddress=0,kLength=0,proLength=0;
    int pos=0;
    char ch,pName[20];   
     
    // cout<<"3:---��������ҵ��������ռ�Ĵ�С ����ڴ������\n";
    do
	{
		 cout<<"----------------���ܣ�ʵ����������㷨---------------\n";
		 cout<<"��������������ڴ�:��ҵ��Ϊ\n";	
		 new_line();
		 cin.getline(pName,20,'\n');
		 cout<<"����������ռ�Ĵ�С:\n";
		 cin>>proLength;    

		//---- ��ʼ���� ----------
		//�Կ������������򣺴�С����
		sortBest(arrKxq);

		for(i=0;i<kxqNum;i++)
		{
		   if( arrKxq[i].kxqLength>=proLength )
		   {
			  pos=i;
			  break;
		   }
		}

		//b��д�ڴ��ѷ�������  
		arrNcfpb[ncNum].sAddress=arrKxq[pos].sAddress;
		arrNcfpb[ncNum].ncLength=proLength;
		arrNcfpb[ncNum].pName=pName;
		++ncNum;

		//��  �޸Ŀ�������
		arrKxq[pos].sAddress=arrKxq[pos].sAddress+proLength; 		
		arrKxq[pos].kxqLength=arrKxq[pos].kxqLength-proLength;
		if(arrKxq[pos].kxqLength==0)   //���������ĳ���Ϊ0ʱ����0 ��ʾ��������
		{
		   arrKxq[pos].kxqFlag=0;   
		   //�Ѳ����õĿ�����ȥ��
		   for(i=pos;i<kxqNum-1;i++)
		   {
			  arrKxq[i]=arrKxq[i+1];
		   }
		   kxqNum=kxqNum-1;
		}
		else
		{
		   arrKxq[pos].kxqFlag=1;   
		} 
	 cout<<"�������� ��������㷨 �����ڴ�������������(yes/no)\n";
     cin>>ch;
     new_line();		
	 }while( (ch!='N') && (ch!='n'));

}


void sortFirst(kxq arr[])
{
   int i=0,j=0;
   kxq tem;
   for(i=0;i<kxqNum;i++)
   {	  
      for(j=i+1;j<kxqNum;j++)
	  {
	     if(arr[i].sAddress > arr[j].sAddress)  //���õ�ַ����
		 {   
			 tem=arr[i];
			 arr[i]=arr[j];
			 arr[j]=tem;		 
		 }	  
	  }  
   }
}

void sortWorst(kxq arr[])
{
   int i=0,j=0;
   kxq tem;
   for(i=0;i<kxqNum;i++)
   {	  
      for(j=i+1;j<kxqNum;j++)
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

void sortBest(kxq arr[])
{
   int i=0,j=0;
   kxq tem;
   for(i=0;i<kxqNum;i++)
   {	  
      for(j=i+1;j<kxqNum;j++)
	  {
	     if(arr[i].kxqLength > arr[j].kxqLength)
		 {   
			 tem=arr[i];
			 arr[i]=arr[j];
			 arr[j]=tem;		 
		 }	  
	  }  
   }
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

	//return kxqNum;   //��鲻֪�� kxqNum��Ҫ��1
    return kxqNum-1;  
}


void showResult(kxq arrKxq[],NCFPB nc[])
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
    cout<<"��ʼ��ַ   ����   ������(��־λ)\n";
    for(j=0;j<ncNum;j++)
	{
	    cout<<nc[j].sAddress<<"\t";
		cout<<nc[j].ncLength<<"\t";
		cout<<nc[j].pName<<"\n";
	}
}

void outKxq(kxq arrKxq[])
{
    cout<<"\n2:------------ϵͳ��ǰ������Ϊ:\n";
    cout<<"��ʼ��ַ\t����\t��־λ\n";
	for(int i=0;i<kxqNum;i++)
	{
	    cout<<arrKxq[i].sAddress<<"\t";
		cout<<arrKxq[i].kxqLength<<"\t";
		cout<<arrKxq[i].kxqFlag<<"\n";
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