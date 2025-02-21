#ifndef FILE_SIMULATOR
#define FILE_SIMULATOR

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef int errnum;

const char * errstr[]={
 "Everything's ok,this message should never be displayed.",
 "Can not find the file or directory!",
 "No such operation!",
 "Arguments error!"
};

typedef enum{DIR,PLAIN,FILE_BLOCK} node_type;

typedef struct _privilege{
 int level;
}privilege;

typedef struct _node{
 struct _node *next;
 struct _node*sub;
}node;

/************file or directory node文件和目录结点*****/
typedef struct _dnode{
 struct _dnode *next;
 struct _dnode *sub;
 node_type type;
 char name[8];
 privilege pri;
 int size;
}dnode;

dnode *root;
dnode *cur_dir;

/********stack strcture栈结点结构********/
typedef struct _stack_node{
 dnode *elem;
 struct _stack_node *next;
}stack_node;

struct _stack{
 stack_node *top;
}stack;
#endif
//#include "filesys.h"

extern errnum init_chain();
extern errnum free_tree(dnode*);
extern errnum ft_pwd();
extern errnum ft_lsall();
extern errnum ft_cd(char*);
extern errnum ft_ls();
extern errnum ft_rm(char*);
extern errnum ft_rmdir(char*);
extern errnum ft_mkdir(char*);
extern errnum ft_touch(char*);
extern errnum ft_ren(char*,char*);
extern errnum ft_cp(char*,char*);
extern errnum ft_cpdir(char*,char*);

extern dnode* copy_node(dnode*,dnode*);
extern dnode* copy_dnode(dnode*);
void push(dnode*);
dnode*pop();
dnode*top();
void message_out(char*);
void error_out(errnum i);

void message_out(char *message){
 printf("%s",message);
}

void error_out(errnum i){
 printf("%s\n",errstr[i]);
}

/********push压栈********/
void push(dnode *node_the){
 stack_node *new_node;
 new_node=(stack_node*)malloc(sizeof(stack_node));
 new_node->elem=node_the;
 new_node->next=stack.top;
 stack.top=new_node;
}

/**********pop***********/
dnode*pop(){
 dnode *node_the;
 stack_node * ltemp;
 node_the=stack.top->elem;
 ltemp=stack.top->next;
 free(stack.top);
 stack.top=ltemp;
 return(node_the);
}

/***********top取栈顶元素***********/
dnode *top(){
 dnode *node_the;
 node_the=stack.top->elem;
 return(node_the);
}

/*********copy a node复制一个结点********/
dnode* copy_node(dnode * node_the,dnode* node_new){
 node_new->next=NULL;
 node_new->sub=NULL;
 node_new->type=node_the->type;
 strcpy(node_new->name,node_the->name);
 return(node_new);
}

/**********init of the basic chain初始化初始目录树*********/
errnum init_chain(){
 root=(dnode*)malloc(sizeof(dnode));
 root->next=NULL;
 root->sub=NULL;
 root->type=DIR;
 strcpy(root->name,"root");
 /******init the stack初始化栈********/
 stack.top=NULL;
 push(root);
 cur_dir=root;
 return 0;
}

/******telease the space of a subtree 释放一棵子树的空间******/
errnum free_tree(dnode* node_the){
 dnode* node_temp;
 if(node_the->sub==NULL){
  free(node_the);
  return 0;
 }
 node_temp=node_the;
 node_the=node_the->sub;
 free(node_temp);
 while(node_the!=NULL){
  node_temp=node_the;
  node_the=node_temp->next;
  free_tree(node_temp);
 }
 return 0;
}

/*********************/
typedef enum{NOP,EXIT,PWD,LSALL,LS,CD,RM,RMDIR,MKDIR,TOUCH,REN,CP,CPDIR}operations;
const char* operationstr[]={
 "",
 "exit",
 "pwd",
 "lsall",
 "ls",
 "cd",
 "rm",
 "rmdir",
 "mkdir",
 "touch",
 "ren",
 "cp",
 "cpdir"
};

