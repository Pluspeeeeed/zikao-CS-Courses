/*
UNIXϵͳ�ļ�������������㷨��
�ѿ��п�ֳ������飬��ָ��һ���и����п��ָ�뼯��һ��
�����ȿɷ�����ң��ֿɼ���Ϊ�޸�ָ����������̵Ĵ�����
UNIXϵͳ�����ÿ��п�������ӵķ�����
UNIXϵͳ��ÿ100�����п���Ϊһ�飬ÿһ��ĵ�һ�����п��еǼ���һ����п�Ŀ�źͿ��п��������²���100����ǲ��ֿ��п�Ŀ�ż������Ǽ���һ��ר�ÿ��У��Ǽ����һ���ŵ��Ǹ����п����е�2����Ԫ�0������ʾ�ÿ���ָ���Ŀ�������һ��Ŀ�ţ����п������˽�����
ϵͳ��ʼ��ʱ�Ȱ�ר�ÿ����ݶ����ڴ棬���������п�ʱ����ֱ�����ڴ��п��ҵ���Щ���ǿ��еģ�ÿ����һ���ѿ��п�����1����Ҫ��һ���еĵ�һ�����п�����ȥ֮ǰӦ�ѵǼ��ڸÿ��е���һ��Ŀ�ż��������浽ר�ÿ��С�
��һ����п鱻����������ٰ�ר�ÿ�����ݶ����ڴ棬ָ����һ��ɹ�����Ŀ��п顣���黹һ��ʱ��ֻҪ�ѹ黹��Ŀ�ŵǼǵ���ǰ�����ҿ��п�����1�������ǰ������100�飬����ڴ��е�����д���黹���ǿ��У��ù黹����Ϊ����ĵ�һ�顣�����ʼ��ʱϵͳ�Ѱ�ר�ÿ�����ڴ�L��Ԫ��ʼ�������У�����ͻ��յ��㷨���£�
  ����һ�����п�
��L��Ԫ���ݣ����п�������
�����п���>1 i : ��L�����п�����
��i��Ԫ�õ�һ���п�ţ�
�Ѹÿ����������ߣ�
���п�����1��
�����п�����1 ȡ��L��1��Ԫ���ݣ�һ��ĵ�һ���Ż�0����
��ֵ��0�޿��п飬�����ߵȴ�
��������Ѹÿ����ݸ��Ƶ�ר�ÿ飻
�ÿ����������ߣ�
��ר�ÿ����ݶ�������L��ʼ������
�黹һ��
��L��Ԫ�Ŀ��п�����
�����п���<100 ���п�����1��
j : ��L�����п�����
�黹�������j��Ԫ��
�����п�����100 �������еǼǵ���Ϣд��黹���У�
�ѹ黹�������L��1��Ԫ��
��L��Ԫ�ó�1��
���ó������Ӻ󣬷�����մ��̿�ʱ�����ڴ��в��Һ��޸ģ�ֻ����һ����п���������еĴ��̿�
����һ��ʱ���������̶�д���ȵ������ӷ�ʽЧ�ʸߡ�
*/
/*
6��5��������UNIX�ĳ������ӷ��������ʵ�֣�
��Ҫ���������ļ�����һ�ѿ��п�� ���룬Ȼ������UNIX�ĳ������ӷ��Ĺ�������10���һ�飬
���ҿ���ʵ������һ������N,Ȼ���N�����п�ռ�ã�Ȼ�����ר�ÿ�Ĵ�С�����кš� 
********************************************************************************************/
/*writer:������ ���ʾ�(�����ο�)�����кõĿ����ͽ���,��ӭ�뱾��̽��.furenjun@sohu.com*/

# include <stdio.h>
# include <iostream.h>
# include <iomanip.h>
# include <stdlib.h>

typedef struct node  *pointer;
struct node 
{
	int frenum;
	int frespa[10];
	pointer next;
};

typedef pointer lklist;

static int totalnum=0;
static int flag11=0;
int  wrinum()
{
	FILE *fp;
	if((fp=fopen("freeblock.txt","w+"))==NULL)
	{
		cout<<"Sorry! file can not open!"<<endl;
		exit(0);
	}
	int m=1;
	for(int i=0;i<105;i++)
	{
        fprintf(fp,"%d",m);
		m++;
		fprintf(fp,"%s"," ");
		if((i+1)%10==0)
			fprintf(fp,"%c",'\n');
	}
	cout<<"�����ѳɹ�д���ļ�."<<endl;
	fclose(fp);
	return 1;
}

