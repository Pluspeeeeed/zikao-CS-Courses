/* 6��4��������~~~
ģ��ڶ��λ���ҳ���û��㷨
1�� ���룺
ҳ�����ļ������д洢����һϵ��ҳ��ţ�ҳ�����������ʾ���ÿո���Ϊ�ָ�����������ģ��������ҳ�档
������һ��ʾ�⣺
1 2 3 4 1 2 5 1 2 3 4 5
2�� ����Ҫ��
��������ʱ��������ʾ��������ҳ�����ļ����ļ�������������һ���ļ����󣬳��򽫶�����ļ��е��й����ݡ�
��ʼ��������������ҳ�򣬳�ʼʱ��Ϊ�ա�
���ݵڶ��λ����㷨�����ݽ��д���
3�� ���Ҫ��
ÿ����һ��ҳ�棨����ÿ����һ��ҳ��ţ����ж��Ƿ���ҳ����Ҫ�����������У��ѱ�������ҳ����������Ļ�ϣ���û�У������һ����*���š�
4�� �ļ���Լ��
�ύ��Դ�������֣�sourceXXX.c����sourceXXX.cpp��������������ȷ����
�����ļ����֣������û�ָ��
���У�XXXΪ�˺š�
5�� ����˵�������Խ�ʦ������׼����һ���ļ�����ʽΪ*.txt��������Ϊÿ���������ָ��һ������
��Ϊ�����ļ�������������Ӽ�������ָ���ļ����ļ����������鿴������������
6�� �ڶ��λ����㷨����FIFO�㷨�����¼򵥵��޸ģ������滻ʱ���ȼ������ҳ���R�����ʣ�λ��
���Ϊ0����ô��ҳ�������类����ģ����ҽ���û�б����ʣ��������̱��滻�������RλΪ1��
�����Rλ�����޸�����װ��ʱ�䣬ʹ������ձ�װ�����ҳ��һ����Ȼ������������滻������ҳ�档
*******************************************************************************************/
/*writer:������ ���ʾ�(�����ο�)�����кõĿ����ͽ���,��ӭ�뱾��̽��.furenjun@sohu.com*/
# include <iostream.h>
# include <stdio.h>
# include <stdlib.h>
# include <iomanip.h>
static int a[100];
int  readfile()
{
	char filename[20];
	int i,j,m;
	i=0;j=0;
	cout<<"�������ļ���(test1.txt):>";
	cin>>filename;
    FILE *fp;
	if((fp=fopen(filename,"r+"))==NULL)
	{
		cout<<"sorry,file can not open!"<<endl;
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%d",&m);
		a[i++]=m;
	}
	cout<<"�ղŶ�������ݸ���Ϊ:"<<i--<<endl;
	for(j=0;j<=i;j++)
	{
		cout<<setw(5)<<a[j];
	//	if((j+1)%5==0)
	//		cout<<endl;
	}
	cout<<endl;
	return i;
}
typedef struct node *pointer;
struct node 
{
	int data;
	int r;
	pointer next;
};
typedef pointer lklist;

 lklist init_lklist ()
 {
	 lklist head;
	 pointer p,q;
	 head=new node;
	 head->next=NULL;
	 p=head;
	for(int i=0;i<3;i++)
	 {
		 q=new node;
		 q->data=65535;
		 q->r=0;
		 q->next =NULL;
		 p->next=q;
		 p=q;
	 }
	 q->next=NULL;
	 return head;
 }
 
lklist show(lklist head)
{
	pointer p;
	p=head->next ;
	int n=0;
	while(p!=NULL)
	{
		if((p->data)==65535)
			cout<<setw(3)<<n;
		else
		cout<<setw(3)<<p->data;
		cout<<"("<<p->r<<")";
		p=p->next;
	}
	cout<<endl;
	return  head;
}

int   find_lklist (lklist head,int x) //�����½����ҳ�����ڴ����Ƿ��Ѿ�����.
{
	pointer p,q;
	int flag=0;
	p=head ;
    q=p->next;
    while(q !=NULL)
	{
		if(q->data==x)
		{
            (q->r)+=1;
			flag=1;
			cout<<setw(3)<<"*";  
            return 1;
		}
		    q=q->next;
	}
	if(flag==0)
	return 0;
	else
	return 1;
}

