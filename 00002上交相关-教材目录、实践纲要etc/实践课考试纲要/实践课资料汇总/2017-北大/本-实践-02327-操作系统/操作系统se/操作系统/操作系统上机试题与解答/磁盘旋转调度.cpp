/*6�£������磺�ϣ��ϻ���������ת�����㷨�����ԣأ��ļ��Ѿ�������*/
/*writer:������ ���ʾ�(�����ο�)�����кõĿ����ͽ���,��ӭ�뱾��̽��.furenjun@sohu.com*/
# include <iostream.h>
# include <fstream.h>
# include <math.h>
# include <iomanip.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct node *pointer;
static int len=0;
int res[100];

 struct node 
{
	int reqord;
	int cylnum;
	int disnum;
	int secnum;
	pointer next;
};


typedef  pointer lklist ;



lklist readfile (lklist head)
{
	FILE *fp;
	//char filename[20];
	//cout<<"Please input file name(disciratt.txt):>";
	//cin>>filename;
	if((fp=fopen("disciratt.txt","r+"))==NULL)
	{
		cout<<"sorry,file can not open!"<<endl;
		exit(0);
	}
    //��ʼ������
	pointer p,q;
	head=new node ;
	head->next=NULL;
	head->reqord=65535;
	head->cylnum=65535;
	head->disnum=65535;
    head->secnum=65535;
	p=head;
    
	while(!feof(fp))
	{
		q=new node ;
		fscanf(fp,"%d",&q->reqord);
		fscanf(fp,"%d",&q->cylnum);
		fscanf(fp,"%d",&q->disnum);
		fscanf(fp,"%d",&q->secnum);
		++len;
		q->next=NULL;
		p->next=q;
		p=q;
	}
	fclose(fp);
	return head;
}  

lklist show( lklist head)
{
    pointer p;
	p=head->next;
	cout<<setw(12)<<"�������"<<setw(10)<<" �����"<<setw(10)<<"���̺�"<<setw(10)<<" ������ "<<endl;
	while(p->next !=NULL)
	{
		cout<<setw(10)<<p->reqord<<setw(10)<<p->cylnum<<setw(10)<<p->disnum<<setw(10)<<p->secnum<<endl;
		p=p->next;
	}
    return head;
}

int SelectSort(lklist head)
{
	int t1,t2,t3,t4;
	lklist p,q,s;
	p=head;
	while(p!=NULL)
	{
		s=p;
		q=p->next ;
		while(q!=NULL)
		{
			if(q->secnum <s->secnum )
               s=q;
			q=q->next ;
		}
		if(s!=p)
		{
			t1=p->reqord ;
			t2=p->cylnum ;
			t3=p->disnum ;
			t4=p->secnum ;
			p->reqord =s->reqord ;
			p->cylnum =s->cylnum ;
			p->disnum =s->disnum ;
			p->secnum =s->secnum ;
			s->reqord =t1;
			s->cylnum =t2;
			s->disnum =t3;
			s->secnum =t4;

		}
		p=p->next ;
	}
	return 1;
}




int disciratt(lklist head,int sec1)
{
	pointer p,q;
	int count=0;
    //int res[100],i=0;
	int i=0;
    p=head ;
	//res[i++]=sec1;
	
	while((p->next!=NULL)&&(p->next->secnum<sec1))  //�ҵ����ڵ��ڵ�ǰ�����ŵĽ��;
	{
		p=p->next;
		++count;
		//cout<<count<<setw(3);

	}
	cout<<"count="<<count<<endl;;
	cout<<"len="<<len<<endl;
	if(count<len-1)          //�����ǰ��ͷ���������ű���������κ������Ŷ���(��С),�������ͷ����ʼ.����Ĳ�������ִ��.
	{

	q=p->next;              //�����ڵ��ڵ�ǰ���ŵĽ��ɾ��;
	res[i++]=q->reqord ;    
    int s=q->secnum ;
	p->next =q->next ;
	delete q;            

	q=p;
	p=p->next ;

	while((p->next!=NULL))  //���ȵ�ǰ�ŵ��Ŵ��Ҳ����ڵ�ǰ�ŵ��ŵ�����������������,�ҽ��ý��ɾ��;

	{
		if(p->secnum!=s)
		{
		res[i++]=p->reqord ;  //���ȵ�ǰ�ŵ��Ŵ��Ҳ����ڵ�ǰ�ŵ��ŵ�����������������,�ҽ��ý��ɾ��;
		s=p->secnum;
		q->next=p->next  ;
		delete p;
		p=q->next ;
		}
		else
		{
			q=q->next ;
			p=p->next ;
		}
	}
	//cout<<"i="<<i<<endl;
	//cout<<"len="<<len<<endl;
	}
	cout<<endl;
	while(i<len-1 )
	{
		q=head;                 //ÿ�ο�ʼ����ɾ��һ�����,������֤ѭ������������.
		p=head->next;
		res[i++]=p->reqord;     //���ȵ�ǰ�ŵ��Ŵ��Ҳ����ڵ�ǰ�ŵ��ŵ�����������������,�ҽ��ý��ɾ��;
		int s=p->secnum;
		q->next=p->next ;
		delete p;
		p=q->next;
		while(p->next !=NULL)
		{
          if(p->secnum!=s)
		  {
		   res[i++]=p->reqord ; //���ȵ�ǰ�ŵ��Ŵ��Ҳ����ڵ�ǰ�ŵ��ŵ�����������������,�ҽ��ý��ɾ��;
		   s=p->secnum;
		   q->next=p->next  ;
		   delete p;
		   p=q->next ;
		  }
		 else
		 {
			q=q->next ;
			p=p->next ;
		 }
		}
	} 

  
	cout<<"���ʴ���˳��Ϊ(��������������):"<<endl;
    for(int j=0;j<len-1;j++)
	{
		
		cout<<setw(3)<<res[j]<<endl;
	}
	
	return 1;
}



void main()
{
	lklist head=NULL;
    head=readfile(head);
	cout<<"���������Ϊ:"<<endl;
	show(head);
    SelectSort(head);
	cout<<"�ź��������Ϊ:"<<endl;
	show(head);
	cout<<"�����뵱ǰ��ͷ����������:>";
	int sec;
	cin>>sec;
	disciratt( head, sec);

	

}


		
	