/***********get the operation得到操作数和参数************/
operations get_operation(char* arg[2]){
 int i,j,k;
 char str[256],opstr[256];
 memset(str,0,256);
 memset(opstr,0,256);
 memset(arg[0],0,256);
 memset(arg[1],0,256);
 printf(":\\>");
 gets(str);/**maybe overflow这里可能出现溢出*/
 for(i=0;i<256;i++){
  if((str[i]==' ')||(str[i]==0)) break;
  opstr[i]=str[i];
 }
 for(j=1;j<=12;j++){
  if(strcmp(opstr,operationstr[j])==0)
   break;
 }
 if(j>12){
  error_out(2);
  return NOP;
 }
    /********0 arguments operations无参数时的操作*******/
 if((j>=EXIT)&&(j<=LS))
  return(j);
 /********1 arguments operations无参数时的操作*******/
 if((j>=CD)&&(j<=TOUCH)){
  if(str[i]==0){
   error_out(3);
   return NOP;
  }
  while((str[i]==' ')&&(i<256)) i++;
  for(k=0;i<256;i++,k++){
   if((str[i]==' ')||(str[i]==0)) break;
   arg[0][k]=str[i];
  }
  if((i>=256)||(k==0)){
   error_out(3);
   return NOP;
  }
  return(j);
 }
 /******2 arguments operations 2个参数时的操作***/
 if((j>=REN)&&(j<=CPDIR)){
  /*****get arguments 1 得到第一个操作数****/
  if(str[i]==0){
   error_out(3);
   return NOP;
  }
  while((str[i]==' ')&&(i<256)) i++;
  for(k=0;i<256;i++,k++){
   if((str[i]==' ')||(str[i]==0)) break;
   arg[0][k]=str[i];
  }
  if((i>=256)||(k==0)){
   error_out(3);
   return NOP;
  }
  /**********get argument 2 得到第二个操作数*********/
  while((str[i]==' ')&&(i<256)) i++;
  for(k=0;i<256;i++,k++){
   if((str[i]==' ')||(str[i]==0)) break;
   arg[1][k]=str[i];
  }
  if((i>=256)||(k==0)){
   error_out(3);
   return NOP;
  }
  return(j);
 }
}
/*********get the full current path得到完整的当前路径*******/
extern errnum ft_pwd(){
 int i=-1,j;
 char name[10][8];
 stack_node *temp;
 temp=stack.top;
 while(!(temp->elem==root)){
  i++;
  strcpy(name[i],temp->elem->name);
  temp=temp->next;
 }
 printf("%s","root");
 for(j=i;j>=0;j--){
  printf("\\%s",name[j]);
 }
 printf("\n");
 return 0;
}

/**display all the directories and files under the current dor 显示当前目录下的所有目录和文件**/
errnum ft_lsall(){
 dnode* node_the;
 node_the=cur_dir;
 push(node_the);
 do{
  node_the=pop();
  printf("directory <%s>:\n",node_the->name);
  node_the=node_the->sub;
  while(node_the){
   if(node_the->type==DIR)
    printf("<%s>    ",node_the->name);
   else
    printf("%s    ",node_the->name);
   if(node_the->type==DIR){
    push(node_the);
   }
   node_the=node_the->next;
  }
  printf("\n");
 }while(top()!=cur_dir);
 return 0;
}

/*****change directory改变目录*****/
errnum ft_cd(char* path){
 dnode*node_next;
 if(strcmp(path,"..")==0){
  if(cur_dir==root)
   return 0;
  pop();
  cur_dir=stack.top->elem;
  return 0;
 }
 node_next=cur_dir->sub;
 while(node_next){
  if(((strcmp(node_next->name,path))==0)&&(node_next->type==DIR)) break;
  node_next=node_next->next;
 }
 if(node_next==NULL){
  error_out(1);
  return 1;
 }
 else{ /*keep the current stack维护当前目录栈***/
  push(node_next);
  cur_dir=node_next;}
 return 0;
}

