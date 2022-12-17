#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0 
#define true 1 
#define n 4 
#define m 10 
struct 
{ 
	char type[10]; /*�豸����*/ 
	int count; /*ӵ���豸̨��*/ 
	int can_use; /*�ִ�Ŀ����豸̨��*/ 
	int address; /*�����豸���豸���е���ʼ��ַ*/ 
}equiptype[n]; /*�豸����壬�ٶ�ϵͳ��n���豸����*/ 
struct 
{ 
	int number; /*�豸���Ժ�*/
	int status; /*�豸�û�״̬,1:ok,0:can not use*/ 
	int used; /*�豸�Ƿ��ѷ��� 1:used,0 :free*/
	char jobname[10];/*ռ���豸����ҵ��*/ 
	int lnumber; /*�豸��Ժ�*/ 
}equipment[m]; /*�豸���壬�ٶ�ϵͳ��m���豸*/ 
void allocate(char *J,char *type,int mm) 
{
	int i,address; /*��ѯ�����豸*/ 
	i=0;int j=0;
	while(i<n&&strcmp(equiptype[i].type,type)!=0)
		i++; 
	if(i>=n)/*û���ҵ������豸*/ 
	{ printf("�޸����豸,�豸����ʧ��");
	return; 
	} 
	if(equiptype[i].can_use<1)/*�����豸�ִ����̨������*/
	{ 
		printf("�����豸���㣬����ʧ��"); 
		return; 
	} 
	address=equiptype[i].address;/* ȡ�������豸���豸���е���ʼ��ַ*/ 
	while(equipment[address].status==1 && equipment[address].used==1) 
	{address++; j++;}/*��д��ҵ������Ժţ�״̬��Ϊ�ѷ���*/ 
	equiptype[i].can_use--; 
	equipment[address].used=1; 
	strcpy(equipment[address].jobname,J); 
	equipment[address].lnumber=mm; 
	equipment[address].status=1;
	return;
}/*�豸���亯������*/ 

void reclaim(char *J,char *type) 
{ 
	int i=0,t,j,k=0,nn; 
	
	while(i<n&&strcmp(equiptype[i].type,type)!=0)
		i++; 
    if(i>=n)//û���ҵ������豸
	{ 
		printf("�޸����豸,�豸����ʧ��");
		return;
	} 
	t=equiptype[i].address; /*ȡ�������豸���豸���е���ʼ��ַ*/ 
	j=equiptype[i].count; /*ȡ�������豸������*/ 
    nn=t+j; 
	for(;t<nn;t++) 
	{
		if(strcmp(equipment[t].jobname,J)==0&&equipment[t].used==1)
		{ k++;
		
		equipment[t].used=0;
		equipment[t].lnumber=0;
		strcpy(equipment[t].jobname,"  ");
		}  
		equiptype[i].can_use+= k;
	}
	if(k==0) 
		printf("����ҵû��ʹ�ø����豸\n");
	
}/*�豸���պ�������*/ 

void main( ) 
{ 
	char J[4]; 
	int i,mm,a; 
	char type[10]; /*�豸����ʼ����*/
	strcpy(equiptype[0].type,"input");/*�����*/
	equiptype[0].count=2;
	equiptype[0].can_use=2; 
	equiptype[0].address=0;
	strcpy(equiptype[1].type,"printer");/*��ӡ�� */
	equiptype[1].count=3;
	equiptype[1].can_use=3; 
	equiptype[1].address=2; 
	strcpy(equiptype[2].type,"disk");/*���̻�*/ 
	equiptype[2].count=4;
	equiptype[2].can_use=4; 
	equiptype[2].address=5;
	strcpy(equiptype[3].type,"tape");/*�Ŵ���*/ 
	equiptype[3].count=1; 
	equiptype[3].can_use=1; /*�豸���ʼ����*/ 
	equiptype[3].address=9;
	for(i=0;i<10;i++) 
	{ 
		equipment[i].number=i;
		equipment[i].status=1;
		equipment[i].used=0;
	} 
	while(1) 
	{ 
		printf("\n0���˳���1�����䣬2�����գ�3����ʾ");
		printf("\nѡ�����0~3��:"); 
		scanf("%d",&a); 
		switch(a) { 
		case 0 : /*a=0�������*/ 
			exit(0); 
		case 1 : /*a=1�����豸*/
			printf("������ҵ������ҵ�����豸����豸��Ժ�"); 
			scanf("%s%s%d",J,type,&mm);
			allocate(J,type,mm);/*�����豸*/
			break; 
		case 2: /*a=2�����豸*/ 
			printf("������ҵ������ҵ�黹���豸��"); 
			scanf("%s%s",J,type);
			reclaim(J,type);/*�����豸*/
			break;
		case 3: /*a=3 ����豸�����豸�������*/ 
			printf("\n����豸���\n"); 
			printf(" �豸���� �豸���� ���к��豸\n"); 
			for(i=0;i<n;i++) 
				printf("%9s%8d%9d\n",equiptype[i].type,equiptype[i].count, equiptype[i].can_use); 
			printf("����豸��:\n"); 
			printf("���Ժ� ��/�� ��/δ���� ռ����ҵ�� ��Ժ�\n"); 
			for(i=0;i<m;i++) 
				printf("%3d%8d%9d%12s%8d\n",equipment[i].number, equipment[i].status,equipment[i].used,equipment[i].jobname, 
				equipment[i].lnumber); 
		} 
	} 
}
