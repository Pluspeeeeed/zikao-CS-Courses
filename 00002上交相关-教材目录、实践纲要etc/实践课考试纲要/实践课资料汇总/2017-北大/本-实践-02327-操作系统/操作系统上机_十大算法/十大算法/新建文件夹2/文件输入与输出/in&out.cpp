/*
**********�����ļ������룬���Է�Ϊ���ࡣ
���ļ��еĸ�����������"�հ׷�"(�ո񣬻س����Ʊ��)��Ϊ�ָ��ġ���"<<"���ɡ�
���ļ��еĸ����������������ַ�(��',')�ͻس�����Ϊ�ָ��ġ�����"get(char ch)"ʵ��
Ҳ����getline(char * buf,int len,char='\n')������һ�С�
**********�����ļ������,����">>"ʵ��Ҳ����"put(ch)"ʵ�֡�
*/
#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>
void main()
{	
	ifstream f1,f2;
	ofstream f3;
	char fname[20];
	int kind;
	cout<<"!!!!!!!!!!�ļ�������!!!!!!!!!!"<<endl;
	cout<<"ѡ���ļ�������(1 �� 2):";
	cin>>kind;
	if(kind==1)
	{//��һ���ļ�������
		int x;char a[30];
		cout<<"�������ļ�������!";
		cin>>fname;
		f1.open(fname,ios::in|ios::nocreate);
		if(!f1)
		{
			cout<<"������ļ�������"<<endl;
			exit(1);
		}
		f1.getline (a,30);
		cout<<a;
		while(f1>>x)
			cout<<x<<' ';
		cout<<endl;
	}
	
	if(kind==2)
	{//�ڶ����ļ�������
		char ch='\0';int space=1;int x;
		char str[10];int i=0;
		cout<<"�������ļ�������!";
		cin>>fname;
		f2.open(fname,ios::in|ios::nocreate);
		if(!f2)
		{
			cout<<"������ļ�������"<<endl;
			exit(1);
		}
		//��"end #####"�Ǵ������������ݵ�����
		while(f2.get(ch)){
			if(ch>='0'&&ch<='9') { str[i]=ch;i++; space=0; } 
			else if(ch==','||ch=='\n') 
			{
				if(space==0) {
					str[i]='\0'; x=atoi(str);
					i=0;space=1;
					cout<<x<<' ';
					cout<<endl;}
			}	
		}
		//���ļ�β�޻س�������������У����򲻼�
		str[i]='\0'; x=atoi(str);
		i=0;space=1;
		cout<<x<<' ';
		//end #####
	}
	
	//�ļ������
	cout<<"!!!!!!!!!!�ļ������!!!!!!!!!!"<<endl;
	cout<<"�����ļ�������!"<<endl;
	cin>>fname;
	f3.open(fname,ios::out);
    if(!f3)
	{
		cout<<"������ļ�������"<<endl;exit(1);
	}
	f3<<"�ļ������!!"<<endl;
	int y=100;
	f3<<y<<endl;
	char ch1;
	cout<<"����һ���ַ���"<<endl;
	cin>>ch1;
	f3.put(ch1);
	f3<<endl;
	f3<<"over"<<endl;
}