lklist update_lklist(lklist head,int x )  //�ڶ��λ����㷨,����ҳ��.
{
	pointer p,q,w,j;
		p=head;
		int flag=0;
		while(p->next !=NULL)
		{       q=p->next ; 
				if(q->r>=1)
				{
					w=new node;
					w->data=q->data;
					w->r=0;
					w->next=NULL;
					p->next=q->next;
						delete q;
					j=head;
                    while(j->next!=NULL)
					j=j->next;
                               //ɾ��ʱ������w->next=j->next;(�����м�)
				    j->next=w;
				}
             if(q->r==0)
			{
				if(q->data ==65535)
					cout<<setw(6)<<" NULL ";   
				else
				cout<<setw(3)<<q->data;
				w=new node;
				w->data=x;
				w->r=0;
		        w->next=NULL;
				p->next=q->next;
                delete q;
				j=head;
                while(j->next!=NULL)
					j=j->next;
                 j->next=w;
				 flag=1;
				 break;
			}
		}
return head;
}



lklist fifo_lklist(lklist head,int x )
{
	        pointer p,q,w,j;
        	p=head;
			q=p->next ;
        	int flag=0;
				if(q->data ==65535)
					cout<<" NULL ";
				else
				cout<<setw(3)<<q->data;
				w=new node;
				w->data=x;
				w->r=0;
		        w->next=NULL;
				p->next=q->next;
                delete q;
				j=head;
                while(j->next!=NULL)
					j=j->next;
                 j->next=w;
		  return head;
}


int   LRU_find (lklist head,int x) //�����½����ҳ�����ڴ����Ƿ��Ѿ�����.
{
	pointer p,q;
	int flag=0;
    p=head ;  
    q=p->next;
    while(q !=NULL)
	{
		if(q->data==x)
		{
			flag=1;
			cout<<setw(3)<<"*";  //��������򲻲���ȱҳ�ж�,���"*".
            return 1;
		}
		    q=q->next;
	}
	if(flag==0)
	return 0;
	else
	return 1;
}

int LRU_notfind(lklist head)  //���û�ҵ��������ͷԪ��
{
	pointer p;
	p=head->next ;
	if(p->data ==65535)
		cout<<" NULL ";
	else
	cout<<setw(3)<<p->data ;
	return 1;
}

lklist LRU_update(lklist head,int x)  //����ҳ��,�����һ��Ԫ�س���,��Ԫ�������β.
{ 
	pointer p,q,w;
	p=head ;
    
    q=p->next;
    while(q !=NULL)
	{
		(q->r)+=1;  //����ҳ�����ʱ���1;
        q=q->next;
	}

	p=head->next ;
	head->next =p->next ;
	delete p;
	p=head;
	while(p->next!=NULL)
		p=p->next ;
	w=new node;
	w->data =x;
	w->r=0;
	w->next =NULL;
	p->next =w;
	return head;
}


int LFU_find(lklist head, int x)
{
	pointer p;
	p=head->next ;
	int flag=0;
	while(p!=NULL )
	{
		if(p->data ==x)
		{
			(p->r)+=1; 
			cout<<setw(3)<<"*";
			flag=1;
			break;
		}
        p=p->next ;
	}
    if(flag==0)
		return 0;
	else
	return 1;
}


lklist LFU_notfind(lklist head,int x)
{
	pointer p,q,w,j,z;
	p=head;
	j=p;
	q=p->next ;
	w=q;
	int y=q->r ;
    while(q!=NULL)    
	{
		if(q->r<y)
		{
			y=q->r ;
			w=q;
			j=p;
		}
        p=p->next ;
		q=q->next ;
	}
	if(w->data==65535)
		cout<<" NULL ";
	else
    cout<<setw(3)<<w->data ;
    j->next=w->next ;
    delete w;
	p=head;
	while(p->next!=NULL)
		p=p->next ;
    z=new node ;
	z->data =x;
	z->r =0;
    z->next=NULL;
    p->next =z;
    return head;
}


int OPT_find(lklist head, int x)
{
	pointer p;
	p=head->next ;
	int flag=0;
	while(p!=NULL )
	{
		if(p->data ==x)
		{
			cout<<setw(3)<<"*";

			//show(head);
			flag=1;
			break;
		}
        p=p->next ;
	}
    if(flag==0)
		return 0;
	else
	return 1;
}


