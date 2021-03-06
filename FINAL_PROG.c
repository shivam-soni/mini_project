#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
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
    char loc[10];
}sym;
abc(char by[5],char a)
{
    char val[5];
    int x=(int)(a);
    itoa(x,val,16);
    strcat(by,val);
}
//typedef struct get_table opfile;
//typedef struct get_prog progfile;
int main()
{   progfile obprogp[40];
    opfile optab[40];
    progfile prog[40] ;
    progfile intermdt[40] ;//intermediate file
    sym *symbol;
    char buf[100],*p,*hexstr,hexadecimalNumber[100],temparr[2],by[7],s1[10],s2[10],s3[10];
    int label=0,operand,k=0,b=0,loc,l,length=0,i,sizeofoptab=0,sizeofprog=0,count,j,lenofnum,temp,temp1,temp2,startloc,len,c,m,sizeofob=0;;
    FILE *fp,*fp1;
    const int base = 16; // Base of Hexadecimal Number
    unsigned long locctr = 0;
    long int decimalNumber,remainder,quotient;

    fp=fopen("optab.txt","r");//opening the file to enter elements into an array
    if(fp==NULL)
    {
        printf("cannot open file");
    }
    while(fscanf(fp,"%s\t%s",optab[sizeofoptab].mneu,optab[sizeofoptab].code)!=EOF)//Filling the mnemonics and codes in the optab array..
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
    while(fgets(buf, sizeof(buf),fp) != NULL)//Entering the first line of the program into char array (buf)
   {
   count=0;
   p = strtok(buf,"\t");//tokenising the first line w.r.t. tab and entering it into char pointer p..
   while(p != NULL)
   {
    if(count==0)
    {
    strcpy(prog[sizeofprog].label,p);//Entering the first word before the tab into the label field of the array prog...
    count =count+1;
    }
    else if(count==1)
    {
      strcpy(prog[sizeofprog].mneu,p);//Entering the 2nd word before the tab into the label field of the array prog...
      count=count+1;
    }
    else if(count==2)
    {
       strcpy(prog[sizeofprog].operand,p);//Entering the 3rd word before the tab into the label field of the array prog...
        count=count+1;
    }

       p = strtok(NULL,"\t");
   }
   sizeofprog=sizeofprog+1;
}
fclose(fp);
for(j=0;j<sizeofprog;j++){
    printf("%s\t%s\t%s",prog[j].label,prog[j].mneu,prog[j].operand);//printing the array prog...
}
 l=0;
while(strcmp(prog[l].mneu,"END")!=0)
{
    p=strtok(prog[l].operand,"\n");
     strcpy(prog[l].operand,p);
     l++;
}
                                        //PASS ONE
fp=fopen("intermediate.txt","w");//opening the intermediate file to enter the locations in it.

    if(strcmp(prog[0].mneu,"START")==0)
    {
        fprintf(fp,"%c\t%s\t%s\t%s\n",32,prog[0].label,prog[0].mneu,prog[0].operand);//entering the first the line
        for (hexstr =prog[0].operand; *hexstr != '\0'; hexstr++)
        {
        length++;
        }
        // COnverting the starting address into hexadecimal
        hexstr = prog[0].operand;
        for (i = 0; *hexstr != '\0' && i < length; i++, hexstr++)
        {
        // Compare *hexstr with ASCII values
            if(*hexstr>=48 && *hexstr<=57)   // is *hexstr Between 0-9
                locctr+=(((int)(*hexstr)) -48)*pow(base, length - i - 1);
            else if((*hexstr>=65&&*hexstr<=70))   // is *hexstr Between A-F
                locctr += (((int)(*hexstr)) - 55) * pow(base, length - i - 1);
            else if (*hexstr >= 97 && *hexstr <= 102)   // is *hexstr Between a-f
                locctr += (((int)(*hexstr)) - 87) * pow(base, length - i - 1);
            else
                printf(" Invalid Hexadecimal Number \n");
        }
    }
    loc=locctr;
    startloc=locctr;
     l=1;
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
    symbol=(sym *)malloc(label*sizeof(sym));//Declaring the symbol table dynamically
    sym *sm=symbol;
    sym *sm1=symbol;
    l=1;
    while(strcmp(prog[l].mneu,"END")!=0)//Starting the pass 1
    {
        if(strcmp(prog[l].label,".")!=0)
        {
            if(strcmp(prog[l].label," ")!=0)
            {
                strcpy(symbol->label,prog[l].label);
                quotient = locctr;
                lenofnum=1;
                while(quotient!=0)
                {
                    temp = quotient % 16;
                    //To convert integer into character
                    if( temp < 10)
                    temp =temp + 48;
                    else
                    temp = temp + 55;
                    hexadecimalNumber[lenofnum++]= temp;
                    quotient = quotient / 16;
                }
                int i=0;
                for(j=lenofnum-1;j>0;j--)
                {
                  symbol->loc[i]=hexadecimalNumber[j];
                  i++;
                }
                  symbol->loc[i]='\0';
                 symbol=symbol+1;
             }
             count=0;
         for(j=0;j<sizeofoptab;j++)
         {
            if(strcmp(prog[l].mneu,"WORD")==0){
                locctr=locctr+3;
                count=1;
                break;
            }
             else if(strcmp(prog[l].mneu,"RESW")==0)
             {
                operand=(int)strtol(prog[l].operand,NULL,10);
                locctr=locctr+(3*operand);
                count=1;
                break;
             }
             else if(strcmp(prog[l].mneu,"RESB")==0)
             {
                  operand=(int)strtol(prog[l].operand,NULL,10);
                  locctr=locctr+operand;
                  count=1;
                  break;

             }
              else if(strcmp(prog[l].mneu,"BYTE")==0)
              {
                   int length;
                   strcpy(buf,prog[l].operand);
                    p=strtok(buf,"CX'xc");
                    length=strlen(p);
                    if(length==1)
                    {
                        locctr=locctr+length;
                    }
                    else{
                    length=(length/2);
                    locctr=locctr+length;
                    }
                count=1;
                   break;

              }
              else if(strcmp(prog[l].mneu,optab[j].mneu)!=0){
                continue;
              }
              else if(strcmp(prog[l].mneu,optab[j].mneu)==0)
              {
                  locctr=locctr+3;
                  count=1;
              }
         }
         if(count==0)
         {
             printf("\nMnemonic not found\n");
         }


      }
    fprintf(fp,"%X\t%s\t%s\t%s\n",loc,prog[l].label,prog[l].mneu,prog[l].operand);
    loc=locctr;
    l++;
    }
    fprintf(fp,"%c\t%s\t%s\t%s\n",32,prog[l].label,prog[l].mneu,prog[l].operand);
printf("\n");

for(j=0;j<label;j++)
{
printf("%s\t%s\n",(sm+j)->loc,(sm+j)->label);

 }


fclose(fp);

                        //PASS 2 STARTS

fp=fopen("intermediate.txt","r");//opening intermediate file to copy the content into the array object prog..
if(fp==NULL)
        printf("cannot open file");
int loc1;

fp1=fopen("objprog.txt","w");//opening the object program file to enter the obcode
if(fp1==NULL)
        printf("cannot open file");

while(fgets(buf, sizeof(buf),fp)!= NULL)//Entering the first line of the program from the file "intermediate.txt" into char array buf
   {
   count=0;
   p = strtok(buf,"\t");//Tokenising the second line according to delimeter "tab"
   while(p != NULL)
   {
    if(count==0)
    {
    strcpy(obprogp[sizeofob].loc,p);//Entering the first word of the line from buf into the array
    count =count+1;
    }
    else if(count==1)
    {
      strcpy(obprogp[sizeofob].label,p);//Entering the second word of the line from buf into the array
      count=count+1;
    }
    else if(count==2)
    {
       strcpy(obprogp[sizeofob].mneu,p);//Entering the third word of the line from buf into the array
        count=count+1;
    }
    else if(count==3)
    {
        strcpy(obprogp[sizeofob].operand,p);//Entering the fourth word of the line from buf into the array
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
fprintf(fp1,"%s\t%s\t%s\t%s",obprogp[0].loc,obprogp[0].label,obprogp[0].mneu,obprogp[0].operand);//Before starting the while loop entering the first line into the file
l=0;
while(strcmp(obprogp[l].mneu,"END")!=0)
{
    p=strtok(obprogp[l].operand,"\n");//removing "\n" from operand field
     strcpy(obprogp[l].operand,p);
     l++;
}
l=1;
while(strcmp(obprogp[l].mneu,"END")!=0)//starting the pass 2
{
 if(strcmp(obprogp[l].label,".")!=0)
    {
        if(strcmp(obprogp[l].mneu,"WORD")==0)
        {c=0,m=0;
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
        }
       else if(strcmp(obprogp[l].mneu,"BYTE")==0)
        {
             int length;
                   strcpy(buf,obprogp[l].operand);
                    p=strtok(buf,"CX'x");
                   if(obprogp[l].operand[0]==67||obprogp[l].operand[0]==99)
                   {

                       by[0]=0;
                       length=strlen(p);
                       for(i=0;i<length;i++)
                       {
                           abc(by,p[i]);
                       }
                       strcpy(obprogp[l].obcode,by);
                   }
                    else if(obprogp[l].operand[0]==120||obprogp[l].operand[0]==88)
                    {
                        strcpy(obprogp[l].obcode,p);
                    }
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

               for(k=0;k<label;k++)
                {
                length=strlen(obprogp[l].operand);
                 if(obprogp[l].operand[length-1]==120||obprogp[l].operand[length-1]==88)//checking if the operand field has "x" for index addressing
                 {  strcpy(buf,obprogp[l].operand);
                    p=strtok(buf,",");
                    if(strcmp(p,(sm+k)->label)==0)
                    {
                        temparr[0]=(sm+k)->loc[0];
                        i=(int)strtol(temparr,NULL,10);

                        if(i<8)
                         sprintf(s3,"%X",i+8);
                        else
                         sprintf(s3,"%X",i);
                         m=0;c=0;
                        while(m<4)
                        {
                            if(m==0){
                            s2[m]=s3[m];
                            //printf("%c",s2[j]);
                            }
                        else{
                            s2[m]=(sm+k)->loc[m];
                    // printf("%c",s2[j]);
                            }
                        m++;
                       }
                       s2[m]='\0';
                       break;
                    }
                    else if(strcmp(p,(sm+k)->label)!=0){
                        continue;
                    }
                    else{
                    printf("Error\n");
                  }
                }
                else
                {
                if(strcmp(obprogp[l].operand,(sm+k)->label)==0)
                  {
                    strcpy(s2,(sm+k)->loc);
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
         obprogp[l].obcode[j]='\0';
      }
}
if(obprogp[l].operand[length-1]==120||obprogp[l].operand[length-1]==88&&length>=8)
fprintf(fp1,"%s\t%s\t%s\t%s%c%s\n",obprogp[l].loc,obprogp[l].label,obprogp[l].mneu,obprogp[l].operand,32,obprogp[l].obcode);
else
fprintf(fp1,"%s\t%s\t%s\t%s\t%s\n",obprogp[l].loc,obprogp[l].label,obprogp[l].mneu,obprogp[l].operand,obprogp[l].obcode);//writing the line "l" into the file "objprog.txt"
l++;
}
fprintf(fp1,"%s\t%s\t%s\t%s\t%c\n",obprogp[l].loc,obprogp[l].label,obprogp[l].mneu,obprogp[l].operand,32);

                            //OBJECT PROGRAM
int lengthofprog,l1;
int l2=0;
 int no_of_lines=l-1;
 length=0;
 for (hexstr =obprogp[no_of_lines].loc; *hexstr != '\0'; hexstr++)
        {
        length++;
        }
        hexstr = obprogp[no_of_lines].loc;
        for (i = 0; *hexstr != '\0' && i < length; i++, hexstr++)
        {
        // Compare *hexstr with ASCII values
            if(*hexstr>=48 && *hexstr<=57)   // is *hexstr Between 0-9
                l2+=(((int)(*hexstr)) -48)*pow(base, length - i - 1);
            else if((*hexstr>=65&&*hexstr<=70))   // is *hexstr Between A-F
                l2+= (((int)(*hexstr)) - 55) * pow(base, length - i - 1);
            else if (*hexstr >= 97 && *hexstr <= 102)   // is *hexstr Between a-f
                l2 += (((int)(*hexstr)) - 87) * pow(base, length - i - 1);
            else
                printf(" Invalid Hexadecimal Number \n");
        }
 l1=startloc;
 char temphex[10];
 lengthofprog=((l2-l1)+1);
 sprintf(temphex,"%X",lengthofprog);
 length=strlen(obprogp[0].label);
 while(length<6)
 {
     obprogp[0].label[length]=32;
     length++;
 }
 obprogp[0].label[length]='\0';
 length=0;
 length=strlen(temphex);
 fp1=fopen("Record_file.txt","w");
 if(length==1)
 fprintf(fp1,"H^%s^00%s^00000%X\n",obprogp[0].label,obprogp[0].operand,lengthofprog);
 else if(length==2)
 fprintf(fp1,"H^%s^00%s^0000%X\n",obprogp[0].label,obprogp[0].operand,lengthofprog);
 else if(length==3)
 fprintf(fp1,"H^%s^00%s^000%X\n",obprogp[0].label,obprogp[0].operand,lengthofprog);
 else if(length==4)
 fprintf(fp1,"H^%s^00%s^00%X\n",obprogp[0].label,obprogp[0].operand,lengthofprog);
 l=1;
while(l<no_of_lines)
 {  temp1=l;
    while(strcmp(obprogp[temp1].obcode," ")==0)
    {
        temp1++;
    }
    fprintf(fp1,"T^00%s^",obprogp[temp1].loc);
    l=temp1;
    temp=0;
    while(1)
    {

        if((strcmp(obprogp[l].obcode," ")!=0)&&temp!=10)
        {
            len=strlen(obprogp[l].obcode);
            if((len%2)==0)
            len=len/2;
            else if((len%2)!=0)
            len=(len+1)/2;
            temp+=len;
            l++;
        }
        else
        {
            break;
        }
    }
    temp2=temp;
    sprintf(temphex,"%X",temp2);
    length=strlen(temphex);
    if(length==1)
    {
        fprintf(fp1,"0%X^",temp2);
    }
    else
    {
        fprintf(fp1,"%X^",temp2);
    }
    m=temp1;
    while(m<l-1)
    {
        fprintf(fp1,"%s^",obprogp[m].obcode);
        m++;
    }
    fprintf(fp1,"%s",obprogp[m].obcode);
    fprintf(fp1,"\n");

 }
 fprintf(fp1,"E^00%s",obprogp[1].loc);
 fclose(fp1);
 fclose(fp1);
return 0;
}



