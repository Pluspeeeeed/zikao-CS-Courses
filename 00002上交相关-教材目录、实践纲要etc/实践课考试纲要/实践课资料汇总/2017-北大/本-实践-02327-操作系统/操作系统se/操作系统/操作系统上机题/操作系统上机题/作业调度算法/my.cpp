/*ÿ����ҵ�������������
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
���������:FIFO������ʱ��̵���ҵ���ȣ������������㷨����Ӧ����������ȵ����㷨*/
#include<iostream.h>
#include<string.h>
#include<stdio.h>
#define MAX 50
typedef struct node{
	char name[20];
	int intime;
	int time;
	int youxian;
}job;
job a[MAX];
int b(0);
void in(){
	FILE *fp;
	int i;
	char fname[20];
	cout<<"�����ļ�����:"<<endl;
	//cin>>fname;
	strcpy(fname,"a.txt");
	if((fp=fopen(fname,"r"))==NULL)
	{	cout<<"�Ҳ����ļ�"<<endl;}
	
	else 
	{
		while(!feof(fp))
		{
		fscanf(fp,"%s %d %d",a[b].name,&a[b].intime,&a[b].time);
		a[b].youxian=0;
		b++;
		}
	
	}
	cout<<"��ҵ"<<"  "<<"����ʱ��"<<"  "<<"��Ҫʱ��"<<"  "<<"���ȼ�"<<endl;

	for(i=0;i<b;i++)
	{ 
	cout<<a[i].name<<"       "<<a[i].intime<<"     "<<a[i].time<<"           "<<a[i].youxian<<endl;
	}
}

void fifo(job p[])
{
	cout<<"��ҵ"<<"  "<<"����ʱ��"<<"  "<<"��Ҫʱ��"<<"  "<<"��ʼʱ��"<<"���ʱ��"<<"��תʱ��"<<endl;
	cout<<p[]
}
void main(){
	in(a);

}
