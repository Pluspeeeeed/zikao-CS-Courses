/***********************************************************************************************
6��1������:
ģ������λʾͼ�������ڴ����ҳ��ķ���
1�� ���룺
��λʾͼ���ļ����ڱ�ʾ�ڴ����ҳ�棬��0����ʾ���У���1����ʾ���䣩��ɡ�ÿ��32������16�С�
�����ļ����������У�ÿ����λʾͼ��һ�У��á�0����1���ַ����������пո񣩱�ʾÿһ�и�λ��ֵ��
input.txt��һ�������ļ���ʽ��ʾ��
2�� ����Ҫ��
��������ʱ��������ʾ��������λʾͼ�ļ����ļ��������������ļ����󣬳��򽫶�����ļ��е��й����ݡ�
����ʾ�������������ҳ���������������һ��ҳ�����N�󣬳���ִ�У�ѡ����Է��������
Ҫ�������N��ҳ�档�������ڴ��ʱ������λʾͼ�д�ͷ����Ϊ0����λ�������Ϊ1����
Ҫ����һЩ�߽����⡣
3�� ���Ҫ��
��1����ʾ���η���ĵ�1��ҳ����λʾͼ�е��кź��кš�
��2����ʾ������ɺ��µ�λʾͼ���֡�
����ļ���ʽ��
��һ�����������ʼλ�õ����кţ��к���ǰ���к��ں��Կո����
�ڶ��п�ʼ���������ļ��ĸ�ʽ������º��λʾͼ
��������г���Ҫ������ݲ�Ҫ�����κ���������
4�� �ļ���Լ��
�ύ��Դ�������֣�source.c����source.cpp��������������ȷ����
�����ļ����֣������û�ָ��
��������result.txt��
5�� ����˵�������Խ�ʦ������׼����һ������ļ�����ʽ��ǰ����������Ϊÿ���������ָ��
һ��������Ϊ�����ļ�������������Ӽ�������ָ���ļ����ļ����������鿴������������
***************************************************************************************/
/*writer:������ ���ʾ�(�����ο�)�����кõĿ����ͽ���,��ӭ�뱾��̽��.furenjun@sohu.com*/
# include <iostream.h>
# include <stdio.h>
# include <stdlib.h>
# include <iomanip.h>
# include <string.h>
static int  a[560];
static int i=0;       //����ͳ�ƶ��������е����ݸ���;   
int  readdata()
{
	FILE *fp;
	char filename[20];
	cout<<"please input file name(��data.txt):>";
	cin>>filename;
	if((fp=fopen(filename,"r+"))==NULL)
	{
		cout<<"sorry!file can not open! "<<endl;
		exit(0);
	}
	char c;
	int  count=0;
	while(!feof(fp))
	{
		c=fgetc(fp);
		if(c=='0')
			++count;
		if(c=='0'||c=='1')
        a[i++]=c-48;
	}
	fclose(fp);
     return  count;
}
void show()   //��ʾλʾͼ�е�����;
{
	for(int j=0;j<i;j++)
	{
		cout<<setw(1)<<a[j];
		if((j+1)%32==0)
			cout<<endl;
	}
	cout<<endl<<"�ܹ��������ݸ���Ϊ:"<<i<<endl;
	return  ;

}


void findpos(int num)         //�ҵ���һ������Ҫ���λʾͼ�ռ�,������Ӧ����������ļ�.
{
	int pos,j,m,count; 
    pos=0;
	int flag=1;
    int start=0;
	for(j=0;j<i;j++)
	{  
		flag=1;
		start=j;
		count=1;
		for(m=j;m<i;m++)
		{
			if(a[m]==1)
			break;
			if(count>=num)
			{
				flag=0;
				break;
			}
			++count;
		}
		if(flag==0)
			break;

	}
	    if(count<num)
		cout<<"soory!Could not fulfil your request!"<<endl;
		else
		if(count>=num)
		{
			FILE *fp;
	        if((fp=fopen("result2.txt","w+"))==NULL)
			{
		     cout<<"sorry!file can not open! "<<endl;
		     exit(0);
			}
			cout<<"found!"<<endl;
			int m=(start+1)/32;
			int n=(start+1)%32;
			cout<<"����������ռ���ʼλ�õ���,�к�(�±����1��ʼ)�ֱ�Ϊ:"<<m+1<<"  "<<n<<endl;
			char b[60]={"����������ռ���ʼλ�õ���,�к�(�±����1��ʼ)�ֱ�Ϊ:"};
			char c[20];
            strcpy(c,"������λʾͼΪ:");

			fprintf(fp,"%s%6d,%6d,%c",b,m+1,n,'\n');
			fprintf(fp,"%c",'\n');
            fprintf(fp,"%s%c",c,'\n');
			for(j=0;j<num;j++)  //�޸�λʾͼֵ;
				a[start++]=1;
			cout<<"������λʾͼΪ:"<<endl;
		   show();
           for(j=0;j<i;j++) 
		   {
			   fprintf(fp,"%d",a[j]);
			   if((j+1)%32==0)
			   {
                   fprintf(fp,"%c",'\n');
			   }
		   }
		   fclose(fp);
		}
		return;
}

void main()
{
 int total=0;

  total=readdata();
  cout<<"�ܿ��п���Ϊ:"<<total<<endl;
  show();
  int judge=1;
  while (judge)
  {
  cout<<"������������ڴ�����:>";
  int num;
  cin>>num;
  if(num==0)
  {
	  cout<<"Sorry!,your input error!please input again."<<endl;
      judge=1;
  }
  else
  {
  if(num>total)
  {
	  cout<<"Sorry,can not fulfil your quest.please input again."<<endl;
	  judge=1;
  }
  else
  {
   judge=0;   
   findpos(num);
  }
  }
  }
}






