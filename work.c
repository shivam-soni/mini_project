#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
typedef struct get_table
{
    char mneu[20];
    char code[20];
}opfile;
int main()
{
    opfile optab[40];
    FILE *fp;
    int i=0,j;
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
    return 0;
}
