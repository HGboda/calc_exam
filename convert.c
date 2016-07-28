#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inbuf[100];
char outbuf[100];
int  capital_letter[100];
char romearry[]="IVXLCDM";

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

void intToletter(int inint)
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
}

int main()
{
    int tmpin;

    set_letter();


    while(1){

      fgets(inbuf,100,stdin);

      tmpin=letterToint(inbuf);
      printf("%d \n",tmpin);

      intToletter(tmpin);

      printf("%s \n",outbuf);
    }

}