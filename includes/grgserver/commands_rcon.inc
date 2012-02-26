RCMD:cmds(params[], "List available RCON commands")
{
	if (fexist("commands.txt"))
	{
		new string[256];
		new File:commands = fopen("commands.txt", io_read);
		while (fread(commands, string))
		{
			new type;
			RemoveNewLine(string);
			sscanf(string, "cs", type, string);
			if (type == 'R')
			{
				printf(string);
			}
		}
	}
	return true;
}

RCMD:reloadpermissions(params[], "Reload all permissions from database")
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

RCMD:reloadpickups(params[], "Reload all pickups from database")
{
	print("Reloading pickups...");
	ReloadPickups();
	print("Done");
	return true;
}

RCMD:showmysqlinfo(params[], "Show various information about the MySQL connection (i.e. number of occured warnings)")
{
	printf("Number of warnings: %d", mysql_warning_count());
	return true;
}