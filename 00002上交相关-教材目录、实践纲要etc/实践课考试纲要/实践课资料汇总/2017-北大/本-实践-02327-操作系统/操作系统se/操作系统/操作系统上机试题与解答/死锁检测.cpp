/*ģ����������㷨

1�� ���룺
����Դ������ļ���ÿһ�а�����Դ��š����̱���������������ʾ�����ÿո�ָ���������¼��Դ��������ĸ����̡�
�����̵ȴ����ļ���ÿһ�а������̱�š���Դ����������������ʾ�����ÿո�ָ���������¼�������ڵȴ��ĸ���Դ��
������һ��ʾ����
��Դ�����
1 1
2 2
3 3
���̵ȴ���
1 2
2 3
3 1
2�� ����Ҫ��
��������ʱ��������ʾ����������Դ������ļ����ļ�������������ʾ����������̵ȴ����ļ����ļ���������
���������ļ����󣬳��򽫶��������ļ��е��й����ݣ���������������㷨���м�⡣
3�� ���Ҫ��
��һ������������������ �� ��������
�ڶ����������ѭ���ȴ����У������̱�ţ��������������
4�� �ļ���Լ��
�ύ��Դ�������֣�sourceXXX.c����sourceXXX.cpp��������������ȷ����
�����ļ����֣������û�ָ��
��������resultXXX.txt��
���У�XXXΪ�˺š�
5�� ��������㷨������һ����Pj����һ���ѱ���������ռ�õ���Դriʱ������������⡣����㷨ͨ���������ҽ��̵ȴ������Դ�������ȷ������Pj����Դri�������Ƿ����γɻ�·�����ǣ���ȷ������������
6�� ����˵�������Խ�ʦ������׼����һ���ļ�����ʽΪ*.txt��������Ϊÿ���������ָ��һ��������Ϊ�����ļ�������������Ӽ�������ָ���ļ����ļ����������鿴������������
***********************************************************************************************/
/*writer:������ ���ʾ�(�����ο�)�����кõĿ����ͽ���,��ӭ�뱾��̽��.furenjun@sohu.com*/
#include<iostream.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip.h>

typedef struct {
int proc;
int resource;
}node;
node allocate[10];
node request[10];


int readrfile(){
char name[20];
FILE *fp;
int m,i,j;
cout<<"��������Դ������ļ���(alloc.txt):";
//cin>>name;

cout<<endl;
if((fp=fopen("test.txt","r+"))==NULL){

cout<<"�ļ����ܴ�1!!!";exit(0);
}
i=0;
while(!feof(fp)){
fscanf(fp,"%d",&m);
allocate[i].resource=m;
fscanf(fp,"%d",&m);
allocate[i].proc=m;
i++;
}
cout<<"��Դ���"<<setw(10)<<"���̱��"<<endl;
for(j=0;j<i;j++){
cout<<setw(4)<<allocate[j].resource<<setw(12)<<allocate[j].proc<<endl;

}
fclose(fp);
return i;
}


int readqfile(){
char name[20];
FILE *fp;
int m,i,j;
cout<<"��������Դ�ȴ����ļ���(req.txt):";
//cin>>name;
cout<<endl;
//if((fp=fopen(name,"r+"))==NULL){
if((fp=fopen("waitfor.txt","r+"))==NULL){

cout<<"�ļ����ܴ�!!!";exit(0);
}
i=0;
while(!feof(fp)){
fscanf(fp,"%d",&m);
request[i].proc=m;
fscanf(fp,"%d",&m);
request[i].resource=m;

i++;
}
cout<<"���̱��"<<setw(10)<<"��Դ���"<<endl;
for(j=0;j<i;j++){
cout<<setw(4)<<request[j].proc<<setw(12)<<request[j].resource<<endl;

}
fclose(fp);
return i;
}


int  lockcheck(node alloc[],node req[],int totalnum,int temp)
{
   //cout<<"temp"<<temp<<endl;
   int  i,j,k,x,w,a[20],z;
   j=0; k=0;
   a[k++]=req[temp].proc;
   int t;
   t=temp;
   for(i=0;i<=temp;i++)  //ע��˴��ı���Ҫ���б���;
   {
    for(z=0;z<totalnum;z++) 
	   {
		   if((req[t].resource==alloc[z].resource)) //�����Դ����������Ӧ���̺Ŵ�������.
		   {    //tΪtemp�ı���,����һ���仯����.
			   a[k++]=alloc[z].proc;  
			   //cout<<"ok1"<<endl;
		       j=z; 
			   break;//�޸�����Ҫ�õ���������Դ���±�
		   }
	   }
	   int flag=0; //�ڴ˴������Ƿ�ֹ������ֲ����޸�t ��ֵ�����,������һ��ѭ��������ʹ��δ�ı��tֵ,�Ӷ�����.
       for(w=0;w<=temp;w++)             //ÿ�ζ���Դ�ȴ���ļ�����Ϊ������Դ�ȴ���Ľ�������.
	   {

		   if((alloc[j].proc ==req[w].proc ))  //�����Դ������е���Դ�ŵ��ڽ��̵ȴ���
			                                         //����Դ��,������Ӧ�Ľ��̺Ž�����̶���.
		   {
			 
			   {
				flag=1;
		        t=w;  //�޸�t��ָʾ���±�ֵ.
				break;
			   }
		   }
	   }
	   if(flag==0)
		   break;

   }


 int flag=0,k2=0;
     x=a[0];
      for( i=1;i<k;i++)  //�����̶������Ƿ���ڻ�
	  {
		  flag=0;
			  if(x==a[i])
			  {
				  flag=1;
				  k2=i;
				  break;
			  }
	  }
     

    if(flag==1)
	  {
	     cout<<"  �˽��̶���������!"<<endl;
	  }
   	 if(flag==0)
	 { 
	     cout<<"  û����!"<<endl;
	 }

    //�����д���ļ�:

   FILE *fp;
   if((fp=fopen("result.txt","ab+"))==NULL)
   {
	   cout<<"soory! can not open file! "<<endl;
	   exit(0);
   }

   char c='\n';
   fputc(c,fp);
   char s[20]=" the number\n";
   fputs(s,fp);
    // cout<<endl<<"k="<<k<<endl;
     cout<<"  �ý��̶���Ϊ:"<<endl;
     for(i=0;i<=k2;i++)
	 {
		 cout<<setw(6)<<a[i];
		 fprintf(fp,"%5d",a[i]);

	 }
     fprintf(fp,"%c",'\n');
     fclose(fp)    ;

	
    
     return 0;
}

void main(){
int n;
n=readrfile();
cout<<endl<<n<<endl;
int m=readqfile();
cout<<endl<<m<<endl;
for(int i=0;i<m;i++)
{
	cout<<endl<<"  ��"<<i+1<<"���������ʱ";
    lockcheck ( allocate,request,m,i);
	
}
cout<<endl;
return ;
}
