#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int get_substr(FILE *fp,char sub_str[][100]);
void error(void);
int main()
{
	FILE *fp;
	char filename[50],ch,sub_str[100][100];
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
int get_substr(FILE *fp,char sub_str[][100])
{
	char ch,ch1,ch2;
	int i=0,j=0;
	sub_str[i][j]='\0';
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
		if(!(ch1==' ' || ch1==',' || ch1=='\n'	) )
		{
			sub_str[i][j++]=ch1;
			ch1=ch2;
			ch2=getc(fp);	if(ch2==EOF)	error();
		}
		else
		{
			if(sub_str[i][0]!='\0')
				sub_str[i++][j]='\0';
			j=0;
			sub_str[i][j]='\0';
			while( ch1==' ' || ch1==',' || ch1=='\n' )
			{
				ch1=ch2;
				ch2=getc(fp);	if(ch2==EOF)	error();
			}
		}
	}
	sub_str[i][j]='\0';	
	return i;
}
void error(void)
{
	printf("\n error --- file ended in an unexpected way\n");
	exit(0);
}
