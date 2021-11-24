#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int get_substr(FILE *fp,char sub_str[][100]);
void error(void);
int main()
{
	FILE *fp;
	char filename[50],ch, sub_str[100][100];
	int substr_count,k;
	
	printf("\n enter the file's name to be opened\n");
	gets(filename);
	fp=fopen(filename,"r");
	if(!fp)
	{
		printf("\n file not found ----- unable to open");
		exit(0);
	}
	
	substr_count=get_substr(fp,sub_str);
	for(k=0;k<substr_count;k++)
	{
		printf("\n%s\n________________________________________\n",sub_str[k]);;
	}
	return 0;
}

// finding substrings using strtok 
int get_substr(FILE *fp,char sub_str[][100])
{
	char ch,ch1,ch2,str[500],*tok;
	int i=0,j=0;
	ch1=getc(fp);	if(ch1==EOF)	error();
	ch2=getc(fp);	if(ch2==EOF)	error();
	while( (ch1!='/') || (ch2!='*') )
	{
		ch1=ch2;
		ch2=getc(fp);	if(ch2==EOF)	error();
	}
	
	ch1=getc(fp);	if(ch1==EOF)	error();
	ch2=getc(fp);	if(ch2==EOF)	error();
	while((ch1!='*') || (ch2!='/') )
	{
		str[i++]=ch1;
		ch1=ch2;
		ch2=getc(fp);	if(ch2==EOF)	error();
	}	
	str[i]='\0';
	tok=strtok(str,", \n");
	while(tok!=NULL)
	{
	//	printf("\n1 %s",tok);
		strcpy(sub_str[j++],tok);
		tok=strtok(NULL,", \n");
	}
	return j;
}
void error(void)
{
	printf("\n error --- file ended in an unexpected way\n");
	exit(0);
}
