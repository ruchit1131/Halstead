#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void extract_variables(char *mainstr,char *substr,char var_str[100][100],int *var_count);
int search_variable(char *mainstr,char *substr,int *arr);
int get_variables(FILE *fp,char var_str[100][100]);
void get_line(FILE *fp,char *str);
int main()
{
	
	FILE *fp;
	char filename[50],ch,var_str[100][100];
	int var_count,i;
	
	printf("\n enter the file's name to be opened\n");
	gets(filename);
	fp=fopen(filename,"r");
	if(!fp)
	{
		printf("\n file not found ----- unable to open");
		exit(0);
	}
	
	var_count=get_variables(fp,var_str);
	for(i=0;i<var_count;i++)
	{
		printf(" %s\n",var_str[i]);
	}
		
}

int get_variables(FILE *fp,char var_str[100][100])
{
	char var_name[35],line[300];
	int arr[100],var_count=0,num;
	
	get_line(fp,line);
	while(!feof(fp))
	{
		if( search_variable(line,"char",arr) )
			extract_variables(line,"char",var_str,&var_count);
		get_line(fp,line);
	}
	return var_count;
}

int search_variable(char *mainstr,char *substr,int *arr)
{
	int substr_count=0,i=0;
	char *tok,*base,str[300];
	strcpy(str,mainstr);
	tok=strtok(str,"&,?.: ;\n\t+-*/%<>=!()[]");
	base=str;
	while(tok!=NULL)
	{
		if( ! ( strcmp(substr,tok) ) )
		{
			substr_count++;
			arr[i++]=tok-base;
		}
		tok=strtok(NULL,"&,?.: ;\n\t+-*/%<>=!()[]");
	}
	
	return substr_count;
}

void extract_variables(char *mainstr,char *substr,char var_str[100][100],int *var_count)
{
	char *tok1,*tok2,temp[300];
	
	if( ! (check_fn( mainstr) ) )
	{	
		tok1=strtok(mainstr," ,");
		while(tok1!=NULL)
		{
			printf("11111%s\n",tok1);
			strcpy(temp,tok1);
			printf("11111%s\n",tok1);
			
			tok2=strtok(temp,"&,?.: ;\n\t+-*/%<>=!()[]");
			strcpy( var_str[ *var_count ],tok2);
			*var_count+=1;	
			
			printf("3333333%s\n",tok2);
			
			tok1=strtok(NULL," ,");
		}	
	}
}


void get_line(FILE *fp,char *str)
{
	char ch;
	int i=0;
	ch=fgetc(fp);
	while( !( (ch==EOF) || (ch=='\n') || (ch==';') ) )
	{
		str[i++]=ch;
		ch=getc(fp);
	}
	str[i]='\0';	
}

int check_fn(char *str)
{
	char temp[300];
	int i=0;
	strcpy(temp,str);
	while( (temp[i]>='a'&&temp[i]<='z')||(temp[i]>='1'&&temp[i]<='9')||(temp[i]>='A'&&temp[i]<='Z')||(temp[i]=='_')||(temp[i]==' ') )
	i++;
	if(temp[i]=='(')
		return 1;
	return 0;
}
