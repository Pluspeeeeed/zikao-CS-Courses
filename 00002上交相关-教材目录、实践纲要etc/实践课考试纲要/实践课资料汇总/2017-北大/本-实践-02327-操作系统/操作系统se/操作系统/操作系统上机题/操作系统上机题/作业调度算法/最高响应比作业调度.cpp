/* 6���ĺ��������Ŀ���𰸣�����

6���ĺ�����Ŀ���
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
*/
#include<string.h>
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
struct job{
	int jnum;
	int arrive;
	int need;
	double bi;
};
int count=0;
void main()
{
	job jobs[10];
	FILE *fp;
	if((fp=fopen("job.txt","r+"))==NULL)
	{
		cout<<"file can not open!"<<endl;
	}
	else
	{
		int i=0;
		while(!feof(fp))
		{
			fscanf(fp,"%d%d%d",&jobs[i].jnum,&jobs[i].arrive,&jobs[i].need);
			i++;
			count++;
		}
		fseek(fp,-1,SEEK_END);
	    char c;
	    fscanf(fp,"%c",&c);
	    if((c=='\n')||(c=='\n'))
		{
	    	count--;
		}
		fclose(fp);
	}
	for(int i=0;i<count;i++)
	{
		jobs[i].bi=(jobs[count-1].arrive-jobs[i].arrive)/jobs[i].need;
	}
	for(i=0;i<count;i++)
	{
		cout<<jobs[i].jnum<<" "<<jobs[i].arrive<<" "<<jobs[i].need<<" "<<jobs[i].bi<<endl;
	}

}