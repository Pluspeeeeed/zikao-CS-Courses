#include <iostream.h>
#include <string.h>
#include<stdlib.h>
const int M=5;

struct MEM
{
	int number;//����
	int length;//������С
	int beginaddress;//����ʼַ
	int status;//����״̬ 0 ��ʾδռ�ã�1 ��ʾռ��
	char jobname[20];//��ҵ��
};

void allocate(MEM table[],char name[],int length)
{
	int i=0;  int flag=-1;  
	for(i=0;i<M;i++)
	{//�ҵ����ʵľ�����
		if(table[i].status==0&&table[i].length>=length) 
		{flag=i;break;}
	}
	if(flag==-1)
	{
		cout<<"\nû���ҵ���������ķ���!\n";return;
	}
	strcpy(table[i].jobname,name);
	table[i].status=1;
	cout<<"�ѳɹ�Ϊ��ҵ"<<name<<" ����"<<length<<"��С���ڴ�ռ�n"<<endl;
	return;
}

void reclaim(MEM table[],char name[])
{
	int   i=0;
	while(i<M&&strcmp(table[i].jobname,name)!=0)
		i++;//�������ҵ��ļ��ż���
	if(i>=5)
	{
		cout<<"\n�������ҵ���ڴ���û���ҵ�!"<<endl;
		return;
	}
	table[i].status=0;
	strcpy(table[i].jobname,"##");
	cout<<"�Ѿ��ɹ��ջ���ҵ"<<name<<"ռ�õ��ڴ�����!"<<endl;
}
void main()
{
	char name[20];
	int length;
	int select=0;
	int i;
	MEM table[M]={  //��ʼ����������ҵ��Ϊ��##�����
		{0,8,0,0,"##"},
		{1,16,10,0,"##"},
		{2,24,30,0,"##"},
		{3,56,60,0,"##"},
		{4,120,120,0,"##"}};  
		
		cout<<"���������"<<endl;
		cout<<"������  ���� ��ʼ��ַ ����״̬ ��ҵ��"<<endl;
		for(i=0;i<M;i++)
		{
			cout<<"  "<<table[i].number<<"  "<<table[i].length<<" "<<table[i].beginaddress ;
			cout<<"  "<<table[i].status <<" "<<table[i].jobname <<endl;
		}
		while(1)
		{
			cout<<"��ѡ��˵�: "<<endl;
			cout<<"0_�˳� 1_�����ڴ� 2_�����ڴ� 3_��ʾ�ڴ����"<<endl;
			
			cin>>select;
			switch(select)
			{
			case 0: exit(0);
			case 1: 
				cout<<"������ҵ��: ";
				cin>>name;
				cout<<"������ҵ��С: ";
				cin>>length;
				allocate(table,name,length);
				break;
			case 2:
				cout<<"������ҵ��: ";
				cin>>name;
				reclaim(table,name);
				break;
			case 3:
				cout<<"������  ���� ��ʼ��ַ ����״̬ ��ҵ��"<<endl;
				for(i=0;i<M;i++)
				{
					cout<<"  "<<table[i].number<<"  "<<table[i].length <<" "<<table[i].beginaddress ;
					cout<<"  "<<table[i].status <<" "<<table[i].jobname <<endl;
				}
				break;
			default:
				cout<<"�����������������!"<<endl;
				break;
			}
		}
}


