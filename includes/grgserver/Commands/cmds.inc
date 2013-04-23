CMD:cmds(playerID, params[], StringID:93(""))
{
	if (fexist(FILE_COMMANDS))
	{
		new string[256];
		new File:file = fopen(FILE_COMMANDS, io_read);
		while (fread(file, string))
		{
			new command[MAX_FUNCTION_NAME];
			new languageStringID;
			new permission[30];
			RemoveNewLine(string);
			if (sscanf(string, "p<\t>s[" #MAX_FUNCTION_NAME "]s[30]d", command, permission, languageStringID))
			{
				if (sscanf(string, "p<\t>s[" #MAX_FUNCTION_NAME "]d", command, languageStringID))
				{
					continue;
				}
			}
			new showCommand;
			if (strlen(permission))
			{
				new permissionID = GetPermissionByName(permission);
				if (permissionID != -1)
				{
					if (permissions[playerID][enum_permission:permissionID])
					{
						showCommand = true;
						Format:command("{A00000}/%s", command);
					}
				}
			}
			else
			{
				showCommand = true;
				Format:command("{00FF00}/%s", command);
			}
			if (showCommand)
			{
				Format:string("%s{FF8C55} - %s", command, LanguageString(playerID, languageStringID));
				SendClientMessage(playerID, COLOR_INFO, string);
			}
		}
		SendClientMessageEx(playerID, COLOR_INFO, StringID:522(""));
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ERROR;
	}
}