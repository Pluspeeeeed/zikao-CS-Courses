#include <iostream.h> 
#include <stdlib.h>
const int pover=0,running=1,already=2,wating=3,timeblock=5;


struct pcb{char name;int status;
int time ;pcb* next;
int precendence;};

void FIFO(pcb *head)
{
	cout<<"*******FIFO*******"<<endl;
	pcb *p;	
	p=head;
	int flag=0;
	while(p!=NULL)
	{
		if(p->status==2) 
		{flag=1;break;}
		p=p->next;
	}
	if(flag==1)
	{
		cout<<"��˳���������¾�������:"<<endl;
		cout<<"������   ʱ��  ��־"<<endl;
		while(p!=NULL)
		{
			if(p->status==2)
			{
				cout<<p->name<<"  "<<p->time<<"  "<<"���н���"<<endl; 
				p->status=pover;
			}
			p=p->next;
		}
	}
	p=head; 
    flag=0;
	while(p!=NULL)
	{
		if(p->status==3)
		{
			flag=1;break;
		}
		p=p->next;
	}
    p=head;
	if(flag==1)
	{
		cout<<"��˳���������µȴ�����"<<endl;
		cout<<"������    ʱ��  ��־"<<endl;
		while(p!=NULL)
		{
			if(p->status==3)
			{
				cout<<p->name<<"  "<<p->time<<"  "<<"���н���"<<endl; 
				p->status=pover;
			}
			p=p->next;
		}
	}
}



void RR(pcb* head)
{
	cout<<"******RR*****"<<endl;
	pcb *p;pcb* q;int flag=0;p=head;	
	while(p!=NULL)
	{
		if(p->status==2) 
		{flag=1;break;}
		p=p->next;
	}
	if(flag==1)
	{
		cout<<"��˳���������¾�������:"<<endl;
		cout<<"������     ��־"<<endl;
		int	flag1=1;
		while(flag1==1)
		{
			flag1=0;p=head;
			while(p!=NULL)
			{
				if(p->time<=timeblock)
				{
					if(p->status==2)
					{
						cout<<p->name<<"        "<<"���н���"<<endl; 
						p->status=pover;p->time=0;
					}
				}
				if(p->time>timeblock)
				{
					if(p->status==2)
					{
						cout<<p->name<<"        "<<"������һ��ʱ��Ƭ"<<endl; 
						p->time=p->time-timeblock;
					}
				}
				p=p->next ;
			}
			cout<<"ʱ��Ƭѭ��һ��!"<<endl;
			q=head;
			while(q!=NULL)
			{
				if((q->status==2)&&(q->time>0)) 
				{
					flag1=1;
					break;
				}
				q=q->next ;
			}
		}
	}
	
	
	flag=0;p=head;
	while(p!=NULL)
	{
		if(p->status==3)
		{
			flag=1;
			break;
		}
		p=p->next;
	}
	if(flag==1)
	{
		cout<<"��˳���������µȴ�����:"<<endl;
		cout<<"������     ��־"<<endl;
		int	flag1=1;
		while(flag1==1)
		{
			flag1=0;p=head;
			while(p!=NULL)
			{
				if(p->time<=timeblock)
				{
					if(p->status==3)
					{
						cout<<p->name<<"        "<<"���н���"<<endl; 
						p->status=pover;p->time=0;
					}
				}
				if(p->time>timeblock)
				{
					if(p->status==3)
					{
						cout<<p->name<<"        "<<"������һ��ʱ��Ƭ"<<endl; 
						p->time=p->time-timeblock;
					}
				}
				p=p->next ;
			}
			cout<<"ʱ��Ƭѭ��һ��!"<<endl;
			q=head;
			while(q!=NULL)
			{
				if((q->status==3)&&(q->time>0)) 
				{
					flag1=1;break;
				}
				q=q->next ;
			}
		}
	}	
}

pcb* create(pcb* head)
{
	char name;
	pcb* p,*q=NULL;
	cout<<"�������̵���ʽ�ṹ,��������Ϊ'@'ʱ��ʾ����!"<<endl;
	cout<<"���������:"<<endl;
	cin>>name;
	while(name!='@')
	{
		p=new pcb;
		p->name =name;
		cout<<"������̵�״̬, 2Ϊ����,3Ϊ�ȴ�:";
		cin>>p->status;
		cout<<"������̵�����ʱ��:";
		cin>>p->time ;
		if(head==NULL) head=p;
		else q->next=p;
		q=p;
		cout<<"���������:";
		cin>>name;
	}
	q->next=NULL;
	
	cout<<"��������Ľ��̵���ϢΪ:"<<endl;
	cout<<" ��  ״̬  ʱ��"<<endl;
	
	p=head;
	while(p!=NULL)
	{
		cout<<p->name<<"  ";
		if(p->status==2) cout<<"����";
		else cout<<"�ȴ�";
		cout<<"  "<<p->time <<endl;
		p=p->next ;
	}
	return head;
}



pcb *InsertCreate(pcb *head)
{
	pcb *p,*f;
	char name;
	if(head==NULL)
	{  head=new pcb;
	head->next=NULL;}
	cout<<"�������̵���ʽ�ṹ,��������Ϊ'@'ʱ��ʾ����!"<<endl;
	cout<<"���������:"<<endl;
	cin>>name;
	while(name!='@')
	{ 
		p=new pcb;
		p->name=name;
		cout<<"������̵�״̬, 2Ϊ����,3Ϊ�ȴ�:";
		cin>>p->status;
		cout<<"������̵�����ʱ��:";
		cin>>p->time ;
		cout<<"������̵����ȼ�:";
		cin>>p->precendence;  
		f=head;  
		while((f->next)&&(p->precendence<=f->next->precendence))
			f=f->next;
		p->next=f->next;
		f->next=p;
		cout<<"���������:";
		cin>>name;
	}
	
	cout<<"��������Ľ��̵���ϢΪ:"<<endl;
	cout<<" ��  ״̬  ���ȼ�"<<endl;
	head=head->next;
	p=head;
	while(p!=NULL)
	{
		cout<<p->name<<"     ";
		if(p->status==2) cout<<"����"<<"  ";
		else cout<<"�ȴ�";
		cout<<"  "<<p->precendence <<endl;
		p=p->next ;
	}
	return head;
}



void main()
{
	pcb* head=NULL;	  
	
	cout<<"ѡ������㷨:   1 Ϊ �Ƚ��ȳ�;  2Ϊʱ��Ƭ��ת"<<endl;
	cout<<"3 Ϊ���ȼ�(�Ƚ��ȳ�); "<<endl;
	int z;
	cin>>z;
	
	if(z==1)
	{
		head=create(head);
		FIFO(head) ;
	}
	if(z==2)
	{
		head=create(head);
		RR(head);
	}
	if(z==3)
	{
		head=InsertCreate(head);
		FIFO(head) ;
	}
	
}