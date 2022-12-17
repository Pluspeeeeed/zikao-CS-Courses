#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define null 0
#define len sizeof(struct cidaohao)

struct cidaohao
{
	struct cidaohao *pre;
	int num;
	struct cidaohao *next;
};

FCFS(array)
int array[50];
{int i,j,sum=0;
 printf("\nFCFS : ");
 for(i=1;array[i]!=-1;i++)
 {
	printf(" %d ",array[i]);
 }
 i=0;
 for(i=0,j=1;array[j]!=-1;i++,j++)
 {
	if(array[i]>array[j])   sum+=(array[i]-array[j]);
	else sum+=(array[j]-array[i]);
 }
 return(sum);
}

SSTF(head,now)
struct cidaohao *head;
int now;
{struct cidaohao *p,*lp,*rp;
 int sum=0,front,behind;
 p=head;
 printf("\nSSTF :");
 while(p->num!=now) p=p->next;/*ȷ��now�������е�λ��*/
 lp=p->pre;
 rp=p->next;
    do
	{
	    if(p->next!=null&&p->pre!=null)
 	    {	front=p->num-lp->num;
		behind=rp->num-p->num;
		if(front>=behind)
		{
			sum+=behind;
			p=rp;
			printf(" %d ",p->num);
			rp=p->next;
		}
		else
		{
			sum+=front;
			p=lp;
			printf(" %d ",p->num);
			lp=p->pre;
		}
	    }
	    else
		{
		    	if(p->next==null)
	  		  	{    while(lp->num!=0)
					{
					 sum+=p->num-lp->num;
					 p=lp;
					 printf(" %d ",p->num);
					 lp=p->pre;
					}
			   	     return(sum);
				}
			if(p->pre==null)
				{
				     while(rp->num!=0)
					{
					 sum+=rp->num-p->num;
					 p=rp;
					 printf(" %d ",p->num);
					 rp=p->next;
					}
			 	     return(sum);
				}
		}
	 }while(p->next!=null||p->pre!=null);
}



SCAN(head,n,m)
struct cidaohao *head;
int n,m;
{struct cidaohao *p,*pp;
 int sum=0;
 printf("\nSCAN : ");
 p=head;
 while(p->num!=m)   p=p->next;/*ȷ��m��λ��*/
 pp=p;
 if(n<m)
	{while(pp->next!=null)
		{
			sum+=pp->next->num-pp->num;
			pp=pp->next;
			printf(" %d ",pp->num);
		}
	 sum+=pp->num-p->pre->num;
	 pp=p->pre;
	 if(pp->num==0) return(sum);
	 else
 	   {while(pp->pre!=null)
		{
			printf(" %d ",pp->num);
			sum+=pp->num-pp->pre->num;
			pp=pp->pre;			
		}
	    printf(" %d ",pp->num);
            return(sum);
	   }
	}
 else
       {
	  while(pp->pre!=null)
		{
			sum+=pp->num-pp->pre->num;
			pp=pp->pre;
			printf(" %d ",pp->num);
		}
	  sum+=p->next->num-pp->num;
	  pp=p->next;
	  if(pp->num==0) return(sum);
 	  else
		{while(pp->next!=null)
		  {
			printf(" %d ",pp->num);
			sum+=pp->next->num-pp->num;
			pp=pp->next;
	          }
	         printf(" %d ",pp->num);
	         return(sum);
 	        }
	}
}




main()
{

	FILE *fp;
	char pt;
	char str[10];
	int cidao[100],i,j=1,count1=0,count2=0,count3=0,last,space=0;
	struct cidaohao *p1,*p2,*new,*head;/*���ڽ�������ı���*/
	struct cidaohao *p,*lp,*rp;
 	for(i=0;i<50;i++) cidao[i]=-1;
	i=0;
	fp=fopen("cipan.txt","r+");/*��fpָ���ļ�*/
	if(fp==NULL)
	{
		printf("Cann't open this file ");
		exit(0);
	}
	printf("\nPlease input cidaohao now : ");
	scanf("%d",&cidao[0]);
	while((pt=fgetc(fp))!=EOF)/*�������ַ���ת�������͡���ʼ*/
	{
		if(pt>='0'&&pt<='9')
		{
			str[i]=pt;i++;
			space=0;
		}
		else
		{
			if(pt==' '||pt=='\n')
			{if(space==1) break;
			 else
			  {str[i]='\0';
			   cidao[j]=atoi(str);
			   if(pt=='\n') break;
			   else
				{
					space=1;
					j++;
			   		i=0;
			   	}
			  }
			}
		}
	 }/*����*/
	if(pt==EOF) {str[i]='\0';cidao[j]=atoi(str);}
	fclose(fp);
	i=0;
	count1=FCFS(cidao);/*FCFS���ȵ��ƶ�����*/
	printf("\nThe Total : %d \n",count1);
	p1=p2=head=(struct cidaohao* )malloc(len);/*��ʼ����˫����*/
	p1->pre=null;
	p1->num=cidao[0];
	p1->next=null;
	i=1;
	while(cidao[i]!=-1)
	{  if(cidao[i]<head->num)/*����ͷ���*/
		{
			p1=(struct cidaohao *)malloc(len);
			p1->next=head;
			p1->pre=null;
			p1->num=cidao[i];
			head->pre=p1;
			head=p1;
		}
	    else
		{
			while(p1->next!=null&&p1->num<=cidao[i])/*��������λ��*/
			{       p2=p1;
				p1=p1->next;
			}
			if (p1->num>cidao[i])/*�����м�����*/
			{
				new=(struct cidaohao*)malloc(len);
				new->num=cidao[i];
				new->next=p1;
				new->pre=p2;
				p1->pre=new;
				p2->next=new;
			}
			else
				{/*����β��*/
				 	new=(struct cidaohao*)malloc(len);
					new->num=cidao[i];
					new->next=null;
					new->pre=p1;
					p1->next=new;
				}
			p1=head;/*ʼ�ձ�֤���������p1ָ��ͷ���*/
		}
		i++;/*��ȡ��һ��cidao[i]*/
	}
	count2=SSTF(head,cidao[0]);
	printf("\nThe Total : %d ",count2);
	printf("\n\nPleast input last cipanhao : ");
	scanf("%d",&last);
	count3=SCAN(head,last,cidao[0]);
	printf("\nThe Total : %d \n",count3);
}
