#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int line=0;
int get_substr(FILE *fp,FILE *out,char sub_str[][100],long int *indx);
void search_in_file(FILE *fp,FILE *out,char sub_str[][100],int substr_count,int indx_correction);
int search(char *mainstr,char *substr,int *arr);
void error(FILE *out);
int main()
{
	FILE *fp,*out;
	char filename[50],ch,sub_str[100][100];
	int substr_count,k;
	long int indx=0;
	
	printf("\n enter the file's name to be opened\n");
	gets(filename);
	fp=fopen(filename,"r");
	if(!fp)
	{
		printf("\n file not found ----- unable to open");
		exit(0);
	}
	
	out=fopen("output.txt","w");
	if(!out)
	{
		printf("\n file not found ----- unable to open");
		exit(0);
	}
	
	substr_count=get_substr(fp,out,sub_str,&indx);
	printf("index=%d\n",indx);
	search_in_file(fp,out,sub_str,substr_count,indx);
	fclose(fp);
	return 0;
}


int get_substr(FILE *fp,FILE *out,char sub_str[][100],long int *indx)
{
	char ch,ch1,ch2,str[500],*tok;
	int i=0,j=0;
	ch1=getc(fp); 	if(ch1==EOF)	error(out);
	ch2=getc(fp);	if(ch2==EOF)	error(out);
	*indx+=2;
	while( (ch1!='/') || (ch2!='*') )
	{
		if(ch1=='\n')
		{
			line++;
			*indx=0;
		}
		ch1=ch2;
		ch2=getc(fp);	if(ch2==EOF)	error(out);
		*indx+=1;
	}
	
	ch1=getc(fp);	if(ch1==EOF)	error(out);
	ch2=getc(fp);	if(ch2==EOF)	error(out);
	*indx+=2;
	while((ch1!='*') || (ch2!='/') )
	{
		str[i++]=ch1;
		if(ch1=='\n')
		{
			line++;
			*indx=0;
		}
		ch1=ch2;
		ch2=getc(fp);	if(ch2==EOF)	error(out);
		*indx+=1;
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

void search_in_file(FILE *fp,FILE *out,char sub_str[][100],int substr_count,int indx_correction)
{
	char ch,ch1,ch2,main_str[300];
	int line_no=0,i=0,flag=0,substring_count,index[100],j=0;
	
	
	while( (ch=getc(fp))!=EOF )
	{
		if(ch=='\n')
		{
			if(flag==0)
			{
				line_no++;
				flag=1;
			}	
		}
		i=0;
		main_str[i++]=ch;
		while( ch!='\n' )                                      
		{
			ch=getc(fp);		if(ch==EOF)	error(out);
			main_str[i++]=ch;
		}
		main_str[i]='\0';
		line_no++;
		
		printf("\n\nin line %d ",line_no+line);
		fprintf(out,"\n\nin line %d ",line_no+line);
		if(line_no!=1)
			indx_correction=0;
		for(j=0;j<substr_count;j++)
		{
			substring_count=search(main_str,sub_str[j],index);
			if(substring_count>0)
			{
				printf("\nsubstring %s is present at index(s) ",sub_str[j]);
				fprintf(out,"\nsubstring %s is present at index(s) ",sub_str[j]);
			}
			for(i=0;i<substring_count;i++)
			{
				printf(" %d ",index[i]+indx_correction);
				fprintf(out," %d ",index[i]+indx_correction);
			}
		}
	}
//	if(flag==0)
//		printf("\nsubstring not found\n");
}
void error(FILE *out)
{
	printf("\n error --- file ended in an unexpected way\n");
	fprintf(out,"\n error --- file ended in an unexpected way\n");
	fclose(out);
	exit(0);
}
