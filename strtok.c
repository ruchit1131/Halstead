#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	char str[100]="abc qwe,ee 6ile7 ww,we, \n\n, ,erff,f  ";
	char *tok;
	tok=strtok(str,", \n");
	
	while(tok!=NULL)
	{
		printf("%s\n",tok);
		tok=strtok(NULL,", \n");
	}
	
	
}
