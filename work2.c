#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
typedef struct get_table
{
    char mneu[20];
    char code[20];
}opfile;
typedef struct get_prog
{
    int loc;
    char label[10];
    char mneu[20];
    char operand[20];
    char obcode[20];
}progfile;
int main()
{
    opfile optab[40];
    char buf[100],*p;
     progfile prog[40] ;
    FILE *fp;
    int i=0,j,count=0,x=0;
    fp=fopen("optab.txt","r");
    if(fp==NULL)
    {
        printf("cannot open file");
    }
    while(fscanf(fp,"%s\t%s",optab[i].mneu,optab[i].code)!=EOF)
    {
        i++;
    }
fclose(fp);
    for(j=0;j<i;j++)
    {
        printf("%s\t%s\n",optab[j].mneu,optab[j].code);
    }

    fp=fopen("prog.txt","r");
    if(fp==NULL)
    {
        printf("cannot open file");
    }
    while(fgets(buf, sizeof(buf),fp) != NULL)
   {
   count=0;
   p = strtok(buf,"\t");
   while(p != NULL)
   {
    if(count==0)
    {
    strcpy(prog[x].label,p);
    count =count+1;
    }
    else if(count==1)
    {
      strcpy(prog[x].mneu,p);
      count=count+1;
    }
    else if(count==2)
    {
       strcpy(prog[x].operand,p);
        count=count+1;
    }

       p = strtok(NULL,"\t");
   }
   x=x+1;
}
fclose(fp);
printf("\n");
for(j=0;j<x;j++){
    printf("%s\t%s\t%s",prog[j].label,prog[j].mneu,prog[j].operand);
}
return 0;
}
