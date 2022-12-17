//����洢��������ҳ������㷨ȫʵ��

/*
���� ����洢��������ҳ�����

ҳ������㷨��Ҫ�У�FIFO���������ʹ�õ����㷨��LRU�����������õ����㷨��LFU��������㷨��OPT�� 

1�� ���룺
ҳ�����ļ������д洢����һϵ��ҳ��ţ�ҳ�����������ʾ���ÿո���Ϊ�ָ�����������ģ��������ҳ�档
������һ��ʾ�⣺
1 2 3 4 1 2 5 1 2 3 4 5
2�� ����Ҫ��
��������ʱ��������ʾ��������ҳ�����ļ����ļ�������������һ���ļ����󣬳��򽫶�����ļ��е��й����ݡ�
��ʼ��������������ҳ�򣬳�ʼʱ��Ϊ�ա�
���ݵڶ��λ����㷨�����ݽ��д���
3�� ���Ҫ��
ÿ����һ��ҳ�棨����ÿ����һ��ҳ��ţ����ж��Ƿ���ҳ����Ҫ�����������У��ѱ�������ҳ����������Ļ�ϣ�
��û�У������һ����*���š�
4�� �ļ���Լ��
�ύ��Դ�������֣�sourceXXX.c����sourceXXX.cpp��������������ȷ����
�����ļ����֣������û�ָ��
���У�XXXΪ�˺š�
5�� ����˵�������Խ�ʦ������׼����һ���ļ�����ʽΪ*.txt��������Ϊÿ���������ָ��һ��������Ϊ�����ļ�
������������Ӽ�������ָ���ļ����ļ����������鿴������������
6�� �ڶ��λ����㷨����FIFO�㷨�����¼򵥵��޸ģ������滻ʱ���ȼ������ҳ���R�����ʣ�λ�����Ϊ0��
��ô��ҳ�������类����ģ����ҽ���û�б����ʣ��������̱��滻�������RλΪ1�������Rλ�����޸�����װ��ʱ�䣬
ʹ������ձ�װ�����ҳ��һ����Ȼ������������滻������ҳ�档



  ҳ������㷨��Ҫ�У�FIFO���������ʹ�õ����㷨��LRU�����������õ����㷨��LFU��������㷨��OPT�� 
�⼸���㷨�ĵ��ȶ��п����ڿ����������� 
������һ���ͣ���һ����Բο��鱾251ҳ��ʵ��ָ���� 
��2001�꿼�⣺ 
Ҫ�� 

1��ʵ�������㷨�� FIFO���������ʹ�õ����㷨��LRU�����������õ����㷨��LFU�� 

2��ҳ�����д�ָ�����ı��ļ���TXT�ļ�����ȡ�� 

3������� 

��һ�У�ÿ����̭��ҳ��� 

�ڶ��У���ʾȱҳ���ܴ��� 


   ���������:FIFO���������ʹ�õ����㷨��LRU�����������õ����㷨��LFU�� �ڶ��λ����㷨

  */


#include<stdio.h>
#include<string.h>
#include<iostream.h>

const int MAXSIZE=1000;//�������ҳ����
const int MAXQUEUE=3;//����ҳ����

typedef struct node{
int ym;
int number;
}page;

page pages[MAXQUEUE]; //����ҳ���
int queue[MAXSIZE];
int t;
page z;

//��ʼ���ṹ����
void initial()
{
	int i;
	for(i=0;i<MAXQUEUE;i++)
	{
		pages[i].ym=-1;
		pages[i].number=0;
	}
	for(i=0;i<MAXSIZE;i++)
	{
		queue[i]=-1;
	}
	t=0;
}

//��ʼ��ҳ����
void init()
{
int i;

for(i=0;i<MAXQUEUE;i++){
  pages[i].ym=-1;
  pages[i].number=0;
}
}

//����ҳ����
int readData()
{
	FILE *fp;
	char fname[20];
	int i;

	cout<<"������ҳ�����ļ���:";
	cin>>fname;

	if((fp=fopen(fname,"r"))==NULL)
	{
		cout<<"����,�ļ��򲻿�,�����ļ���"<<endl;
		return 0;
	}
	else
	{
		while(!feof(fp))
		{
			fscanf(fp,"%d ",&queue[t]);
			t++;
		}
	}

	cout<<"�����ҳ����:";
	for(i=0;i<t;i++)
	{
		cout<<queue[i]<<"  ";
	}
	return 1;
}

//FIFO�����㷨

void  FIFO()
{
	int a=0;
	for( int i=0 ; i<MAXQUEUE ; i++ )
	{
		pages[i].ym=queue[i];
		cout<<queue[i]<<"  ";
		a++;
	}
	for( i=MAXQUEUE ; i<t ;i++)
	{	int p=0;
		for( int j=0 ; (j<MAXQUEUE)&&(p==0) ; j++ )
		{
			if(queue[i]==pages[j].ym)
			{
				p=1;
			}
		}
		if(p==0)
		{
			cout<<queue[i]<<"   ";
			a++;
			for( int k=0 ; k<MAXQUEUE-1 ;k++)
			{
				pages[k].ym=pages[k+1].ym;
			}
			pages[k].ym=queue[i];
		}
	}
cout<<endl<<"��ȱҳ��:"<<a<<endl;

}
//�������ʹ�õ����㷨��LRU��

