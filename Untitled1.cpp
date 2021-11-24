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




tok=strtok(mainstr,"&,?.: ;\n\t+-*/%<>=!()[]");
		while(tok!=NULL)
		{
			if( ( strcmp(substr,tok) ) )
			{
				strcpy( var_str[ *var_count ],tok);
				*var_count+=1;
			}
			tok=strtok( NULL,"&,?.: ;\n\t+-*/%<>=!()[]");
		}
