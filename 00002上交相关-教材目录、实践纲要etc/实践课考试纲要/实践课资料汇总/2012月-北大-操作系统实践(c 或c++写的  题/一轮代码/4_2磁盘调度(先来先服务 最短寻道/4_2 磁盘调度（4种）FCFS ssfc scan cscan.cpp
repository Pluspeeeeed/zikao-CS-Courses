/*

2008.6.21  ģ������������ȹ��̣�
20����ͷ��0-19�� ����200�����棻
�������ڣ�0-199��
�������У�
��1������ʦ�������ļ������ļ��д��д��̷������������š�
��2�������������ȷ�����̵����㷨������Ŀ����ʾ���Ƚ���������̷�������Ĵŵ����Լ���ͷ�ƶ����ܴŵ�����
��3�������赱ǰ��ͷ��λ����57�ŵ��ϰ������Ѱ��ʱ�����ȴŵ������㷨������Ļ����ʾ���Ƚ���Լ���ͷ�ƶ����ܴŵ�����

����: fcfs, ssTf(���Ѱ��),scan(���ݵ���),cscan(ѭ�������㷨)
*/
#include <iostream>               
#include <valarray> 
using namespace std;

#define maxNum 20
#define inifity 65500

typedef struct ciPanXuLie
{
   int cpNum;
   int flag;  //0��ʾδ���ʣ�1��ʾ�ѷ���
}cpxl;

int readFile(cpxl arrCpxl[]);  //��������Ĵ�������
void outCpxl(cpxl arrCpxl[],int arrNum);
void new_line();  //ȥ��û�õ��ַ�

void firstCp(cpxl arrCpxl[],int arrNum); //�����ȷ���

void shortCp(cpxl arrCpxl[],int arrNum); //���Ѱ��ʱ������
int smallPos(cpxl arrCpxl[],int arrJuli[],int arrNum);  //���뵱ǰ��ͷ����Ĵŵ����������±�

void scanCp(cpxl arrCpxl[],int arrNum);  //���ݵ���
void smallToBig(cpxl arrCpxl[],int arrNum);

void cScanCp(cpxl arrCpxl[],int arrNum); //ѭ�������㷨
 
void main()
{
    int flag=1,arrNum,selNum;	
	cpxl arrCpxl[maxNum];

    cout<<"���ܣ�ʵ�ִ��̵���(�����ȷ��� ���Ѱ�� ���ݵ��� ѭ�������㷨)\n\n";
   
	//���ļ�
    arrNum=readFile(arrCpxl);
    outCpxl(arrCpxl,arrNum);

	while(flag!=0)
	{
		cout<<"\n\n���̵��ȣ���ѡ��; 1:�����ȷ���; 2:���Ѱ��ʱ������ 3:���ݵ��� 4:ѭ�������㷨; 0:�˳�ϵͳ \n";
	    cin>>selNum;
		switch(selNum)
		{
		   case 1:
			   {
				 firstCp(arrCpxl,arrNum);
				 break;
			   }
		   case 2:
			   {
				 shortCp(arrCpxl,arrNum);
				 break;
			   }
		   case 3:
			   {
			      scanCp(arrCpxl,arrNum);
			   }
		   case 4:
			   {
			      cScanCp(arrCpxl,arrNum);
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
}


int readFile(cpxl arrCpxl[])  //��������Ĵ�������
{
    char fName[50];
	FILE *stream;
	int  kxqNum=0;

    cout<<"������ ���д��̷������������� ���ļ���";
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
	    fscanf(stream,"%d",&arrCpxl[kxqNum].cpNum);
        arrCpxl[kxqNum].flag=0;  
        //kxqNum++;
        kxqNum=kxqNum+1;
	}    
    fclose(stream);	
    return kxqNum;  
}

void outCpxl(cpxl arrCpxl[],int arrNum)
{
   cout<<"\n�ļ��еĴ�������Ϊ:\n";
   for(int i=0;i<arrNum;i++)
   {
      cout<<arrCpxl[i].cpNum<<"\t";   
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


void firstCp(cpxl arrCpxl[],int arrNum)  //�����ȷ���
{
	int currNum,sum=0;
    cout<<"�������ͷ���ڵĴ�ͷ��\n";
    cin>>currNum;

    cout<<"\n���������ȷ�����̵����㷨,���̷�������Ĵŵ���Ϊ:\n";
    for(int i=0;i<arrNum;i++)
	{
	    cout<<arrCpxl[i].cpNum<<"\t";
	}
	//�����ܴŵ���
    for(i=0;i<arrNum;i++)
	{
	   if(i==0)
	   {
	       sum+=abs(arrCpxl[i].cpNum-currNum);
	   }
	   else
	   {
	       sum+=abs(arrCpxl[i].cpNum-arrCpxl[i-1].cpNum);
	   }
	}
     cout<<"\n ��ͷ�ƶ����ܴŵ���Ϊ:"<<sum<<endl;
}


void shortCp(cpxl arrCpxl[],int arrNum)  //���Ѱ��ʱ������
{
    
	int juli[maxNum],pos=0,sum=0;
	
    int currNum=57;  //��ʼʱ��ǰ��ͷ��
    cout<<"\n��ʼʱ��ǰ��ͷ��Ϊ"<<currNum<<endl; 
	cout<<"\n�������Ѱ��ʱ�����ȴŵ������㷨,���̷�������Ĵŵ���Ϊ:";

    for(int j=1;j<=arrNum;j++)     //ÿ����һ���뵱ǰ��ͷ���Ĵŵ�����
	{
		for(int i=0; i<arrNum ;i++)    
		{		   
		   juli[i]=abs(arrCpxl[i].cpNum-currNum);		   
		} 

		pos = smallPos(arrCpxl,juli,arrNum);
		
		cout<<arrCpxl[pos].cpNum<<"\t";
		sum+=juli[pos];       
	     
		arrCpxl[pos].flag=1;          //����˴ŵ��ѷ��ʹ�
        currNum=arrCpxl[pos].cpNum;   //�޸ĵ�ǰ�ŵ�
    }
    cout<<"\n ��ͷ�ƶ����ܴŵ���Ϊ:"<<sum<<endl;

}


int smallPos(cpxl arrCpxl[],int arrJuli[],int arrNum)
{
    int temp=0,pos;

	//Ϊtemp����ֵ
	for(int j=0;j<arrNum;j++)
	{
	    if(arrCpxl[j].flag==0)
		{
		    temp=arrCpxl[j].cpNum;
			pos=j;
			break;
		}
	}

    //��δ���ʹ��Ĵŵ��� �� ������С��
	for(int i=0;i<arrNum;i++)
	{
	   if(arrCpxl[i].flag==0 && temp>arrJuli[i] ) 
	   {
	       temp=arrJuli[i];
		   pos=i;
	   }
	}
	return pos;
}

//���ݵ���
void scanCp(cpxl arrCpxl[],int arrNum)  
{
   int i,j,sum=0;
   int currNum;    //��ʼʱ��ͷ�� 
   int adj;  //������һ�η��ʹ��Ĵŵ�
   
   cout<<"\n�����뵱ǰ��ͷ��(��100)��"<<endl; 
   cin>>currNum; 

   smallToBig(arrCpxl,arrNum);
   cout<<"\n���յ��ݵ����㷨,���̷�������Ĵŵ���Ϊ:";
   for(i=0;i<arrNum;i++)
   {
      if(arrCpxl[i].cpNum>currNum)
	  {
	     break;
	  }
   }

   sum=0;
   adj=currNum;
   for(j=i;j<arrNum;j++)
   {
      cout<<arrCpxl[j].cpNum<<"  ";
	  sum+=abs(arrCpxl[j].cpNum-adj);
	  adj=arrCpxl[j].cpNum;
   }
   for(j=i-1;j>=0;j--)
   {
      cout<<arrCpxl[j].cpNum<<"  ";
	  sum+=abs(arrCpxl[j].cpNum-adj);
	  adj=arrCpxl[j].cpNum;
   }
   cout<<"\n���յ��ݵ����㷨,�ܵĴŵ��ƶ�����Ϊ:"<<sum<<endl;
 
}

void smallToBig(cpxl arrCpxl[],int arrNum)
{
	int temp;
    for(int i=0;i<arrNum;i++)
	{
	   for(int j=i+1;j<arrNum;j++)
	   {
	       if(arrCpxl[i].cpNum>arrCpxl[j].cpNum)
		   {
			   temp=arrCpxl[i].cpNum;
		       arrCpxl[i].cpNum=arrCpxl[j].cpNum;
               arrCpxl[j].cpNum=temp;
		   }
	   }
	}	
}

//ѭ�������㷨:�Ե��ݵ����㷨��һ��
void cScanCp(cpxl arrCpxl[],int arrNum) 
{
   int i,j,sum=0;
   int currNum;    //��ʼʱ��ͷ�� 
   int adj;  //������һ�η��ʹ��Ĵŵ�
   
   cout<<"\n�����뵱ǰ��ͷ��(��100)��"<<endl; 
   cin>>currNum; 

   smallToBig(arrCpxl,arrNum);
   cout<<"\n����ѭ�������㷨,���̷�������Ĵŵ���Ϊ:";
   for(i=0;i<arrNum;i++)
   {
      if(arrCpxl[i].cpNum>currNum)
	  {
	     break;
	  }
   }

   sum=0;
   adj=currNum;
   for(j=i;j<arrNum;j++)
   {
      cout<<arrCpxl[j].cpNum<<"  ";
	  sum+=abs(arrCpxl[j].cpNum-adj);
	  adj=arrCpxl[j].cpNum;
   }
   for(j=0;j<=(i-1);j++)   //�޸ĵ�
   {
      cout<<arrCpxl[j].cpNum<<"  ";
	  sum+=abs(arrCpxl[j].cpNum-adj);
	  adj=arrCpxl[j].cpNum;
   }
   cout<<"\n���� ѭ�������㷨,�ܵĴŵ��ƶ�����Ϊ:"<<sum<<endl;
}