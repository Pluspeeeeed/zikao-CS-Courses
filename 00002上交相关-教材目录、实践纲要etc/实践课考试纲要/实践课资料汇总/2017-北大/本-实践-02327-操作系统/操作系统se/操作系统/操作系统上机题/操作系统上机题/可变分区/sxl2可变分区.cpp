//�ɱ�����洢�������е��ڴ�����㷨ȫʵ��

/*�ɱ�����洢�������е��ڴ����

  �ɱ���������㷨��:������Ӧ�����㷨,������Ӧ�����㷨,���Ӧ�㷨
�û�����ڴ�ռ�����룻ϵͳ���������ߵ�Ҫ�󣬰���һ���ķ�����Է����ڴ�ռ��ʹ��������ҳ���
��������Ŀ��������ָ������ߣ�������ִ����ϻ������黹�ڴ���Դʱ��ϵͳҪ�ջ�����ռ�õ��ڴ�ռ�
�����黹�Ĳ����ڴ�ռ䡣

1����������ʱ���Ƚ������룺�����������ļ������������У�ÿ���������������ʼ��ַ�����ȣ���Ϊ
�����������������Զ��Ÿ�����

2������������������Ļ����ʾ��������������ݣ����������м�¼���ڴ��пɹ�����Ŀ�������ʼַ��
���ȣ��ñ�־λָ���÷����Ƿ���δ����Ŀ�������

3�����û���������û���ʾ����һ���ڴ����룬��ʽΪ����ҵ��������ռ�Ĵ�С��

4����������������㷨ѡ��һ�����������ָ���䣬�޸���Ӧ�����ݽṹ��������������д��
���ѷ���������ʼ��ַ�����ȡ���־λ�������б�־λ��һ��������ָ�������������ĸ���ҵ��

5���ظ�3��4��ֱ������Ϊ�����ַ���0����

6������Ļ����ʾ����µĿ���������ѷ�����������ݡ�

���������:FIFO,������Ӧ�����㷨,���Ӧ�㷨

*/

#include<stdio.h>
#include<iostream.h>
#include<string.h>
#include<iomanip.h>

const int MAX=100;//���������¼��

typedef struct node{
int start;
int length;
char jobname[20];
}job;

job frees[MAX];//�����������
int freet;

job occupys[MAX];//�����ѷ�������
int occupyt;

job copy[MAX];
job s;
//��ʼ������
void initial()
{
int i;

for(i=0;i<MAX;i++){
  frees[i].start=-1;
  frees[i].length=0;
  strcpy(frees[i].jobname,"free");

  occupys[i].start=-1;
  occupys[i].length=0;
  strcpy(occupys[i].jobname,"");
}
freet=0;
occupyt=0;
}

void init()
{
	for( int i=0 ; i<freet ;i++)
	{
		copy[i].start=frees[i].start;
		copy[i].length=frees[i].length;
		strcpy(copy[i].jobname,frees[i].jobname);
	}
}
//�����ݺ���
int readData()
{
FILE *fp;
char fname[20];

cout<<"�������ʼ���б��ļ���:";
cin>>fname;

if((fp=fopen(fname,"r"))==NULL){
  cout<<"����,�ļ��򲻿�,�����ļ���"<<endl;
}
else{
  while(!feof(fp))
  {
   fscanf(fp,"%d,%d",&frees[freet].start,&frees[freet].length);
   freet++;
  }
	freet--;
  return 1;
	}
return 0;
}

//FIFO
void sortaddress()
{
  int i,j;
  for(i=0;i<freet;i++)
	{
		for(j=0;j<freet-i-1;j++)
		{
			if(copy[j].start>copy[j+1].start)
			{
				s=copy[j];
				copy[j]=copy[j+1];
				copy[j+1]=s;
			}
		}
		
		
	}
}
//������Ӧ�����㷨

void sortadlength()
{
  int i,j;
  for(i=0;i<freet;i++)
	{
		for(j=0;j<freet-i-1;j++)
		{
			if(copy[j].length>copy[j+1].length)
			{
				s=copy[j];
				copy[j]=copy[j+1];
				copy[j+1]=s;
	
			}
		}
		
		
	}
}
//���Ӧ�㷨
void sortadmax()
{
  int i,j;
  for(i=0;i<freet;i++)
	{
		for(j=0;j<freet-i-1;j++)
		{
			if(copy[j].length<copy[j+1].length)
			{
				s=copy[j];
				copy[j]=copy[j+1];
				copy[j+1]=s;
	
			}
		}
		
		
	}
}
//��ʾ����
void view()
{
	int i;
	cout<<endl<<"----------------------------------------------------------"<<endl;
	cout<<"��ǰ���б�:"<<endl;
	cout<<"��ʼ��ַ    ����      ״̬"<<endl;
	for(i=0;i<freet;i++)
	{
		cout<<"  "<<copy[i].start<<"          "<<copy[i].length<<"       "<<copy[i].jobname<<endl;
	}

	cout<<endl<<"----------------------------------------------------------"<<endl;
	cout<<"��ǰ�ѷ����:"<<endl;
	cout<<"��ʼ��ַ    ����   ռ����ҵ��"<<endl;
	for(i=0;i<occupyt;i++)
	{
		cout<<"  "<<occupys[i].start<<"          "<<occupys[i].length<<"         "<<occupys[i].jobname<<endl;
	}
}

