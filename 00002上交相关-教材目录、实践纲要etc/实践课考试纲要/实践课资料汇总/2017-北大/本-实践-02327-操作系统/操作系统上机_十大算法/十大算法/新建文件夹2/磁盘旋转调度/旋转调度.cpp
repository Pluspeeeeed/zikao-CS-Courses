#include <iostream.h>   
#include <fstream.h>
#include <stdlib.h>  
const int M=4;
const int SQS=20;//�����������

struct XZDU
{
	char qqcx;  //�������
	int zmh;  //�����
	int cth;  //��ͷ��    
	int sqh;  //������
};

void create(XZDU table[]) 
{ 
	ifstream f1;
	char filname[20];  
	int i;
	cout<<"��������ת���ȵ��ļ���:"<<endl;
	cin>>filname;  
	f1.open(filname,ios::in|ios::nocreate);
	if(!f1)
	{
		cout<<"���ܴ�ָ���ļ�!"<<endl;  
		exit(1);
	}
	for(i=0;i<M;i++)
	{
		f1>>table[i].qqcx;  
		f1>>table[i].zmh;
		f1>>table[i].cth; 	
		f1>>table[i].sqh; 
	}
	cout<<"��ת�����ļ�������Ϊ��"<<endl;
	for(i=0;i<M;i++)
	{
		cout<<" "<<table[i].qqcx<<" "<<table[i].zmh<<" ";
		cout<<table[i].cth<<"  "<<table[i].sqh<<endl;
	}
	f1.close();
}

void main()
{
	XZDU xzdu[M];
	int i;int flag[M];int j=0;int flag1=1;
	create(xzdu);
	for(i=0;i<M;i++) flag[i]=0;
	//�ٶ���ͷ��0��ʼ����
	cout<<"���ʴ���Ϊ��"<<endl;
	while(flag1){
		flag1=0;
		for(i=0;i<SQS;i++)
			for(j=0;j<M;j++) 
			{
				if((xzdu[j].sqh==i)&&(flag[j]==0)) 
				{
					flag[j]=1;cout<<xzdu[j].qqcx <<"  ";break;
				}
			}
			for(j=0;j<M;j++) 
				if(flag[j]==0) {flag1=1;break;}
	}

}