/**display the directories and files under the current directory显示当前目录下得目录和文件**/
errnum ft_ls(){
 dnode*node_sub,*node_next;
 node_sub=cur_dir->sub;
 node_next=node_sub;
 while(node_next){
  if(node_next->type==DIR)
   printf("<%s>    ",node_next->name);
  else
   printf("%s    ",node_next->name);
  node_next=node_next->next;
 }
 printf("\n");
 return 0;
}

/******delete the given file删除给定文件******/
errnum ft_rm(char* name){
 dnode *node_next,*node_the;
 node_next=cur_dir;
 node_the=cur_dir->sub;
 while(node_the){
  if((node_the->type==PLAIN)&&(!(strcmp(node_the->name,name))))
   break;
  else{
   node_the=node_the->next;
   if(node_next==cur_dir)
    node_next=node_next->sub;
   else
    node_next=node_next->next;
  }
 }
 if(node_the==NULL){
  error_out(1);
  return 1;
 }
 if(node_the==cur_dir->sub)
  cur_dir->sub=node_the->next;
 else
  node_next->next=node_the->next;
 free(node_the);
 return 0;
}

/******delete the given directory删除给定的目录******/
errnum ft_rmdir(char* name){
 dnode* node_next,*node_the;
 char choice,choice1[5];
 node_next=cur_dir;
 node_the=cur_dir->sub;
 while(node_the){
  if((node_the->type==DIR)&&(!(strcmp(node_the->name,name))))
   break;
  else{
   node_the=node_the->next;
   if(node_next==cur_dir)
    node_next=node_next->sub;
   else
    node_next=node_next->next;
  }
 }
 if(node_the==NULL){
  error_out(1);
  return 1;
 }
 if(node_the->sub){
  message_out("the directory is not NULL,do you want to del it?(y or n)");
  scanf("%c",&choice);
  gets(choice1);
  if(choice=='y'){
   if(node_the==cur_dir->sub)
    cur_dir->sub=node_the->next;
   else
    node_next->next=node_the->next;
   free_tree(node_the);
  }
  else
   return 0;
 }
 else{
  if(node_the==cur_dir->sub)
   cur_dir->sub=node_the->next;
  else
   node_next->next=node_the->next;
  free(node_the);
 }
 return 0;
}

/********make a new directory创建一个目录******/
errnum ft_mkdir(char* name){
 dnode *node_next,*node_new;
 node_new=(dnode*)malloc(sizeof(dnode));
 node_new->next=NULL;
 node_new->sub=NULL;
 node_new->type=DIR;
 strcpy(node_new->name,name);
 if(cur_dir->sub==NULL){
  cur_dir->sub=node_new;
 }
 else{
  node_next=cur_dir->sub;
  while(node_next->next)
   node_next=node_next->next;
  node_next->next=node_new;
 }
 return 0;
}

/*****make a new file创建一个新的文件*****/
errnum ft_touch(char *name){
 dnode* node_new,*node_next;
 node_new=(dnode*)malloc(sizeof(dnode));
 node_new->next=NULL;
 node_new->sub=NULL;
 node_new->type=PLAIN;
 strcpy(node_new->name,name);
 if(cur_dir->sub==NULL){
  cur_dir->sub=node_new;
 }
 else{
  node_next=cur_dir->sub;
  while(node_next->next)
   node_next=node_next->next;
  node_next->next=node_new;
 }
 return 0;
}

/********rename a file or directory重命名一个文件或者目录*****/
errnum ft_ren(char* oldname,char* newname){
 dnode* node_the;
 node_the=cur_dir->sub;
 while(node_the){
  if(strcmp(node_the->name,oldname)==0)
   break;
  else{
   node_the=node_the->next;
  }
 }
 if(node_the==NULL){
  error_out(1);
  return 1;
 }
 else
  strcpy(node_the->name,newname);
 return 0;
}

