#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int search_variale(char *mainstr,char *substr,int *arr);
int main()
{
	char 	mainstr[500]="           		abc+= abc+ abc1*(abc/abc1-abc2) , abc=abc+abcabc ;";
	char substr[50]="abc";
	int i,arr[100],count;
	count=search_variable(mainstr,substr,arr);
	for(i=0;i<count;i++)
		printf("variable %s is present at index %d\n",substr,arr[i]);
	return 0;
}
int search_variable(char *mainstr,char *substr,int *arr)
{
	int substr_count=0,i=0;
	char *tok,*base;
	tok=strtok(mainstr,"&,?.: ;\n\t+-*/%<>=!()[]");
	base=mainstr;
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