//�㷨
void suanfa()
{
  char jobname[20];
  int joblength;
  cout<<"�������������ڴ�ռ����ҵ��";
  cin>>jobname;
  cout<<"�������������ڴ�ռ��С:";
  cin>>joblength;
  int flag=0;
  for(int i=0;i<freet&&flag==0;i++)
  {
	if(copy[i].length>=joblength)
	{
		flag=1;
	}
  }
	if(flag==0)
	{
		cout<<endl<<"��ǰû�������������볤�ȵĿ����ڴ�,���Ժ�����"<<endl;
	}
    else
	{
		int t=0;
        i--;
		occupys[occupyt].start=copy[i].start;
		strcpy(occupys[occupyt].jobname,jobname);
		occupys[occupyt].length=joblength;
		occupyt++;
		if(copy[i].length!=joblength)
		{
			copy[i].start+=joblength;
			copy[i].length-=joblength;
		}
		else
		{
			for(int j=i;j<freet-1;j++)
			{
				copy[j]=copy[j+1];
			}
			freet--;
			cout<<"�ڴ�ռ�ɹ�"<<endl;
		 }
	}
}


//������ҵ   
void finished()
{   int start,length,f=0;
	char jobname[20];
	cout<<"������Ҫ��������ҵ��:";
	cin>>jobname;
	int flag=-1;
	for( int i=0;i<occupyt;i++)
	{
		if(!strcmp(occupys[i].jobname,jobname))
		{
			flag=i;
			start=occupys[i].start;
			length=occupys[i].length;
		}
	}
	if(flag==-1)
	{
		cout<<"û�������ҵ��"<<endl;
	}
	else
	{
		for( i=0; (i<freet)&&(f==0); i++)
		{
			if((copy[i].start+copy[i].length==start)&&(copy[i+1].start==start+length)&&((i+1) < freet ))
			{
				copy[i].length+=(length+copy[i+1].length);
				i++;
				for( ; i<freet-1;i++)
				{
					copy[i]=copy[i+1];
				}
				freet--;
				f=1;
			}
			else if(copy[i].start+copy[i].length==start)
			{
				copy[i].length+=length;
				f=1;
			}
			else if((copy[i].start==start+length))
			{
				copy[i].start=start;
				copy[i].length+=length;
				f=1;
			}
			
		}
		if(i>=freet)
		{
			copy[freet].start=start;
			copy[freet].length=length;
			freet++;
		}
  //������б�
		/*for(i=0;i<freet;i++)
		{
			if((copy[i].start+copy[i].length)==start)
			{
				if( ( (i+1) < freet )&&(copy[i+1].start==start+length))
				{
					frees[i].length=frees[i].length+frees[i+1].length+length;
					for(int j=i+1;j<freet;j++)
					{
						copy[j]=copy[j+1];
					}
					freet--;
					p=1;
				}
				else
				{
				copy[i].length+=length;
				 p=1;
				}
			}
			if(copy[i].start==(start+length))
			{
				copy[i].start=start;
				copy[i].length+=length;
				p=1;
			}
			}

		if(p==0)
		{
			copy[freet].start=start;
			copy[freet].length=length;
			freet++;
		}*/



  //ɾ��������еĸ���ҵ

		for(i=flag;i<occupyt-1;i++)
		{
			occupys[i]=occupys[i+1];
		}
			occupyt--;
	}
}

void main()
{
	int flag=1;
 int chioce=0;
 initial();
 flag=readData();
init();
 while(flag==1){
  cout<<endl<<endl<<"========================================================="<<endl;
  cout<<"              �ɱ�����洢����ģ��ϵͳ"<<endl;
  cout<<"========================================================="<<endl;
  cout<<"   1.����ռ�   2.������ҵ   3.��ʾ���б�ͷ����  0.�˳�"<<endl;
  cout<<"��ѡ��:";
  cin>>chioce;
  switch(chioce){
  case 1:
	  {
    cout<<endl<<endl<<"========================================"<<endl;
	cout<<"��ѡ��һ���㷨"<<endl;
	cout<<"   1.�����ȷ���   2.�����㷨   3.��㷨  0.�˳�"<<endl;
	cout<<"��ѡ��:";
	int i;
	cin>>i;
    switch(i)
	{
    case 1:
       sortaddress();
		suanfa();
		break;
	case 2:
		sortadlength();
		suanfa();
		break;
    case 3:
        sortadmax();
        suanfa();
		break;
    case 0:
		flag=0;
		break;
	default:
		cout<<"ѡ�����!���������"<<endl;
	}
	  }
   break;
  case 2:
   finished();
   break;
  case 3:
   view();
   break;
  case 0:
   flag=0;
   break;
  default:
   cout<<"ѡ�����!���������"<<endl;
  }
}


}

