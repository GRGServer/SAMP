CMD:cmds(playerID, params[] , 93)
{
	if (fexist(FILE_COMMANDS))
	{
		new string[256];
		new File:file = fopen(FILE_COMMANDS, io_read);
		while (fread(file, string))
		{
			new command[MAX_FUNCTION_NAME];
			new languageStringName[STRINGLENGTH_LANGUAGESTRINGNAME];
			new permission[30];
			RemoveNewLine(string);
			if (sscanf(string, "p<\t>s[" #MAX_FUNCTION_NAME "]s[30]s[" #STRINGLENGTH_LANGUAGESTRINGNAME "]", command, permission, languageStringName))
			{
				if (sscanf(string, "p<\t>s[" #MAX_FUNCTION_NAME "]s[" #STRINGLENGTH_LANGUAGESTRINGNAME "]", command, languageStringName))
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
				/* TODO: Show command list in two columns
				new commandLength = strlen(command);
				for (new character = 0; character < MAX_FUNCTION_NAME; character++)
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
		SendClientMessageEx(playerID, COLOR_INFO, "522");
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ERROR;
	}
}