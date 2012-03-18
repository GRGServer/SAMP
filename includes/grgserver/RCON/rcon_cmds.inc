RCMD:cmds(params[], 149)
{
	if (fexist(FILE_COMMANDS))
	{
		new string[256];
		new infoText[256];
		new File:file = fopen(FILE_COMMANDS, io_read);
		print("Available commands:");
		while (fread(file, string))
		{
			new type;
			fread(file, infoText);
			RemoveNewLine(string);
			RemoveNewLine(infoText);
			sscanf(string, "cs", type, string);
			if (type == 'R')
			{
				printf("  %s - %s", string, infoText);
			}
		}
	}
	return true;
}