/*6���ĺ�����Ŀ���
ģ�������Ӧ��������ҵ�����㷨
**********************
���룺��ҵ���ļ������д洢����һϵ��Ҫִ�е���ҵ��
ÿ����ҵ�������������
��ҵ�š���ҵ����ϵͳ��ʱ�䣨��һ������ʾ����10��10����ʾ��1010��������ִ��ʱ�䣨��λ�֣�
�����ÿո������������ʾ����
1 800 50
2 815 30
3 830 25
4 835 20
5 845 15
6 900 10
7 920 5
���е���ʱ��Ϊ���һ����ҵ����ϵͳ��ʱ�䣡
�����ҵ�ţ������ڴ��ʱ�䣡ÿ�����һ����ҵ��Ϣ��
1 920 90
2 930 24
3 1000 60

*/
/*writer:���ʾ�(�����ο�)�����кõĿ����ͽ���,��ӭ�뱾��̽��.furenjun@sohu.com*/
# include <iostream.h>
# include <stdio.h>
# include <stdlib.h>
# include <iomanip.h>
# include <string.h>

typedef struct  
{
	char Jname[6];
	int  Etime;
	int  Rtime;
	int  Finish;
} node;
 static int n=7;
 node node1[20];
 
 int init_pro()
 {
	 FILE  *fp;
	 char filename[30];
	 cout<<"please input file name(��job.txt��job2.txt):>";
	 cin>>filename;

	 
	 if((fp=fopen(filename,"r+"))==NULL)
	 {
		 cout<<"file can not open!"<<endl;
		 exit(0);
	 }
	 int a[100];
     int i=0,m=0;
	 
	 while(!feof(fp))
	 {
		 fscanf(fp,"%d",&m);
		 a[i++]=m;
	 }
	 int w=i/3;
	 fclose(fp);
	 char name[6];
	 name[0]='j';
     name[1]='o';
	 name[2]='b';
	 name[3]=49;
     name[4]='\0';
	
	 int pos=0;
	 for(i=0;i<n;i++)
	 {
		 
		 name[3]=48+a[pos];
		 
		 strcpy(node1[i].Jname,name);
		 //cout<<setw(6)<<node1[i].Jname;
		 node1[i].Etime=a[pos+1];
		 node1[i].Rtime=a[pos+2];
		 node1[i].Finish=0;
		 pos+=3;
	 }

	 return w;
    
 }

 int timetran( int num)
 {
	 int m=0,n1=0;
	 m=num/100;
	 n1=num%100;
	 m=m*60;
	 n1+=m;
	 return n1;
 }

 int timetran2(int num2)
 {
	 
	 int m2=0,n2=0;
	 m2=num2/60;
	 n2=num2%60;
	 m2=m2*100;
	 n2+=m2;
	 return n2;
 }

 void timetran3(int num3)
 {
	 
	 int m2=0,n2=0;
	 m2=num3/60;
	 n2=num3%60;
	 cout<<" ("<<m2<<":";
	 if(n2<10)
     cout<<"0"<<n2<<")"<<endl;
	 else
	 cout<<n2<<")"<<endl;
	 return ;
 }

 void show(   )
 {
	 cout<<setw(8)<<"��ҵ��"<<setw(10)<<"����ʱ��"<<setw(12)<<"������ʱ��"<<"  "<<"���н������"<<endl;

	 for(int j=0;j<n;j++)
	 {
		 cout<<setw(8)<<node1[j].Jname;
		 cout<<setw(8)<<node1[j].Etime;
		 cout<<setw(8)<<node1[j].Rtime;
		 cout<<setw(12)<<node1[j].Finish;
         cout<<endl;
	 }
	 return;
 }

void show2( )
{
    cout<<setw(8)<<"��ҵ��"<<setw(10)<<"����ʱ��"<<setw(12)<<"������ʱ��"<<"  "<<"���н������"<<endl;

	 for(int j=0;j<n;j++)
	 {
		 cout<<setw(8)<<node1[j].Jname;
		 cout<<setw(8)<<timetran(node1[j].Etime);
		 cout<<setw(8)<<node1[j].Rtime;
		 cout<<setw(12)<<node1[j].Finish;
		 node1[j].Etime=timetran(node1[j].Etime);   //ע��Ҫ�ڴ˴��޸Ľ���ʱ���Է�����ʾ��ֵ;
         cout<<endl;
	 }
	 return ;
}


void proattemper(int n3,int runtime)
{
	for(int j=0;j<n3;j++)
	{
		float dev,max;
		int flag;
		for(int i=0;i<n3;i++)
		{
		if(node1[i].Finish ==0)
		{
		dev=float(node1[i].Rtime);
	     max=float(runtime-node1[i].Etime)/dev;
		// cout<<"tempmax"<<float(runtime-node1[i].Etime)<<"/"<<dev;
		flag=i;
		break;
		}
		}

		for(i=0;i<n3;i++)
		{
		  if(node1[i].Finish ==0)
		  {
		  dev=float(node1[i].Rtime);
		  if( max<(float(runtime-node1[i].Etime)/dev))
		  {
			 max=float(runtime-node1[i].Etime)/dev;
			  flag=i;
			  
		  }
		 }
		}

        node1[flag].Finish =1;
		cout<<setw(8)<<node1[flag].Jname <<setw(8)<<timetran2(runtime);  timetran3(runtime); 
		//	<<setw(8)<<"flag="<<flag+1<<setw(8)<<"max="<<max<<" "<<float(runtime-node1[flag].Etime)<<"/"<<dev;
		runtime=runtime+node1[flag].Rtime ;
        cout<<endl;
	  //	show( );
	}
}





 int main(void)
 {
       n=init_pro();
	   cout<<"���ļ�����ĸ�����״̬:"<<endl;
       show( );
	   cout<<"����ʱ��ת���ɷ��Ӻ�����̵�״̬:"<<endl;

	   show2();  //�Ƚ�������ʱ�Ӻͷ�����ʾ��ֵͳһת��Ϊ������,��д�������.
	   int runtime;
	   runtime=node1[n-1].Etime ;
       cout<<setw(8)<<"��ҵ��"<<setw(10)<<"����ʱ��"<<setw(12)<<endl;
       proattemper(n,runtime);

	   return 0;
 }

