/*2_2
6���ĺ�����Ŀ���
ģ�������Ӧ��������ҵ�����㷨
���룺��ҵ���ļ������д洢����һϵ��Ҫִ�е���ҵ��
ÿ����ҵ�������������
��ҵ�š���ҵ����ϵͳ��ʱ�䣨��һ������ʾ����10��10����ʾ��1010��������ִ��ʱ�䣨��λ�֣����ȼ���0����ߣ�
�����ÿո������������ʾ����
1 800 50
2 815 30
3 830 25
4 835 20
5 845 15
6 900 10
7 920 5
���е���ʱ��Ϊ���һ����ҵ����ϵͳ��ʱ�䣡
�����ҵ�ţ������ڴ��ʱ�䣡ÿ�����һ����ҵ��Ϣ

*/

#include <stdio.h>
#include <iostream> 
#include <iomanip> 
using namespace std;

const int arrNum=20;
const int infinity=100000;
typedef struct job{
   int jobNo;
   int arrivalTime;
   int runTime;
   int priority;  //��Ӧ�ȵ����ȼ���Ĭ��Ϊ0
   int finishFlag; //0:��ʾ�ȴ��� 1����������
}JobNode;

int readFile(JobNode JN[arrNum]);
void comXYB(JobNode JN[arrNum],int jbNum,int startTime);  //���� �ȴ� ��ҵ����Ӧ��
int  findSmallJob(JobNode JN[arrNum],int jbNum);  //��  �ȴ� ��Ӧ����С����ҵ��
void outJob(JobNode JN[arrNum],int jobNo,int startTime);
void new_line();

void main()
{
	int jbNum,startTime,runJob,k;
	int sHour,sMinute;

	JobNode JN[arrNum];
	cout<<"--ģ�������Ӧ��������ҵ�����㷨---\n";
    jbNum=readFile(JN);

    cout<<"\n���������Ӧ��������ҵ�����㷨����ҵ�ĵ������\n";
	cout<<"\n��ҵ��  �����ڴ��ʱ��  ����ʱ�� \n";
    
    startTime=JN[jbNum-1].arrivalTime;
	k=jbNum;
	while(k>0)
	{
	  
       comXYB(JN,jbNum,startTime);
       runJob=findSmallJob(JN,jbNum);
       //����������
       outJob(JN,runJob,startTime);
       //startTime=startTime+JN[runJob].runTime;
	   //Ϊ��һ����ҵ�Ŀ�ʼʱ�� ����: 8:50 ������30���ӣ� ���¸���ҵ�Ŀ�ʼʱ��Ϊ 9:20����920�� ��8+1��*100+20
       sHour=startTime/100;   
	   sMinute=startTime%100;
       startTime=(sHour+(sMinute+JN[runJob].runTime)/60)*100+ (sMinute+JN[runJob].runTime)%60;  //��60Ϊ���Ƽ��㣬����ʾʱΪ10����

	   --k;
	}    
}


int readFile(JobNode JN[arrNum])
{
    char fName[50];
	FILE *stream;
    int i=0;

    cout<<"\n���룺��ҵ���ļ������д洢����һϵ��Ҫִ�е���ҵ��ÿ����ҵ�������������\n";
    cout<<"\n��ҵ�š���ҵ����ϵͳ��ʱ�䣨��һ������ʾ����10��10����ʾ��1010��������ִ��ʱ�䣨��λ�֣����ȼ���0����ߣ�\n\n";
    cout<<"��������ҵ���ļ���\n";
   
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
	    fscanf(stream,"%d %d %d",&JN[i].jobNo,&JN[i].arrivalTime,&JN[i].runTime);
        JN[i].finishFlag=0; 
		JN[i].priority=0;

		++i;
       
	}    
    fclose(stream);
    return i-1;
}


void comXYB(JobNode JN[arrNum],int jbNum,int startTime)  //���� �ȴ��� ��ҵ����Ӧ��
{
   int sHour,sMinute,aHour,aMinute;
   for(int i=0;i<jbNum;i++)
   {
      if(JN[i].finishFlag==0)
      {
          sHour=startTime/60;     //��9:20 ��sHour ��9  sMinute��20
          sMinute=startTime%60; 
          aHour=JN[i].arrivalTime/60;
          aMinute=JN[i].arrivalTime%60;
          //��ʱ��ͳһΪ������������Ӧ�ȣ�����)          
	      JN[i].priority=( double( (sHour-aHour)*60+sMinute-aMinute+JN[i].runTime) )/JN[i].runTime;  //ע������
	  }
   }

}

int  findSmallJob(JobNode JN[arrNum],int jbNum)  //�� �ȴ��� ��Ӧ����С����ҵ��
{
   int min=infinity,pos;   //�ܴ��һ����
   for(int i=0;i<jbNum;i++)
   {
      if(JN[i].finishFlag==0 && min>JN[i].priority)
      {
           min=JN[i].priority;
		   pos=i;
	  }
   }
   return pos;
}

void outJob(JobNode JN[arrNum],int jobNo,int startTime)
{
  
   cout<<JN[jobNo].jobNo<<"  ";
   cout<<startTime<<"  ";
   cout<<JN[jobNo].runTime<<endl;
  
   JN[jobNo].finishFlag=1;
}

void new_line()
{
    char symbol;
    do
	{
	   cin.get(symbol);
	}while(symbol!='\n');
}