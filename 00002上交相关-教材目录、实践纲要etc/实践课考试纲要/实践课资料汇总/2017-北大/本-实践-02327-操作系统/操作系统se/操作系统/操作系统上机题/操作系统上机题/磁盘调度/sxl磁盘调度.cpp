//���̵����㷨

/*

���̵����㷨 
Ҫ�� 
1��ʵ�������㷨��
1�������ȷ��� 
2�����Ѱ�����ȣ���ʦ�����ǰ��ͷ��λ�ã� 
3�������㷨 
2���ŵ�����˳���ָ�����ı��ļ���TXT�ļ�����ȡ�� 
3������� 
��һ�У��ŵ��ķ���˳�� 
�ڶ��У���ʾ�ƶ��ܵ��� 
���������:FIFO�����Ѱ�����ȵ����㷨�������㷨
*/

#include<stdio.h>
#include<iostream.h>
#include<string.h>
#include<math.h>

const int MAX=200;  //������������

//�ṹ�嶨��
typedef struct node{
int texe;
int t ;
}qu;

qu queue[MAX],copy[MAX];
int q=0,p=0;

int start;  //���忪ʼʱ��ͷ����λ��

//��ʼ������
void initial()
{
 	for(int i=0;i<MAX;i++)
 	{
  		queue[i].texe=-1;
  		queue[i].t=0;
	}

}
void init()
{for(int i=0;i<q;i++)
{
	copy[i]=queue[i];

}
p=q;
}
//����ŵ�����
int readData()
{
FILE *fp;
char fname[20];
int temp;
cout<<"������ŵ������ļ���:";
cin>>fname;

if((fp=fopen(fname,"r"))==NULL){
  cout<<"����,�ļ��򲻿�,�����ļ���"<<endl;
  return 0;
}
else{
  while(!feof(fp)){
   fscanf(fp,"%d ",&temp);
   queue[q].texe=temp;
   q++;
  }
  cout<<endl<<"---------------------------------------------"<<endl;
  cout<<"������Ĵŵ�����:";
  for(int i=0;i<q;i++){
   cout<<queue[i].texe<<"  ";
  }
  cout<<endl<<"������Ϊ:"<<q<<endl;
}
return 1;
}

//FIFO�㷨
void FIFO()
{
int i;
int total=0;
int current;

cout<<endl<<"---------------------------------------------"<<endl;
cout<<"FIFO�㷨�ķ��ʴŵ���˳����:";

current=start;
for(i=0;i<q;i++){
  cout<<queue[i].texe<<"  ";
  total+=abs(queue[i].texe-current);
  current=queue[i].texe;
}
cout<<endl<<"��ͷ�ƹ���������:"<<total;
}
//���Ѱ�����ȵ����㷨
void shortest()
{
	int total=0;
	qu n;
	int m;
	int current=start;
	for(int i=0;i<q;i++)
	{
		for(int j=0;j<p;j++)
		{
			copy[j].t=abs(copy[j].texe-current);
		}
		n=copy[0];
		m=0;
		for(int k=0;k<p-1;k++)
		{
			if(n.t>copy[k+1].t)
			{
				n=copy[k+1];
				m=k+1;
			}
		}
		cout<<n.texe<<"  ";
		total+=n.t;
		current=n.texe;;
		for(j=m;j<p-1;j++)
		{
			copy[j]=copy[j+1];
		}
		p--;
	}
	

cout<<endl<<"��ͷ�ƹ���������:"<<total;
}