void  LRU()
{
	int a=0;
	for( int i=0 ; i<MAXQUEUE ; i++ )
	{
		pages[i].ym=queue[i];
		cout<<queue[i]<<"  ";
		a++;
	}
	for( i=MAXQUEUE ; i<t ;i++)
	{	int p=0;
		for( int j=0 ; (j<MAXQUEUE)&&(p==0) ; j++ )
		{
			if(queue[i]==pages[j].ym)
			{
				p=1;
				for( ; j< MAXQUEUE-1 ; j++ )
				{
					pages[j].ym=pages[j+1].ym;
				}
				pages[j].ym=queue[i];
			}
		}
		if(p==0)
		{
			cout<<queue[i]<<"   ";
			a++;
			for( int k=0 ; k<MAXQUEUE-1 ;k++)
			{
				pages[k].ym=pages[k+1].ym;
			}
			pages[k].ym=queue[i];
		}
	}
cout<<endl<<"��ȱҳ��:"<<a<<endl;

} 
//�������õ����㷨(LFU)

void  LFU()
{
	int a=0;
	for( int i=0 ; i<MAXQUEUE ; i++ )
	{
		pages[i].ym=queue[i];
		cout<<queue[i]<<"  ";
		a++;
	}
	for( i=MAXQUEUE ; i<t ; i++)
	{	int p=0;
		for( int j=0 ; (j<MAXQUEUE)&&(p==0) ; j++ )
		{
			if(queue[i]==pages[j].ym)
			{
				p=1;
				pages[j].number++;
			}
		}
		if(p==0)
		{
			cout<<queue[i]<<"   ";
			a++;
			for( int q=0 ; q<MAXQUEUE-1 ;q++)
				for(int j=0 ; j<MAXQUEUE-q-1 ; j++ )
					if(pages[j].number>pages[j+1].number)
					{
						/*z.ym=pages[j].ym;
						z.number=pages[j].number;
						pages[j].ym=pages[j+1].ym;
						pages[j].number=pages[j+1].number;
						pages[j+1].ym=z.ym;
						pages[j+1].number=z.number*/			
						z=pages[j];
						pages[j]=pages[j+1];
						pages[j+1]=z;
					}
			for( int k=0 ; k<MAXQUEUE-1 ; k++)
			{
				pages[k].ym=pages[k+1].ym;
				pages[k].number=pages[k+1].number;
			}
			pages[k].ym=queue[i];
			pages[k].number=0;
		}
	}
cout<<endl<<"��ȱҳ��:"<<a<<endl;

} 

//�ڶ��λ����㷨

void second()
{	
	int a=0;
	for( int i=0 ; i<MAXQUEUE ; i++ )
	{
		pages[i].ym=queue[i];
		cout<<queue[i]<<"  ";
		a++;
	}
	for( i=MAXQUEUE ; i<t ;i++)
	{	int f=0;
		int p=0;
		for( int j=0 ; (j<MAXQUEUE)&&(p==0) ; j++ )
		{
			if(queue[i]==pages[j].ym)
			{
				p=1;
				pages[j].number=1;
			}
		}
		if(p==0)
		{
			cout<<queue[i]<<"   ";
			a++;
			for(int k=0 ; k<MAXQUEUE ;k++)
			{
				if(pages[k].number==0)
				{
					f=1;
					for( ; k<MAXQUEUE-1 ;k++)
					{
						pages[k].ym=pages[k+1].ym;
						pages[k].number=pages[k+1].number;
					}
					
				}
			}
			if(f==0)
			{
				for( k=0 ; k<MAXQUEUE ; k++)
				{
					pages[k].number=0;
				}
				for( int k=0 ; k<MAXQUEUE-1 ;k++)
				{
					pages[k].ym=pages[k+1].ym;
					pages[k].number=pages[k+1].number;
				}
			}
			k--;
			pages[k].ym=queue[i];
			pages[k].number=0;
		}
	}
cout<<endl<<"��ȱҳ��:"<<a<<endl;

}

void main()
{
initial();
int c,m=1;

if(readData()){
while(m)
{
cout<<endl<<"--------------------------------------"<<endl;
cout<<"��ѡ��Ҫ���㷨��"<<endl;
cout<<"1�������ȷ���  2��LRU  3��LFU  4���ڶ���ҳ�����  5���˳�"<<endl;
cout<<"--------------------------------------"<<endl;
cin>>c;
	switch(c)
	{
	case 1:
		init();
		FIFO();
		break;
	case 2:
		init();
		LRU();
		break;
	case 3:
		init();
		LFU();
		break;
	case 4:
		init();
		second();
		break;
	case 5:
		m=0;
		break;
	default:
		cout<<"ѡ�����"<<endl;
	}
	}
}
}


