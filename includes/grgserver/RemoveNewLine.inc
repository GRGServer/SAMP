RemoveNewLine(string[])
{
	new length = strlen(string);
	while (length-- && string[length] <= ' ')
	{
		string[length] = '\0';
	}
}