lklist readfile( lklist head)   //��head Ϊר�ÿ�
{
	FILE *fp;
	if((fp=fopen("freeblock.txt","r+"))==NULL)
	{
		cout<<"Sorry! file can not open!"<<endl;
		exit(0);
	}
	pointer p,q;
	head=new node;
	head->frenum=0; 
	for(int i=0;i<10;i++)
		head->frespa[i]=0;
	head->next =NULL;
	p=head;
	int CouNum=0,s=0;
    while(!feof(fp))
	{
		i=0; 
		int temp=0;
		q=new node ;  //ע�������½��Ӧд��while(1)֮��.
		if(CouNum==0)
        {
			q->frespa[i++]=0; 
			++totalnum;
			++CouNum;
		}
		
		while(1)
        {
			int m=0;
			fscanf(fp,"%d",&m);
        	q->frespa[i++]=m;
			++totalnum;
			//cout<<"m"<<setw(3)<<m;
			//cout<<"i"<<setw(3)<<i;
		    temp=i;
			if((i)%10==0)             //ע��ѭ���˳�������.
				break;
			if(feof(fp))
				break;
		
		}   
		    if(temp%10==0)
            q->frenum=10;
			else
            q->frenum=temp-1;
			if(s==0)
            q->frenum=temp;
			s++;
			q->next=head;
			head=q;
	}
	fclose(fp);
	return head;
}

void show(lklist head)
{
	pointer p;
	p=head ;
    cout<<"���������������:"  <<endl;
	int i=1;
	while(p!=NULL )
    {
        cout<<"��"<<i++<<"��������Ϊ:"<<endl;  
		cout<<"�ܿ���:"<<setw(3)<<p->frenum <<endl;
		int n=p->frenum ;
		for(int j=n-1;j>=0;j--)
		{
			cout<<setw(3)<<p->frespa[j]<<endl;
		}
		p=p->next ;
	}
	return ;
}


lklist allotblock(lklist head)
{
	pointer p;
	cout<<"��������Ҫ����Ŀ���:>";
	int num,count=0,i=0;
	cin>>num;
	p=head;
	cout<<"total="<<totalnum-2<<endl;
   if((num>(totalnum-2))||(num<=0))
   {
	   cout<<"Sorry! can not fulfil your request."<<endl;
	   exit(0);
   }

   int j=0;
	cout<<"�ָ����Ŀ��Ϊ:"<<endl;
	
	while((p!=NULL)&&(count<num))
	{
       i=0;
	   int n=p->frenum;
       if(i>=n )
		   break;

	   flag11=n-1;
	   for( j=n-1;j>=0;j--)
	   {
		   cout<<setw(5)<<p->frespa[j] ;
		   --totalnum;
           ++count;
		   if(count%10==0)
			   cout<<endl;
		   if(count>=num)
		   {
			   flag11=j;
			   
			   break;
		   }
	   }
	   if(count>=num)
		   {
			   
			  // cout<<"flag="<<flag<<endl;
			   break;
		   }
       head=head->next ;
	   p=head;
	}
	//cout<<"flag11="<<flag11<<endl;
	if( j==0)
	{  
		cout<<endl<<"ר�ÿ���������Ϊ:"<<endl;
		cout<<"�ܿ���Ϊ:"<<setw(3)<<p->frenum <<endl;
		head=head->next ;
		p=head;
		cout<<"��������:"<<endl;
		for(i=p->frenum-1;i>=0;i-- )
			cout<<setw(5)<<p->frespa[i]<<endl;
	}
	else
	{
		cout<<endl<<"ר�ÿ���������Ϊ:"<<endl;
		cout<<"�ܿ���Ϊ:"<<setw(3)<<j<<endl;
		cout<<"��������:"<<endl;
        for(i=j-1;i>=0;i-- )
			cout<<setw(5)<<p->frespa[i]<<endl;   
	}
    return head;


}

void main()
{
	lklist head=NULL;
	wrinum();
	head=readfile(head);
    show(head);
	allotblock(head);
}