//�����㷨
void elevator()
{
	int total=0;
	int current=start;
	int f=0;
	qu s;
	cout<<endl<<"---------------------------------------------"<<endl;
	cout<<"���ݵ����㷨"<<endl;
	for(int i=0;i<p;i++)
		for(int j=0;j<p-i-1;j++)
		{
			if(copy[j].texe>copy[j+1].texe)
			{
				s=copy[j];
				copy[j]=copy[j+1];
				copy[j+1]=s;
			}
		}
		

	for(i=0;(i<p)&&(f==0);i++)
	{
		if(copy[i].texe>=current)
		{
			f=1;
		}
	}
	i--;
	//��ͷ��ʼ����
	cout<<"��ͷ��ʼ����ķ��ʴŵ���˳����:";
	int k=i;
	for(i;i<p;i++)
	{
		cout<<" "<<copy[i].texe<<"  ";
		total+=abs(copy[i].texe-current);
		current=copy[i].texe;
	}
	i=k;
	i--;
	for(i;i>=0;i--)
	{
		cout<<" "<<copy[i].texe<<"  ";
		total+=abs(copy[i].texe-current);
		current=copy[i].texe;
	}
cout<<endl<<"��ͷ�ƹ���������:"<<total<<endl;

	//��ͷ��ʼ����
	total=0;
	cout<<"��ͷ��ʼ����ķ��ʴŵ���˳����:";
	i=k;
	i--;
	for(i;i>=0;i--)
	{
		cout<<" "<<copy[i].texe<<"  ";
		total+=abs(copy[i].texe-current);
		current=copy[i].texe;
	}
	i=k;
	for(i;i<p;i++)
	{
		cout<<" "<<copy[i].texe<<"  ";
		total+=abs(copy[i].texe-current);
		current=copy[i].texe;
	}
	
cout<<endl<<"��ͷ�ƹ���������:"<<total<<endl;

/*int i,j,p,flag;
int total=0;
int current;

cout<<endl<<"---------------------------------------------"<<endl;
cout<<"���ݵ����㷨"<<endl;

//��ͷ��ʼ����
cout<<"��ͷ��ʼ����ķ��ʴŵ���˳����:";

current=start;
for(i=0;i<q;i++){
  flag=1000;
  p=-1;
  for(j=0;j<q;j++){
   if((queue[j].t==0)&&(queue[j].texe>=current)){
    if(abs(queue[j].texe-current)<flag){
     p=j;
     flag=abs(queue[j].texe-current);
    }
   }
  }
  if(p!=-1){
    cout<<queue[p].texe<<"  ";
    total+=abs(queue[p].texe-current);
    current=queue[p].texe;
    queue[p].t=1;
  }
  else{
   for(j=0;j<q;j++){
    if((queue[j].t==0)&&(queue[j].texe<current)){
     if(abs(queue[j].texe-current)<flag){
      p=j;
      flag=abs(queue[j].texe-current);
     }
    }
   }
   cout<<queue[p].texe<<"  ";
   total+=abs(queue[p].texe-current);
   current=queue[p].texe;
   queue[p].t=1;
  }
}
cout<<endl<<"��ͷ�ƹ���������:"<<total<<endl;

//��ͷ��ʼ����
for(i=0;i<q;i++){
  queue[i].t=0;
}
total=0;

cout<<"��ͷ��ʼ����ķ��ʴŵ���˳����:";

current=start;
for(i=0;i<q;i++){
  flag=1000;
  p=-1;
  for(j=0;j<q;j++){
   if((queue[j].t==0)&&(queue[j].texe<=current)){
    if(abs(queue[j].texe-current)<flag){
     p=j;
     flag=abs(queue[j].texe-current);
    }
   }
  }
  if(p!=-1){
    cout<<queue[p].texe<<"  ";
    total+=abs(queue[p].texe-current);
    current=queue[p].texe;
    queue[p].t=1;
  }
  else{
   for(j=0;j<q;j++){
    if((queue[j].t==0)&&(queue[j].texe>current)){
     if(abs(queue[j].texe-current)<flag){
      p=j;
      flag=abs(queue[j].texe-current);
     }
    }
   }
   cout<<queue[p].texe<<"  ";
   total+=abs(queue[p].texe-current);
   current=queue[p].texe;
   queue[p].t=1;
  }
}
cout<<endl<<"��ͷ�ƹ���������:"<<total;

*/}


void main()
{
initial();
	if(readData())
	{cout<<"�������ͷ����ʼλ�ã�"<<endl;
	cin>>start;
	int c,f=1;
	while(f)
	{
	cout<<endl<<"-------------------------"<<endl;
	cout<<" 0���˳�   1��FIFO     2�����Ѱ�����ȵ����㷨    3�������㷨 "<<endl;
	cout<<"-------------------------"<<endl;
	cout<<"��ѡ��"<<endl;
	cin>>c;
	switch(c)
		{case 1:
			init();
			FIFO();
			break;
		case 2:
			init();
			shortest();
			break;
		case 3:
			init();
			elevator();
			break;
		case 0:
			f=0;
			break;
		default:
			cout<<"ѡ�����!"<<endl;
		}

	}
	cout<<"��ӭʹ�ñ�ϵͳ"<<endl;
	}
}