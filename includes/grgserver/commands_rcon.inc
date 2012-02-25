RCMD:cmds(params[])
{
	if (fexist("commands.txt"))
	{
		new string[256];
		new line[256];
		new count;
		new File:commands = fopen("commands.txt", io_read);
		while (fread(commands, string))
		{
			new type;
			new command[256];
			RemoveNewLine(string);
			sscanf(string, "cs", type, command);
			if (type == 'R')
			{
				count++;
				if (count == 1)
				{
					Format:line("%s", command);
				}
				else
				{
					Format:line("%s %s", line, command);
				}
				if (count == HELP_COMMANDSPERLINE)
				{
					count = 0;
					print(line);
				}
			}
		}
		if (!count)
		{
			print(line);
		}
	}
	return true;
}

RCMD:reloadpermissions(params[])
{
	print("Reloading permissions...");
	mysql_query("SELECT * FROM `permissions`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new playerID = strval(GetMySQLField("UserID"));
		if (playerID)
		{
			LoadPermission:ADMIN(playerID, "Admin");
			LoadPermission:MAPPER(playerID, "Mapper");
			LoadPermission:MODERATOR(playerID, "Moderator");
			LoadPermission:NPCADMIN(playerID, "NPCAdmin");
			LoadPermission:SERVERADMIN(playerID, "ServerAdmin");
			LoadPermission:TELEPORT(playerID, "Teleport");
		}
	}
	mysql_free_result();
	print("Done");
	return true;
}

RCMD:reloadpickups(params[])
{
	print("Reloading pickups...");
	ReloadPickups();
	print("Done");
	return true;
}

RCMD:showmysqlinfo(params[])
{
	printf("Number of warnings: %d", mysql_warning_count());
	return true;
}