/****copy a file from the current dir to the given dir 从当前目录复制文件到一个给定的目录***/
errnum ft_cp(char *name,char* dirname){
 dnode *node_the,*node_new;
 node_the=cur_dir->sub;
 while(node_the){
  if((node_the->type==PLAIN)&&(!(strcmp(node_the->name,name))))
   break;
  else{
   node_the=node_the->next;
  }
 }
 if(node_the==NULL){
  error_out(1);
  return 1;
 }
 node_new=(dnode*)malloc(sizeof(dnode));
 node_new=copy_node(node_the,node_new);
 node_the=cur_dir->sub;
 while(node_the){
  if((strcmp(node_the->name,dirname)==0)&&(node_the->type==DIR))
   break;
  else{
   node_the=node_the->next;
  }
 }
 if(node_the==NULL){
  error_out(1);
  return 1;
 }
 if(node_the->sub==NULL){
  node_the->sub=node_new;
 }
 else{
  node_the=node_the->sub;
  while(node_the->next)
   node_the=node_the->next;
  node_the->next=node_new;
 }
 return 0;
}

/*******copy a node拷贝一个结点*****/
dnode* copy_dnode(dnode* node_the){
 dnode* node_new,*node_temp;
 if(node_the->sub==NULL){
  node_new=(dnode*)malloc(sizeof(dnode));
  copy_node(node_the,node_new);
  return(node_new);
 }
 else{
  node_new=(dnode*)malloc(sizeof(dnode));
  copy_node(node_the,node_new);
  node_the=node_the->sub;
  node_new->sub=copy_dnode(node_the);
  node_temp=node_new->sub;
  while(node_the->next!=NULL){
   node_temp->next=copy_dnode(node_the->next);
   node_the=node_the->next;
   node_temp=node_temp->next;
  }
  node_temp->next=NULL;
  return(node_new);
 }
}

/***copy a directory from current dir to the given dir从当前目录复制目录到给定目录下***/
errnum ft_cpdir(char* name,char * dirname){
 dnode * node_the,* node_new;
 node_the=cur_dir->sub;
 while(node_the){
  if((node_the->type==DIR)&&(!(strcmp(node_the->name,name))))
   break;
  else{
   node_the=node_the->next;
  }
 }
 if(node_the==NULL){
  error_out(1);
  return 1;
 }
 node_new=copy_dnode(node_the);
 node_the=cur_dir->sub;
 while(node_the){
  if(!(strcmp(node_the->name,dirname))&&(node_the->type==DIR))
   break;
  else{
   node_the=node_the->next;
  }
 }
 if(node_the==NULL){
  error_out(1);
  return 1;
 }
 if(node_the->sub==NULL){
  node_the->sub=node_new;
 }
 else{
  node_the=node_the->sub;
  while(node_the->next)
   node_the=node_the->next;
  node_the->next=node_new;
 }
 return 0;
}

/*******main主函数***********/
int main(){
 operations op;
 char* arguments[2];
 arguments[0]=malloc(256);
 arguments[1]=malloc(256);
 /********init the directory tree初始化目录树***/
 init_chain();
 /********main loop主循环******/
 for(;;){
  op=get_operation(arguments);
  switch(op){
  case PWD:
   {
    ft_pwd();
       break;
   }
  case LSALL:
   {
    ft_lsall();
       break;
   }
  case CD:
   {
    ft_cd(arguments[0]);
    break;
   }
  case LS:
   {
    ft_ls();
    break;
   }
  case RM:
   {
    ft_rm(arguments[0]);
    break;
   }
  case RMDIR:
   {
    ft_rmdir(arguments[0]);
    break;
   }
  case MKDIR:
   {
    ft_mkdir(arguments[0]);
    break;
   }
  case TOUCH:
   {
    ft_touch(arguments[0]);
    break;
   }
  case REN:
   {
    ft_ren(arguments[0],arguments[1]);
    break;
   }
  case CP:
   {
    ft_cp(arguments[0],arguments[1]);
    break;
   }
  case CPDIR:
   {
    ft_cpdir(arguments[0],arguments[1]);
    break;
   }
  case EXIT:
   {
    goto _out;
   }
  default:;
  }
 }
 /********exiting pricess 退出********/
 _out:
 return 0;
}
 
