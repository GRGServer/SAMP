RCMD:cmds(params[], 149)
{
	if (fexist(FILE_COMMANDS))
	{
		new string[256];
		new File:file = fopen(FILE_COMMANDS, io_read);
		print("Available commands:");
		while (fread(file, string))
		{
			new type;
			new languageStringID;
			RemoveNewLine(string);
			sscanf(string, "csd", type, string, languageStringID);
			if (type == 'R')
			{
				printf("  %s - %s", string, languageStrings[languageStringID][LANGUAGESTRING_ENGLISH]);
			}
		}
	}
	return true;
}