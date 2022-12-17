// ���̹���.cpp : Defines the entry point for the console application.
//

#include<stdio.h>
#include<string.h>
#include<iostream.h>
const int MAXGROUP=10;//������Ĵ�С
const int MAXBLOCK=10;
const int MAXJOB=10;//����һ����ҵ���������Ŀ���
//�ṹ�嶨��
typedef struct node{
	int quantity;
	int cell[MAXBLOCK];
	struct node *next;
}group;  

typedef struct node1{
	char name[20];
	int quantity;
	int cell[MAXJOB];  /*asdfcomputer*/
	struct node1 *next;
}job;

group *head,*b;
int total;

job *jhead;

//��ʼ���麯��
void initial()
	{
		int i,j;
		group *q;
		q=head;
		group *p;
		job *w;
		w=new job;
		strcpy(w->name,"null");
		w->quantity=0;
		w->next=NULL;
		jhead=w;
	
	for( i=0;i<MAXGROUP;i++)
	{
		p=new group;
		p->quantity=0;
		p->next=NULL;
		q->next=p;
		q=q->next;

	}
	q=head;
	for(i=0;i<MAXGROUP && (q!=NULL);i++)
	{
		for(j=0;j<MAXBLOCK;j++)
		{
			q->cell[j]=i*MAXBLOCK+j;

		}
		q->quantity=MAXBLOCK;
		q=q->next;
	}
	total=MAXBLOCK*MAXGROUP;
	cout<<"�ܵĿ��п�����"<<total;

}

void bid()
{
	int i,j,num,m;
	char jobname[20];
	m=0;
	group *p;
	job *q=new job;
	//job *jhead1=jhead;
	p=head;
	
	cout<<"��������ҵ������";
	cin>>jobname;

	cout<<"��������ҵ����Ҫ�Ŀ���:";
	cin>>num;
	if((num<=total)&&(num<=MAXJOB))
	{
		strcpy(q->name,jobname);
		total-=num;
		q->quantity=num;
		for(i=0;(i<MAXGROUP) && (m<num);i++)
		{
			for(j=0;(j<MAXBLOCK) && (m<num);j++)
			{
				if(p->cell[j]!=-1){
					p->cell[j]=-1;
					q->cell[m]=i*MAXBLOCK+j;
					m++;
					p->quantity--;
				}
				b=p;
			}
			p=p->next;
		}
		//b���ڼ�¼������Ŀ���
		q->next=jhead->next;
		jhead->next=q;
	}
	else
	{
		cout<<"����Ҫ�Ŀ�������"<<endl;
	}
}
void finish()
{
	int f=0,m=0;
	char jobname[20];
	group *p;
	job *q,*s;
	p=head;
	s=jhead;
	q=jhead->next;
	cout<<"��������ҵ������";
	cin>>jobname;
while((q!=NULL)&&(f==0))
{
	if(!strcmp(q->name,jobname))
		{	
		
			total+=q->quantity;
			for(int i=0;(i<MAXGROUP)&&(f==0);i++)
			{
				if(p->next==b)
				{
					f=1;
					for(int j=0;(j<MAXBLOCK) && (m<q->quantity);j++)
					{
						if(b->cell[j]==-1)
						{	
							b->cell[j]=q->cell[m];
							m++;
							b->quantity++;
						}
					}
						if(m<q->quantity)
						{		
							for( j=0;(j<MAXBLOCK) && (m<q->quantity);j++)
								if(p->cell[j]==-1)
								{
									p->cell[j]=q->cell[m];
									m++;
								
									p->quantity++;
									b=p;

								}
							/*	cout<<p->quantity;
						for( j=0;(j<MAXBLOCK);j++)
						{
							cout<<endl<<p->cell[j]<<" ";
						}*/

						}
						
				
					
				}
				p=p->next;
				
				}
			s->next=q->next;
			delete q;
		}
	cout<<endl;
	q=q->next;
	s=s->next;
}
	if(q==NULL)
	{
		cout<<"û�������ҵ"<<endl;
	}

}
void view_pages()
{
job *p;
int i;

p=jhead->next;
if(p==NULL)cout<<"��ǰû���û���ҵ"<<endl;
else
  cout<<"��ǰ���е��û���ҵҳ�����"<<endl;
while(p!=NULL){
  cout<<"��ҵ��:"<<p->name<<"    ���ÿ���:"<<p->quantity<<endl;
  cout<<"����ҵ������������:"<<endl;
  for(i=0;i<p->quantity;i++){
   cout<<p->cell[i]<<"  ";
  }
cout<<endl;
p=p->next;
}
}
/*typedef struct node{
	int quantity;
	int cell[MAXBLOCK];
	struct node *next;
}group;*/
/*const int MAXGROUP=10;//������Ĵ�С
const int MAXBLOCK=100;
const int MAXJOB=100;//����һ����ҵ���������Ŀ���*/
void view()
{	
		group *p;   /*���涨����group *head �� *b */	            
		p=head;
		for(int i=0;(i<MAXGROUP)&&(p!=NULL);i++)
		{
			for(int j=0;j<MAXBLOCK;j++)
			{
				cout<<"  "<<p->cell[j];	
				
			}
			cout<<" "<<"�еĿ��п�����"<<p->quantity<<endl;
			p=p->next;
		}
		cout<<"���еĿ��п���"<<total;
}
void main()
{		

	head=new group;
	initial();
		int f=1;
		int chioce;
		while(f){
		  cout<<endl<<"===================================================="<<endl;
		  cout<<"           ģ��UNIX�ĳ������ӷ�    "<<endl;
		  cout<<"===================================================="<<endl;
		  cout<<"1.������п�  2.������ҵ 3.�鿴ר�ÿ�  4���鿴��ҵ 0.�˳�"<<endl;
		  cout<<"��ѡ��:";
		  cin>>chioce;

		  switch(chioce)
		  {
		  case 1:
			   bid();
			   break;
		  case 2:
			   finish();
			   break;
		  case 3:
				view();
				break;
		  case 4:
				view_pages();
				break;
		  case 0:
				f=0;
				break;
		  default:
		   cout<<"ѡ�����!"<<endl;
		  }
			}

}
 

