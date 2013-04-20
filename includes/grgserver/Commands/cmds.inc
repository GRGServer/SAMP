CMD:cmds(playerID, params[] , 93)
{
	if (fexist(FILE_COMMANDS))
	{
		new string[256];
		new File:file = fopen(FILE_COMMANDS, io_read);
		while (fread(file, string))
		{
			new type;
			new command[MAX_FUNCTION_NAME];
			new languageStringName[100];
			new permission[30];
			RemoveNewLine(string);
			if (sscanf(string, "p\tcsss", type, command, permission, languageStringName))
			{
				sscanf(string, "p\tcss", type, command, languageStringName);
			}
			if (type)
			{
				new showCommand;
				if (type == '-')
				{
					showCommand = true;
					Format:command("{00FF00}/%s", command);
				}
				if (type == 'P' && strlen(permission))
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
				if (showCommand)
				{
					/* TODO: Show command list in two columns
					new commandLength = strlen(command);
					for (new character = 0; character < MAX_FUNC_NAME; character++)
					{
						if (character >= commandLength)
						{
							command[character] = ' ';
						}
					}*/
					Format:string("%s{FF8C55} - %s", command, LanguageString(playerID, languageStringName));
					SendClientMessage(playerID, COLOR_INFO, string);
				}
			}
		}
		SendClientMessageEx(playerID, COLOR_INFO, "522");
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ERROR;
	}
}