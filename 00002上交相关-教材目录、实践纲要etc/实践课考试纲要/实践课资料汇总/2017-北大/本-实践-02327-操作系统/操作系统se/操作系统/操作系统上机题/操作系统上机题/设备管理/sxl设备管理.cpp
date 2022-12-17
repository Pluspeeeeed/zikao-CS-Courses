//�豸����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip.h>
#define False 0
#define True 1
#define N 4
#define M 10 //�ܹ��豸̨��
typedef struct {
	char type[10];
	int OwnNumber;
	int NowNumber;
	int Address;
}node1;
node1 EquipType [N];
typedef struct {
	int SysNumber;//���Ժ�
	int Status; //�豸�Ƿ�û�
	int Flag;//�豸�Ƿ��ѷ���
	char Job[5];
	int UserNumber;//��Ժ�
}node2;
node2 Equipment[M];

//�豸����ʼ��
void InitEquipment(){
	int i;
	strcpy(EquipType[0].type,"input");
	EquipType[0].OwnNumber=2;
	EquipType[0].NowNumber=2;
	EquipType[0].Address=0;

	strcpy(EquipType[1].type,"printer");
	EquipType[1].OwnNumber=3;
	EquipType[1].NowNumber=3;
	EquipType[1].Address=2;
	
	strcpy(EquipType[2].type,"disk");
	EquipType[2].OwnNumber=4;
	EquipType[2].NowNumber=4;
	EquipType[2].Address=5;

	strcpy(EquipType[3].type,"tape");
	EquipType[3].OwnNumber=1;
	EquipType[3].NowNumber=1;
	EquipType[3].Address=9;

	for( i=0;i<M;i++){
		Equipment[i].SysNumber=i;
		Equipment[i].Status=1;
		Equipment[i].Flag=0;
	}
}

//�豸���亯��
void Allocate(){
	char Job[5],type[10];
	//���ȼ������豸����д�豸�����
	int find=0,pos=0,add=0,exit=0,Num,temp=0;
	cout<<"��������ҵ��:"<<endl;
	gets(Job);
	cout<<"��������ҵ�����豸��(input/printer/disk/tape):"<<endl;
	gets(type);
	cout<<"��������ҵ�����豸̨��:"<<endl;
	cin>>Num;
	for(pos=0;pos<N;pos++){
		if((strcmp(EquipType[pos].type,type)==0) && (EquipType[pos].NowNumber>=Num)){
			find=1;
			break;
		}
	}
	if(find==0){
		cout<<"�޸����豸�����豸�ִ����̨�������㣬�豸����ʧ�ܣ�"<<endl;
		return;
	}
	else{
		for(int i=0;((i<M) && (exit==0));i++){
			temp=Equipment[i].SysNumber;
			if((temp>=EquipType[pos].Address)){
				if((Equipment[i].Status==1) && (Equipment[i].Flag==0)){
					add++;
					Equipment[i].Flag=1;
					strcpy(Equipment[i].Job,Job);
					Equipment[i].UserNumber=add;
					if(add>=Num){
						exit=1;
					}
				}
			}
		}
		if(exit==1){
			EquipType[pos].NowNumber-=Num;
			cout<<"�豸����ɹ���"<<endl;
			cout<<endl;			
		}
	}
}
void Reclaim(){
	char Job[5],temp=0;
	int pos=0,add=0,own=0,find=0,num=0,f=1,f1=0;
	cout<<"��������ҵ��:"<<endl;
	cin>>Job;
	while(f==1){
		if(!strcmp(Equipment[pos].Job,Job))
		{
			Equipment[pos].Flag=0;
			strcpy(Equipment[pos].Job,"");
			Equipment[pos].UserNumber=0;
			temp=Equipment[pos].SysNumber;
			f1=1;
			for(int i=0;i<N;i++)
			{	if(EquipType[i].Address==temp)
				{	//cout<<"sssssssssssss";
					EquipType[i].NowNumber++;
					break;
				}
				else {
					if(EquipType[i].Address>temp)
					{	
						i--;
						EquipType[i].NowNumber++;
						break;
					}
				}
			}
		}
		pos++;
		if(pos>M){
			f=0;
		}
	}
	if(f1==0){
		cout<<"û�з�����Ҫ���յ������豸���豸����ʧ�ܣ�"<<endl;
		return;
	}
	

	

	/*add=EquipType[pos].Address;
	own=EquipType[pos].OwnNumber;
	num=add+own;
	for(find=0;add<num;add++){
		if((Equipment[add].Flag==1)){
			find=1;
			Equipment[add].Flag=0;
			Equipment[add].UserNumber=0;
			strcpy(Equipment[add].Job," ");
			EquipType[pos].NowNumber+=nu;
			break;
		}
	}
	if(find==0){
		cout<<"������ҵû��ʹ�ø����豸��"<<endl;
	}*/
}

void DispEquipment(){
	int i=0;
	cout<<"�豸���"<<endl;
	cout<<"�豸����  �豸ӵ����  ���ڿ����豸��"<<endl;
	for(i=0;i<N;i++){
		cout<<EquipType[i].type<<"  "<<EquipType[i].OwnNumber<<"  "<<EquipType[i].NowNumber<<endl;
	}
	cout<<"�豸��:"<<endl;
	cout<<"���Ժ�  ��/��   ��/δ����   ռ����ҵ��  ��Ժ�"<<endl;
	for(i=0;i<M;i++){
		cout<<Equipment[i].SysNumber<<"  "<<Equipment[i].Status<<"  "<<Equipment[i].Flag<<"  "<<Equipment[i].Job<<"  "<<Equipment[i].UserNumber<<endl;
	}
}
void main(){
	
	int Menu,exit1;
	while(1){
		cout<<"��ռ�豸�ķ�������գ�"<<endl;
		cout<<"1.�豸���ʼ��"<<endl;
		cout<<"2.����һ���豸"<<endl;
		cout<<"3.����һ���豸"<<endl;
		cout<<"4.��ʾ�豸�����"<<endl;
		cout<<"5.�˳�"<<endl;
		cin>>Menu;
		if(Menu<=5&&Menu>0){
			switch(Menu){
				case 1:
					InitEquipment();
					break;
				case 2:
				
					Allocate();
					break;
				case 3:
					Reclaim();
					break;
				case 4:
					DispEquipment();
					break;
				case 5:
					exit1=1;
					break;
			}
		}
		if(exit1==1){
			break;
		}
	}
}