/***************************************************************************************
6��2��
ģ��ɱ����������֮�����������㷨
1�� ���룺
��1�������������ļ���ÿһ�а�����������ʼ��ַ�������������������ʾ�����ÿո�
�ָ�������
��2�������¹黹�Ŀ�������ʼ��ַ�ͳ��ȡ�
������һ��ʾ�⣺
15 23
48 20
98 12
2�� ����Ҫ��
��������ʱ��������ʾ����������������ļ����ļ�������������һ���ļ����󣬳��򽫶�
����ļ��е��й����ݡ�
����ʾ���������¹黹����������ʼ��ַ�ͳ��ȣ������������������󣬰��ջ����㷨���
�������Ļ��չ�����Ҫ���Ǹ��ֿ��ܵ��������
3�� ���Ҫ��
����µĿ�������ÿһ�а�����������ʼ��ַ���������
4�� �ļ���Լ��
 �ύ��Դ�������֣�sourceXXX.c����sourceXXX.cpp��������������ȷ����
 �����ļ����֣������û�ָ��
 ��������resultXXX.txt��
���У�XXXΪ�˺š�
5�� ����˵�������Խ�ʦ������׼����һ���ļ�����ʽΪ*.txt��������Ϊÿ���������ָ��
һ��������Ϊ�����ļ�������������Ӽ�������ָ���ļ����ļ����������鿴������������
***************************************************************************************/
/*writer:������ ���ʾ�(�����ο�)�����кõĿ����ͽ���,��ӭ�뱾��̽��.furenjun@sohu.com*/
# include <iostream.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <iomanip.h>

typedef struct 
{
	int start;
	int len;
	int end;
}node;
node fre[20];
static int len=0;

int readdata()
{
	FILE *fp;
	/*
	char filename[20];
	cout<<"please input file name(��freearea.txt):>";
	cin>>filename;
     */
	if((fp=fopen("freearea.txt","r+"))==NULL)
	{
		cout<<"sorry! file can not open!"<<endl;
		exit(0);
	}
	int a[100],m=0,i=0;
	while(!feof(fp))
	{

		fscanf(fp,"%d",&m);
		a[i++]=m;
	}
	m=i/2;
	cout<<"������������Ϊ:"<<m<<endl;
	int w=0;
	for(int j=0;j<m;j++)
	{
		fre[j].start=a[w+0];
		fre[j].len=a[w+1];
		fre[j].end=fre[j].start+fre[j].len;
		w+=2;
	}
    return m;
}

void show( )
{
   cout<<"�������������"<<endl;
   cout<<setw(12)<<"��ʼ��ַ"<<setw(6)<<"����"<<setw(10)<<"������ַ"<<endl;
   for(int i=0;i<len;i++)
   {
	   cout<<setw(10)<<fre[i].start<<setw(7)<<fre[i].len<<setw(9)<<fre[i].end<<endl;
   }
   return ;
}

void reclaim()
{
	cout<<"�������¹黹����������ʼ��ַ�ͳ���"<<endl;
	cout<<"��ʼ��ַ:";
	int startpos;
    cin>>startpos;
    cout<<"��    ��:";
	int len2;
    cin>>len2;
	int end2=startpos+len2;
	int maxend=fre[0].end;

	for(int y=0;y<len;y++)
	{
		if(maxend<fre[y].end)
			maxend=fre[y].end;
	}

    for( y=0;y<len;y++)      //����������ݵ���Ч��                  
	{
		if((startpos<fre[0].start)&&(end2>fre[0].start))
		{
			cout<<endl<<"������Ļ��տ��������ȷǷ�!"<<endl<<endl;
			return;
		}
        if(startpos>=maxend)
			break;
		if((startpos>=fre[y].start)&&(startpos<fre[y].end))
		{
			cout<<endl<<"������Ļ��տ�������ʼ��ַ�Ƿ�!"<<endl<<endl;
			return;
		}
	}
	int t=0;
	for(y=0;y<len;y++)
	{
		if(startpos>=fre[y].end)
		{
			 t=y;
		}
	}
   
        if(startpos<maxend)     //������������δ��ַ,��ȻӦ�ò��������.
		{
        if((startpos>=fre[t].end)&&(end2>fre[t+1].start))   
		{
			cout<<endl<<"������Ļ��տ��������ȷǷ�!"<<endl<<endl;
			return;
		}
		}
	
	int shali=0,xiali=0;   //�������Ƿ�������,���ٻ���û��������;
	int s=65535,x=65535;
	for(int j=0;j<len;j++)
	{
		if(fre[j].start==end2)
		{
			x=j;
		}
		if(fre[j].end==startpos)
		{
			s=j;
		}
	}
	if(x==65535&&s==65535)
	{
		cout<<"������������;"<<endl;
	
		fre[len].start =startpos;
		fre[len].len =len2;
		fre[len].end =end2;
		len+=1;
	}
	if(x==65535&&s!=65535)
	{  
		cout<<"��������;"<<endl;
        fre[s].len+=len2;        //�޸�ԭ��Ľ�����ַ�ͳ���;
		fre[s].end+=len2;
	}
	if(x!=65535&&s==65535)
	{
		cout<<"��������;"<<endl;
		fre[x].start=startpos;  //�޸�ԭ�����ʼ��ַ�ͳ���;
		fre[x].len+=len2;
		
	}
	if(s!=65535&&x!=65535)
	{
        cout<<"����������;"<<endl;
		fre[s].len+=len2;        //�޸�ԭ��ĳ���;
		fre[s].len+=fre[x].len;  
		fre[s].end =fre[x].end;  //�޸�ԭ��Ľ�����ַ;
		fre[x].start =0;
		fre[x].len =0;
		fre[x].end =0;
	}
    
	node temp;                 //�Կ��������е����ݽ���ð������
    int i,ok;
	for(i=1;i<len;i++)
	{
		ok=1;
		for(j=0;j<len-i;j++)
		{
			if(fre[j].start>fre[j+1].start  )
			{
				temp=fre[j] ;
				fre[j] =fre[j+1];
				fre[j+1]=temp;
				ok=0;
			}
			
		}
		if(ok)              //ע��if(ok)���Ӧд�ڴ�ѭ����.
				break;
	}
	return ;
}

int outres()
{
	FILE *fp;
	int flag=1;
	if((fp=fopen("result3.txt","w+"))==NULL)
	{
		cout<<"Sorry! file can not open! "<<endl;
		flag=0;
		exit(0);
	}
	fprintf(fp,"%s","�������������");
    fprintf(fp,"%c",'\n');
	fprintf(fp,"%12s%6s%10s","��ʼ��ַ","����","������ַ");
	fprintf(fp,"%c",'\n');
	for(int i=0;i<len;i++)
	{
		fprintf(fp,"%10d%7d%9d",fre[i].start ,fre[i].len ,fre[i].end );
		fprintf(fp,"%c",'\n');
	}
	fclose(fp);
	return flag;
}

void main()
{
	len=readdata();   
    show( );
	int run=1;
	while(run)
	{
	reclaim();
	show( );
	int bj=0;
    bj=outres();
	if(bj==1)
	cout<<"Result have saved to result3.txt."<<endl;
	cout<<"Are you  continue?(Y/N)";
	char c[2],b[2]={"Y"};
	cin>>c;
    strcpy(c,strupr(c)) ;
	if(strcmp(c,"Y")!=0)
		run=0;
	else
		run=1;
	}
}

   







