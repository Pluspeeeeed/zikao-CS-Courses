#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define null 0
#define len sizeof(struct page)

struct page
{ int num;
  int tag;
  struct page *next;
};


struct page *create(int n)    /*建立分配的内存空间，并初始化，返回头结点*/
{int count=1;
 struct page *p1,*p2,*head;
 head=p2=p1=(struct page *)malloc(len);
 p1->tag=-1;p1->num=-1;
 while(count<n)
 {count++;
  p1=(struct page *)malloc(len);
  p1->tag=-1;p1->num=-1;
  p2->next=p1;
  p2=p1;
 }
 p2->next=null;
 return(head);
}


void FIFO(array,n)
int array[],n;
{int *p;
 struct page *cp,*dp,*head,*new;
 int count=0;
 head=create(n);
 p=array;
 while(*p!=-1)
{ cp=dp=head;
  for(;cp->num!=*p&&cp->next!=null;) cp=cp->next;
  if (cp->num==*p) printf(" ! " );
  else
      { count++;
        cp=head;
        for(;cp->tag!=-1&&cp->next!=null;) cp=cp->next;
        if(cp->tag==-1)
 	  {cp->num=*p;
           cp->tag=0;
	   printf(" * ");
 	  }
        else
          {new=(struct page*)malloc(len);
           new->num=*p;
 	   new->tag=0;
	   new->next=null;
           cp->next=new;
           head=head->next;
	   printf(" %d ",dp->num);
	   free(dp);
          }
      }
  p++;
}
printf("\nQueye Zongshu : %d \n",count);
}


void LRU(array,n)
int array[],n;
{int count=0,*p=array;
 struct page *head,*cp,*dp,*rp,*new,*endp;
 head=create(n);
 while(*p!=-1)
  {cp=dp=rp=endp=head;
   for(;endp->next!=null;) endp=endp->next;
   for(;cp->num!=*p&&cp->next!=null;) 
     {rp=cp;cp=cp->next;}
   if(cp->num==*p)
     {printf(" ! ");
      if(cp->next!=null)
       {if(cp!=head)
      	rp->next=cp->next; 	 
        else head=head->next; 
       }
      endp->next=cp;
      cp->next=null;
     }
   else
       {count++;
        cp=rp=head;
        for(;cp->tag!=-1&&cp->next!=null;) cp=cp->next;
        if(cp->tag==-1)
           {printf(" * "); 
	    cp->num=*p;
 	    cp->tag=0;
            }
 	else
	    {new=(struct page *)malloc(len);
	     new->num=*p;
	     new->tag=0;
	     new->next=null;
             cp->next=new;
             dp=head;
	     head=head->next;
	     printf(" %d ",dp->num);
	     free(dp);
            }
        }
      p++;
    }
   printf("\nQueye Zongshu : %d \n",count);
}


OPT(array,n)
int array[],n;
{int *p,*q,count=0,i;
 struct page *head,*cp,*dp,*new;
 p=array;
 head=create(n);
 while(*p!=-1)
  { cp=head;
    for(;cp->num!=*p&&cp->next!=null;) cp=cp->next;
     if(cp->num!=*p)
     { count++;
        cp=head;
        for(;cp->tag!=-1&&cp->next!=null;) cp=cp->next;
        if(cp->tag==-1)
           {printf(" * ");
  	    cp->num=*p;
            cp->tag=0;
           }
        else 
		{ i=1;q=p;q++;cp=head;
		  while(*q!=-1&&i<n)
   		     { for(;*q!=cp->num&&cp->next!=null;) cp=cp->next;
  		       if(*q==cp->num)
			  {cp->tag=1;
     			   i++;
			  }
 		       q++;cp=head;
		     }
		  if(i==n)
                    { 
		      for(;cp->tag!=0;) cp=cp->next;
		      printf(" %d ",cp->num);
		      cp->num=*p;
		    }
                  else
                    { cp=head;
 		      for(;cp->tag!=0;) cp=cp->next;
		      if(cp==head)
			{ for(;cp->next!=null;) cp=cp->next;
                          new=(struct page *)malloc(len);
			  new->num=*p;
			  new->tag=0;
			  new->next=null;
 			  cp->next=new;
			  dp=head;
			  head=head->next;
			  printf(" %d ",dp->num);
			  free(dp);
 			}
		      else
			 { printf(" %d ",cp->num);
			   cp->num=*p;
			 }
		     }
		 cp=head;
  		 for(;cp->next!=null;) {cp->tag=0;cp=cp->next;}
		 cp->tag=0;
                }
  	}
      else printf(" ! ");
      p++;
  }
 printf("\nQueye Zongshu : %d \n",count);
}

main()
{
	FILE *fp;
	char pt;
	char str[10];
	int i,j=0;
	int page[50],space=0;
	for(i=0;i<50;i++)
	page[i]=-1;
	fp=fopen("page.txt","r+");
	if(fp==NULL)
	{
		printf("Cann't open the file\n");
		exit(0);
        }
	i=0;
	while((pt=fgetc(fp))!=EOF)/*将数字字符串转化成整型—开始*/
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
			   page[j]=atoi(str);
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
	 }/*结束*/
	if(pt==EOF) {str[i]='\0';page[j]=atoi(str);}
	i=0;
	while(page[i]!=-1) {printf(" %d ",page[i]);i++;}
	fclose(fp);
printf("\n");
printf(" ! : mean no moved \n * : mean have free space \n\n");
printf("FIFO ");
FIFO(page,3);
printf("\nLRU ");
LRU(page,3);
printf("\nOPT ");
OPT(page,3);
}
