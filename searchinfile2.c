#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void search_in_file(char *sub_str,char *filename);
int main()
{
	
	char filename[50],ch,sub_str[100];
	printf("\n enter the file's name to be opened\n");
	gets(filename);
	printf("\nenter the string to be searched\n");
	gets(sub_str);
	search_in_file(sub_str,filename);
	
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

void search_in_file(char *sub_str,char *filename)
{
	FILE *fp;
	char ch,main_str[300];
	int line_no=0,i=0,flag=0,substring_count,index[100];
	fp=fopen(filename,"r");
	if(!fp)
	{
		printf("\n file not found ----- unable to open");
		exit(0);
	}
	
	fgets(main_str,100,fp);
	while( !feof(fp) )
	{
		line_no++;
		substring_count=search(main_str,sub_str,index);
		for(i=0;i<substring_count;i++)
		{
			flag=1;
			printf("\nsubstring %s is present in line %d at index %d",sub_str,line_no,index[i]);
		}
		fgets(main_str,100,fp);
	}
	
	fclose(fp);
	if(flag==0)
		printf("\nsubstring not found\n");
} 
