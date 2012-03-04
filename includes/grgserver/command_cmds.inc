CMD:cmds(playerid, params[] , "Liste mit Befehlen anzeigen")
{
	if (fexist(FILE_COMMANDS))
	{
		new string[256];
		new File:file = fopen(FILE_COMMANDS, io_read);
		while (fread(file, string))
		{
			new type;
			new command[MAX_FUNC_NAME];
			new infoText[256];
			new permission[30];
			RemoveNewLine(string);
			if (sscanf(string, "css", type, command, permission))
			{
				sscanf(string, "cs", type, command);
			}
			if (type)
			{
				new showCommand;
				fread(file, infoText);
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
						if (permissions[playerid][enum_permission:permissionID])
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
					Format:string("%s{FF8C55} - %s", command, infoText);
					SendClientMessage(playerid, COLOR_INFO, string);
				}
			}
		}
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ERROR;
	}
}