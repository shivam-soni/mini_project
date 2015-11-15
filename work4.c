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
    char loc[10];
    char label[10];
    char mneu[20];
    char operand[20];
    char obcode[20];
}progfile;
typedef struct symbol
{
    char label[10];
    int loc;
}sym;
//typedef struct get_table opfile;
//typedef struct get_prog progfile;
int main()
{
    opfile optab[40];
    progfile prog[40] ;
    progfile intermdt[40] ;//intermediate file
    sym *symbol;
    char buf[100],*p;
    int locctr,label=0,operand,k=0,b=0,loc;
    FILE *fp;
    int sizeofoptab=0,sizeofprog=0,count,j;
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
        printf("%s %s\n",optab[j].mneu,optab[j].code);
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
//printf("\n%s\n",prog[9].label);
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
    printf("%d\n",l);
    fprintf(fp,"%c\t%s\t%s\t%s",32,prog[l].label,prog[l].mneu,prog[l].operand);


for(j=0;j<label;j++)
{
printf("%d\t%s\n",(sm+j)->loc,(sm+j)->label);

 }


fclose(fp);
                        //PASS 2 STARTS

progfile obprogp[40];
FILE *fp1;
int sizeofob=0;
char s1[10],s2[10];
fp=fopen("intermediate.txt","r");

if(fp==NULL)
    {
        printf("cannot open file");
    }
int loc1;

fp1=fopen("objprog.txt","w");
if(fp1==NULL)
    {
        printf("cannot open file");
    }

while(fgets(buf, sizeof(buf),fp)!= NULL)
   {
   count=0;
   p = strtok(buf,"\t");
   while(p != NULL)
   {
    if(count==0)
    {
    strcpy(obprogp[sizeofob].loc,p);
    count =count+1;
    }
    else if(count==1)
    {
      strcpy(obprogp[sizeofob].label,p);
      count=count+1;
    }
    else if(count==2)
    {
       strcpy(obprogp[sizeofob].mneu,p);
        count=count+1;
    }
    else if(count==3)
    {
        strcpy(obprogp[sizeofob].operand,p);
    }

       p = strtok(NULL,"\t");
   }
   sizeofob=sizeofob+1;
}
printf("\n");
for(j=0;j<sizeofob;j++)
{
printf("%s\t%s\t%s\t%s",obprogp[j].loc,obprogp[j].label,obprogp[j].mneu,obprogp[j].operand);
}
fprintf(fp1,"%s\t%s\t%s\t%s",obprogp[0].loc,obprogp[0].label,obprogp[0].mneu,obprogp[0].operand);
l=0;
while(strcmp(obprogp[l].mneu,"END")!=0)
{
    p=strtok(obprogp[l].operand,"\n");
     strcpy(obprogp[l].operand,p);
     //printf("%s ",obprogp[l].operand);
     l++;
}
l=1;
while(strcmp(obprogp[l].mneu,"END")!=0)
{
 if(strcmp(obprogp[l].label,".")!=0)
    {
        if(strcmp(obprogp[l].mneu,"WORD")==0)
        {int len,c=0,m=0;
            len=strlen(obprogp[l].operand);

            m=len;
            while(m<6)
            {
                obprogp[l].obcode[c]=48;
               m++;
               c++;
            }
           m=0;
           while(m<len)
         {
             obprogp[l].obcode[c]=obprogp[l].operand[m];
             c++;
             m++;
         }
         obprogp[l].obcode[c]='\0';
        // printf("%s",obprogp[l].obcode);
        }
       else if(strcmp(obprogp[l].mneu,"BYTE")==0)
        {
             int length;
                   strcpy(buf,obprogp[l].operand);
                  // printf("%s",buf);
                    p=strtok(buf,"CX'");
                   // printf("%s",p);
                    if(strcmp(p,"EOF")==0)
                    {
                        strcpy(obprogp[l].obcode,"454F46");
                    }
                    else
                    {
                        strcpy(obprogp[l].obcode,p);
                    }
              //printf("%s",obprogp[l].obcode);
        }
       else if((strcmp(obprogp[l].mneu,"RESW")==0)||(strcmp(obprogp[l].mneu,"RESB")==0))
        {
            strcpy(obprogp[l].obcode," ");
        }
        else if(strcmp(obprogp[l].mneu,"RSUB")==0)
        {
            strcpy(obprogp[l].obcode,"4C0000");
        }
        else
        {
         for(j=0;j<sizeofoptab;j++)
         {
            if(strcmp(obprogp[l].mneu,optab[j].mneu)==0)
            {
               strcpy(s1,optab[j].code);
              // puts(s1);

               for(k=0;k<label;k++)
                {
                 //printf("\n%d\t%s\n",(sm+k)->loc,(sm+k)->label);
                 strcpy(buf,obprogp[l].operand);
                 p=strtok(buf,"\n");
                 //puts(p);
                if(strcmp(p,(sm+k)->label)==0)
                  {
                    sprintf(s2,"%d",(sm+k)->loc);
                    //puts(s2);
                    break;
                  }
                  else if(strcmp(obprogp[l].operand,(sm+k)->label)!=0){
                    continue;
                  }
                  else{
                    printf("Error\n");
                  }

                }
            }
            else if(strcmp(obprogp[l].mneu,optab[j].mneu)!=0)
              continue;
            else
              printf("Error\n");
        }
         j=0;int t=0;
         while(j<6)
         {
          if(j<2)
          {
           obprogp[l].obcode[j]=s1[j];
           j++;
          }
          else
          {
           obprogp[l].obcode[j]=s2[t];
           j++;
           t++;
          }
         }
      }
}
fprintf(fp1,"%s\t%s\t%s\t%s\t%s\n",obprogp[l].loc,obprogp[l].label,obprogp[l].mneu,obprogp[l].operand,obprogp[l].obcode);
l++;
}
printf("\n");

/*for(j=0;j<l;j++)
{
printf("%s ",obprogp[j].obcode);
}*/
fclose(fp1);
fclose(fp);
return 0;
}
