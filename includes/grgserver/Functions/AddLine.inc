AddLine(string[], line[], stringSize = sizeof(string))
{
	if (strlen(string))
	{
		format(string, stringSize, "%s\n", string);
	}
	strcat(string, line, stringSize);
}