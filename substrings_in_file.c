#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int line=0;
int get_substr(FILE *fp,char sub_str[][100],long int *pos,long int *indx);
void search_in_file(FILE *fp,char *sub_str,int indx_correction);
int search(char *mainstr,char *substr,int *arr);
void error(void);
int main()
{
	FILE *fp;
	char filename[50],ch,sub_str[100][100];
	int substr_count,k;
	long int start_pos,indx=0;
	
	printf("\n enter the file's name to be opened\n");
	gets(filename);
	fp=fopen(filename,"r");
	if(!fp)
	{
		printf("\n file not found ----- unable to open");
		exit(0);
	}
	
	substr_count=get_substr(fp,sub_str,&start_pos,&indx);
	printf("\nindex=%d",indx);
	for(k=0;k<substr_count;k++)
	{
		if(sub_str[k][0]!='\0')
		{
			fseek(fp,start_pos,SEEK_SET);
			printf("\n%s________________________________________",sub_str[k]);
			search_in_file(fp,sub_str[k],indx);
		}
	}
	return 0;
}
int get_substr(FILE *fp,char sub_str[][100],long int *pos,long int *indx)
{
	char ch1,ch2;
	int i=0,j=0;
	ch1=getc(fp);
	if(ch1==EOF)
		error();
	ch2=getc(fp);
	if(ch2==EOF)
		error();
	*indx+=2;
	while( (ch1!='/') || (ch2!='*') )
	{
		if(ch1=='\n')
		{
			line++;
			*indx=0;
		}
		ch1=ch2;
		ch2=getc(fp);
		if(ch2==EOF)
			error();
		*indx+=1;
	}
	
	ch1=getc(fp);
	if(ch1==EOF)
		error();
	ch2=getc(fp);
	if(ch2==EOF)
		error();
	*indx+=2;
	while((ch1!='*') || (ch2!='/') )
	{
		if(!(ch1==' ' || ch1==',' || ch1=='\n') )
		{
			if(ch1=='\n')
			{
				line++;
				*indx=0;
			}
			sub_str[i][j++]=ch1;
			ch1=ch2;
			ch2=getc(fp);
			if(ch2==EOF)
				error();
			*indx+=1;
		}
		else
		{
			sub_str[i++][j]='\0';
			j=0;
			while( ch1==' ' || ch1==',' || ch1=='\n' )
			{
				if(ch1=='\n')
				{
					line++;
					*indx=0;
				}
				ch1=ch2;
				ch2=getc(fp);
				if(ch2==EOF)
					error();
				*indx+=1;
			}
		}
	}	
	*pos=ftell(fp);
	return i;
}

int search(char *mainstr,char *substr,int *arr)
{
	int i=0,j=0,str_len,substr_len,substr_count=0;
	str_len=strlen(mainstr);
	substr_len=strlen(substr);
	
	for(i=0;i<=str_len-substr_len;i++)
	{
		for(j=0;j<substr_len;j++)
		{
			if( mainstr[i+j]!=substr[j])
				break;		
		}
		if( j==substr_len)
			arr[substr_count++]=i;
	}
	return substr_count;
}

void search_in_file(FILE *fp,char *sub_str,int indx_correction)
{
	char ch,ch1,ch2,main_str[300];
	int line_no=0,i=0,flag=0,substring_count,index[100];
	
	while( (ch=getc(fp))!=EOF )
	{
		if(ch=='\n')
			line_no++;
		i=0;
		main_str[i++]=ch;
		while( ch!='\n' )                                      
		{
			ch=getc(fp);	
			main_str[i++]=ch;
		}
		main_str[i]='\0';
		line_no++;
		
		if(line_no!=1)
			indx_correction=0;
		substring_count=search(main_str,sub_str,index);
		for(i=0;i<substring_count;i++)
		{
			flag=1;
			printf("\nsubstring %s is present in line %d at index %d",sub_str,line_no+line,index[i]+indx_correction);
		}
	}
	
	if(flag==0)
		printf("\nsubstring not found\n");
}
void error(void)
{
	printf("\n error --- file ended in an unexpected way\n");
	exit(0);
}
