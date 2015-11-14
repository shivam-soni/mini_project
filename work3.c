#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
typedef struct get_table
{
    char mneu[20];
    char code[20];
}opfile;
typedef struct symbol
{
    char label[10];
    int loc;
}sym;
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
      sym *symbol;
      int sizeofoptab=0,sizeofprog=0,count,j;
    FILE *fp;
    int locctr,label=0,operand,k=0,b=0,loc;
    fp=fopen("optab.txt","r");
    if(fp==NULL)
    {
        printf("cannot open file");
    }
    while(fscanf(fp,"%s\t%s",optab[sizeofoptab].mneu,optab[sizeofoptab].code)!=EOF)
    {
        sizeofoptab++;
    }
fclose(fp);
    for(j=0;j<sizeofoptab;j++)
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
    strcpy(prog[sizeofprog].label,p);
    count =count+1;
    }
    else if(count==1)
    {
      strcpy(prog[sizeofprog].mneu,p);
      count=count+1;
    }
    else if(count==2)
    {
       strcpy(prog[sizeofprog].operand,p);
        count=count+1;
    }

       p = strtok(NULL,"\t");
   }
   sizeofprog=sizeofprog+1;
}
fclose(fp);
printf("\n");
for(j=0;j<sizeofprog;j++){
    printf("%s\t%s\t%s",prog[j].label,prog[j].mneu,prog[j].operand);
}
fp=fopen("intermediate.txt","w");



    if(strcmp(prog[0].mneu,"START")==0)
    {
        locctr=(int)strtol(prog[0].operand,NULL,10);
        fprintf(fp,"%c\t%s\t%s\t%s",32,prog[0].label,prog[0].mneu,prog[0].operand);

    }
    loc=locctr;
    int l=1;
     while(strcmp(prog[l].mneu,"END")!=0)
    {
        if(strcmp(prog[l].label," ")!=0)
        {
        label=label+1;
            l=l+1;
        }
        else{
            l=l+1;
        }

    }
 printf("\n%d\n",label);

symbol=(sym *)malloc(label*sizeof(sym));
    sym *sm=symbol;
    sym *sm1=symbol;
    l=1;
   // fprintf(fp,"%d\t%s\t%s\t%s\n",locctr,prog[l].label,prog[l].mneu,prog[l].operand)
    while(strcmp(prog[l].mneu,"END")!=0)
    {
        //fprintf(fp,"%d\t%s\t%s\t%s",locctr,prog[l].label,prog[l].mneu,prog[l].operand);
        if(strcmp(prog[l].label,".")!=0)
        {
            if(strcmp(prog[l].label," ")!=0)
            {
                strcpy(symbol->label,prog[l].label);
                symbol->loc=locctr;
               // printf("%d\t%s\n",symbol->loc,symbol->label);
                symbol=symbol+1;
            }
         for(j=0;j<sizeofoptab;j++)
         {
            if(strcmp(prog[l].mneu,"WORD")==0){
                locctr=locctr+3;
                break;
            }
             else if(strcmp(prog[l].mneu,"RESW")==0)
             {
                operand=(int)strtol(prog[l].operand,NULL,10);
                locctr=locctr+(3*operand);
                break;
             }
             else if(strcmp(prog[l].mneu,"RESB")==0)
             {
                  operand=(int)strtol(prog[l].operand,NULL,10);
                  locctr=locctr+operand;
                  break;
             }
              else if(strcmp(prog[l].mneu,"BYTE")==0)
              {
                   int length;
                   strcpy(buf,prog[l].operand);
                   //printf("%s",buf);
                    p=strtok(buf,"CX'");
                    length=strlen(p);
                    if(length==1)
                    {
                        locctr=locctr+length;
                    }
                    else{
                    length=(length/2);
                    locctr=locctr+length;
                    }

                   break;
              }
              else if(strcmp(prog[l].mneu,optab[j].mneu)!=0){
                continue;
              }
              else if(strcmp(prog[l].mneu,optab[j].mneu)==0)
              {
                  locctr=locctr+3;
              }
              else
                printf("error");
         }
      }
    fprintf(fp,"%d\t%s\t%s\t%s",loc,prog[l].label,prog[l].mneu,prog[l].operand);
    loc=locctr;
    l++;
    }
   // printf("%d\n",l);
    fprintf(fp,"%c\t%s\t%s\t%s",32,prog[l].label,prog[l].mneu,prog[l].operand);


for(j=0;j<label;j++)
{
printf("%d\t%s\n",(sm+j)->loc,(sm+j)->label);

 }


fclose(fp);
return 0;
}
