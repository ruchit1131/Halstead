#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void search_in_file(FILE *fp,char *sub_str);
int main()
{
	FILE *fp;
	char filename[50],ch,sub_str[100];
	
	printf("\n enter the file's name to be opened\n");
	gets(filename);
	fp=fopen(filename,"r");
	if(!fp)
	{
		printf("\n file not found ----- unable to open");
		exit(0);
	}
	printf("\nenter the string to be searched\n");
	gets(sub_str);
	
	search_in_file(fp,sub_str);
	
	fclose(fp);	
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

void search_in_file(FILE *fp,char *sub_str)
{
	char ch,main_str[300];
	int line_no=0,i=0,flag=0,substring_count,index[100];
	while( (ch=getc(fp))!=EOF )
	{
		line_no++;
		i=0;
		main_str[i++]=ch;
		while( (ch=getc(fp))!='\n' )                                      
			main_str[i++]=ch;
		main_str[i]='\0';
		
		substring_count=search(main_str,sub_str,index);
		for(i=0;i<substring_count;i++)
		{
			flag=1;
			printf("\nsubstring %s is present in line %d at index %d",sub_str,line_no,index[i]);
		}
	}
	
	fclose(fp);
	if(flag==0)
		printf("\nsubstring not found\n");
} 