lklist OPT_notfind(lklist head,int x,int start,int len)
{
	pointer p,q;
	p=head;
	
	q=head->next ;
	int num,j,s1;
	for(int i=1;i<=3;i++)  //��һ����������˭���ʱ��ŷ��ʵ���.
	{  
		j=1;
		int flag=0;
		num=q->data ;
		s1=start;   //�˴�һ��Ҫ����һ��������ִ��startֵ,��������һ��forѭ��startֵ����ı�
    	while((len-s1)>=0)
		{   
 
		
			if(num==a[s1++])
			{
				flag=1;
				q->r=j;
				break;
			}
			j++;
		}
		if(flag==0)
			q->r=65535;
			
		q=q->next ;

	}
	pointer w,y;
	p=head;
	w=p;
	q=head->next ;
	y=q;
    int max;
	max=q->data ;
	while(q!=NULL)   //�ҳ��ʱ��ŷ��ʵ���ҳ��
	{
		if(max<=q->r )
		{
			max=q->r ;
            w=p;
			y=q;
		}
		p=p->next ;
		q=q->next ;
	}
	if(y->data ==65535)
		cout<<" NULL ";
	else
	cout<<setw(3)<<y->data ;
//	show(head);
	w->next =y->next ;  //ɾ���ҵ���ҳ��
	delete y;
	pointer z;           
    z=new node ;        //������ҳ�� 
	z->data =x;
	z->next =NULL;
	z->r =0;
	p=head->next ;
	while(p->next !=NULL)
		p=p->next ;
	p->next =z;
	return head;
}


	
void main()
{
	int n,x;
	n=readfile();
	pointer p;
	p=init_lklist();
	int i;
	//cout<<"check"<<endl;
	//for( i=0;i<=n;i++)
    //cout<<setw(6)<<a[i];
    //cout<<endl;
    //cout<<"init :  ";
    //show(p);
	cout<<"start : "<<endl;
	cout<<"( * )"<<"��ʾû�в���ȱҳ�ж�.���������������ҳ��."<<endl<<endl;
	cout<<"�ڶ��λ����㷨."<<endl;
    int find=0; 
	for( i=0;i<=n;i++)
	{
	   x=a[i];
       find=find_lklist (p, x);
	   if (find==0)
		   update_lklist(p,x);
	   //show(p);        //���ϴ˾佫��ʾ����ҳ��仯����.
	}
	cout<<endl;
    p=init_lklist();
    cout<<"(FIFO)�Ƚ��ȳ��㷨." <<endl;
	find=0;
	for( i=0;i<=n;i++)
	{
	   x=a[i];
       find=find_lklist (p, x);
	   if (!find)
		   fifo_lklist(p,x);
	   //show(p);   //���ϴ˾佫��ʾ����ҳ��仯����.
	}
	cout<<endl;
    cout<<"(LRU)�������ʹ���㷨:"<<endl;
    p=init_lklist();
	find=0;
	for(i=0;i<=n;i++)
	{
		x=a[i];
        find=LRU_find (p,x) ; //�����ڴ����½����ҳ���Ƿ��Ѿ�����,���������"*"��.
		
		if(!find)
		LRU_notfind(p);   //����������������һ��Ԫ��.
        LRU_update(p,x);  //����ҳ��,�����һ��Ԫ�س���,��Ԫ�������β.
		//show(p);        //���ϴ˾佫��ʾ����ҳ��仯����.
	}   
	cout<<endl;
	cout<<"(LFU)������ʹ���㷨:"<<endl;
    p=init_lklist();
	find=0;
    for(i=0;i<=n;i++)
	{
		x=a[i];
        find=LFU_find (p,x) ; //�����ڴ����½����ҳ���Ƿ��Ѿ�����,���������"*"��.
		if(!find)
			LFU_notfind(p,x);
		//show(p);
	}
	cout<<endl;

	cout<<"(OPT)����ҳ���û��㷨:"<<endl;
    p=init_lklist();
	find=0;
    for(i=0;i<=n;i++)
	{
		x=a[i];
        find=OPT_find (p,x) ; //�����ڴ����½����ҳ���Ƿ��Ѿ�����,���������"*"��.
		if(!find)
			OPT_notfind(p,x,i,n);
	
	}
	cout<<endl;

}


