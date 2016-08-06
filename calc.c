#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//buffer for rome capital convert
char inbuf[100];
char outbuf[100];
int  capital_letter[100];
char romearry[]="IVXLCDM";

//stack struct for calculation
#define stkarry 10

typedef struct stack{
    int data;
    struct stack *next;
}stack;

stack *head[stkarry];
stack *tail[stkarry];


void set_letter()
{
    capital_letter['I']=1;
    capital_letter['V']=5;
    capital_letter['X']=10;
    capital_letter['L']=50;
    capital_letter['C']=100;
    capital_letter['D']=500;
    capital_letter['M']=1000;
}

int letterToint(char *incapital)
{
    int i,tmpint,outint;
    for(tmpint=outint=i=0; incapital[i]; i++)
    {
      if(tmpint < capital_letter[incapital[i]])
      {
          outint = outint - 2*tmpint;
      }
      outint = outint + capital_letter[incapital[i]];
      tmpint = capital_letter[incapital[i]];
    }
    return outint;
}

char * intToletter(int inint,char *outbuf)
{
    int i,std,cnt,tmp;

    for(i=0;inint;)
    {
      tmp=inint;
      for(std=1000,cnt=3;tmp==inint;std/=10,cnt--)
      {
        if(inint>=std)
        {
          inint-=std;
          outbuf[i++]=romearry[2*cnt];
        }
        else if(inint>=std-std/10)
        {
          inint-=std-std/10;
          outbuf[i++]=romearry[2*cnt-2];
          outbuf[i++]=romearry[2*cnt];
        }
        else if(inint>=std/2)
        {
          inint-=std/2;
          outbuf[i++]=romearry[2*cnt-1];
        }
        else if(inint>=std/2-std/10)
        {
          inint-=std/2-std/10;
          outbuf[i++]=romearry[2*cnt-2];
          outbuf[i++]=romearry[2*cnt-1];
        }
      }
    }
    outbuf[i]=0;
    return outbuf;
}


//stack implementation
void stackinit()
{
    int index = 0;
    head[index]=(stack *)malloc(sizeof(stack));
    head[index]->data=-1;
    head[index]->next=0;
    tail[index]=head[index];
}

int isEmpty(int index)
{
    return head[index]->data==-1;
}

void push(int index,int val)
{
    stack *p=head[index];
    head[index]=(stack *)malloc(sizeof(stack));
    head[index]->data=val;
    head[index]->next=p;
}

int pop(int index)
{
    int result;
    stack *p=head[index];
    result=head[index]->data;
    head[index]=head[index]->next;
    free(p);
    return result;
}

stack *find(int index,int val)
{
    stack *p=head[index];
    for(;p;p=p->next){
        if(p->data==val){
            return p;
        }
    }
    return 0;
}

int stacklen()
{
   
    int count = 0;
    int index = 0;
    stack * p;
    p=head[index];

    for(;p;p=p->next){
        count = count + 1;
    }
    return count-1;
}

void destroy(int index)
{
    for(;!isEmpty(index);){
        pop(index);
    }
}

void initbuf()
{
    memset(inbuf,0,sizeof(char)*100);
    memset(outbuf,0,sizeof(char)*100);

}

char * testcase(char (*inputbuf)[10],char *verifybuf)
{
  int in1,in2;
  int calcflag = 0;
  char * retbuf;

  stackinit();
  set_letter();
  initbuf();

  
  int testcnt = 0;
  int resultcnt = 0;
  // char testbuf[][10] = {"XIV","LX"};
  char (*testbuf)[10];
  char *resultbuf;
  testbuf = inputbuf;
  resultbuf = verifybuf;
  // char resultbuf[][10] = {"LXXIV"};

  while(1)
  {
    
    if(stacklen() == 2 && calcflag ==0){
      printf("input + or - letter \n");
      calcflag = 1;
      memcpy(inbuf,"+",sizeof(char));
      
    }
    else if(stacklen() == 1 && calcflag == 1){
      printf("input = letter \n");
      calcflag = 0;
      memcpy(inbuf,"=",sizeof(char));
    }
    else{
      // printf("input rome letter \n");
      if (testcnt >= 2){
          break;
      } 
      memcpy(inbuf,testbuf[testcnt],sizeof(testbuf[testcnt]));
      printf("input rome letter %s\n",inbuf);
      testcnt += 1;
    }
   
    // fgets(inbuf,100,stdin);
    

    if(inbuf[0]=='+'||inbuf[0]=='-'||inbuf[0]=='=')
    {
      if(inbuf[0]=='=')
      {
        if(isEmpty(0)){
            printf("no input in stack\n");
        }
        else if(head[0]->data<1){
            printf("out of range exception\n");
        }
        else{
            retbuf = intToletter(head[0]->data,outbuf);
            printf("result %s\n",retbuf);
            pop(0);
            if (!strcmp(retbuf,resultbuf)){
              printf("result success!!\n");
            }
            else{
              printf("result fail!!\n");
            }
        
        }
        
      }
      else if(head[0]->data==-1||head[0]->next->data==-1){
          printf("no data in stack\n");
      }
      else 
      {
        in1=pop(0);
        in2=pop(0);
        if(inbuf[0]=='+')
        { 
          push(0,in1+in2); 
        }
        else if(inbuf[0]=='-')
        {
          push(0,in2-in1);
        }
        
      }
    }
    else
    {
      push(0,letterToint(inbuf));
      
    }
  }

  return retbuf;
}

#ifndef UNIT_TEST
int main()
{
    int in1,in2;
    int calcflag = 0;

    stackinit();
    set_letter();
    initbuf();

    
    while(1)
    {

      
      if(stacklen() == 2 && calcflag ==0){
        printf("input + or - letter \n");
        calcflag = 1;
      }
      else if(stacklen() == 1 && calcflag == 1){
        printf("input = letter \n");
        calcflag = 0;
      }
      else{
        printf("input rome letter \n");
      }
     
      fgets(inbuf,100,stdin);

      if(inbuf[0]=='+'||inbuf[0]=='-'||inbuf[0]=='=')
      {
        if(inbuf[0]=='=')
        {
          if(isEmpty(0)){
              printf("no input in stack\n");
          }
          else if(head[0]->data<1){//||head[0]->data>4999){
              printf("out of range exception\n");
          }
          else{
              printf("result %s\n",intToletter(head[0]->data,outbuf));
              pop(0);
          }
          
        }
        else if(head[0]->data==-1||head[0]->next->data==-1){
            printf("no data in stack\n");
        }
        else 
        {
          in1=pop(0);
          in2=pop(0);
          if(inbuf[0]=='+')
          { 
            push(0,in1+in2); 
          }
          else if(inbuf[0]=='-')
          {
            push(0,in2-in1);
          }
          
        }
      }
      else
      {
        push(0,letterToint(inbuf));
        
      }
    }
    
    
}
#endif
