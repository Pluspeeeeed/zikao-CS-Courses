/*
��2002���
�ڴ汻���ֳ�2048�飨ҳ������32λ�ֳ����ִ��λʾͼ��Ϊ0��λ��ʾ�ÿ���δ���䣬Ϊ1��λ��ʾ�ÿ��ѷ���
ʵϰ��飺 
1�����г����ɼ���ʦ�����ļ��������ļ��д����ڴ�Ŀǰ״����λʾͼ�����ݣ�0��1���ļ�����������Ӧ����ʾ�������Ѻã��� 
2���������Ƶĳ���Ӧ�������ݣ��������Ӧ�����ݽṹ�С� 
3����ʾ�Ѻõ��û����棬�ɼ���ʦ�����ڴ����루�ܿ������� 
4�����������λʾͼ״̬��Ϊ�û������ڴ棬������ҳ�� 
5�����λʾͼ��ҳ��

 �����ļ�: ֻ���main�����е�  writeFile();  ǰ //ȥ������  
 
�򵥵Ĳ����ļ�1:4_3.txt;  (����޸Ĵ��� const int row=3��const int col=4;  

*/
#include <stdlib.h>

#include <iostream>     

using namespace std;

/*const int row=64;   //��( 2048/32=64; ���Կ��� [64][32]�Ķ�ά�����¼2048���ڴ� ��ʹ�����)
const int col=32; 
//const int ncMax=20; */

const int row=3;   
const int col=4;

void readFile(int arr[row][col]); 
void outData(int arr[row][col]);
void new_line();  //ȥ��û�õ��ַ�

void writeFile();  //���ɲ�������(�빤���ļ���ͬһĿ¼��)

 
void main()
{
	int arr[row][col],ncNum,k=0,kxqTotalNum=0;	
	int b,page=0;       //Ϊ�����ڴ������̿��,ҳ��
	int i,j;

    cout<<"\n4_3�ļ��Ĵ洢����:λʾͼ��ʹ�� \n\n"; 

	// writeFile();  // �����ɲ�������4_3data.txt�ļ�

    readFile(arr);
	outData(arr);

    cout<<"\n���� �����ڴ����루�ܿ����� \n";
    cin>>ncNum;

	
	//
    for(i=0;i<row;i++)
	{
	   for(j=0;j<col;j++)
	   {
	       if(arr[i][j]==0)
		   {
		      ++kxqTotalNum;
		   }
	   }
	}
	if(ncNum>kxqTotalNum)
	{
	   cout<<"\n��ǰû���㹻���ڴ�飬�޷���������ʧ��\n";
	}
	else
	{
		//��ҳ�����޸�λʾͼ
		cout<<"\nҳ��Ϊ��\n�߼�ҳ�� ������\n";
		for(i=0;i<row;i++)
		{
		  for(j=0;j<col;j++)
		  {
			 if(ncNum>0 && arr[i][j]==0 )
			 {
				b=i*col+j;   //������̿�� 
				cout<<page<<"    "<<b<<"  \n";
				++page;
				arr[i][j]=1;  //�޸�λʾͼ
                
				--ncNum;			
			 }
		  }
		}
    
		outData(arr);		
	}
}


void readFile(int arr[row][col])  
{
    char fName[50];
	FILE *stream;
	int  num,i,j;

    cout<<"�������ļ���(������ǰ�ڴ�ʹ�������λʾͼ������:0 δʹ��;1 �ѷ��䣩 \n"; 
	cin.getline(fName,50,'\n');
	stream  = fopen( fName, "r" ); //���ļ�
	while(stream==NULL)
    {
       cout<<"�ļ�����·�����������������ļ���\n";
	   //new_line();
	   cin.getline(fName,50,'\n');
       stream  = fopen( fName, "r" );
	}
    
    num=0;  //��ʾ�����һ������
	while(!feof(stream))
	{
	   i=num/col;   //�������ڶ�ά������ĸ�λ��
	   j=num%col; 
	   fscanf(stream,"%d",&arr[i][j]);
	   ++num;       
	}   
	
    fclose(stream);	
   
}

void outData(int arr[row][col])
{
   cout<<"\nλʾͼΪ:\n";
   for(int i=0;i<row;i++)
   {
	  for(int j=0;j<col;j++)
	  {
         cout<<arr[i][j]<<"\t";  
	  }
	  cout<<"\n";
   }
}


void new_line()   //ȥ��û���ַ�
{
    char symbol;
    do
	{
	   cin.get(symbol);
	}while(symbol!='\n');
}

void writeFile()
{
    FILE *fStream;

	fStream=fopen("4_2data.txt","w+"); 
    
	if(fStream==NULL)
	{
	   cout<<"���ļ�ʧ��"<<endl;
	   exit(1);
	}

	for(int i=0;i<row;i++)    //�ҵĲ�������Ϊ:����0 2 4 ���У��ĵ�2,3��ֵΪ0������1 3 5 ���У��ĵ�63 64��ֵΪ0��������Ϊ1
	{
	   for(int j=0;j<col;j++)
	   {
	       if(i%2==0 && (j==2 || j==3))
		   {
		      fprintf(fStream,"%d  ",0);
		   }
		   else if(i%2 !=0 && (j==62 ||j==63))
		   {
		      fprintf(fStream,"%d  ",0);
		   }
		   else
		   {
		      fprintf(fStream,"%d  ",1);
		   }
	   }
	   

	}

	fclose(fStream);
}

