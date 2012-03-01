RCMD:cmds(params[], "List available RCON commands")
{
	if (fexist("commands.txt"))
	{
		new string[256];
		new infoText[256];
		new File:commands = fopen("commands.txt", io_read);
		print("Available commands:");
		while (fread(commands, string))
		{
			new type;
			fread(commands, infoText);
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

RCMD:reconnectnpcs(params[], "Reconnect all NPCs")
{
	Exec:ReconnectNPCs();
	return true;
}

RCMD:reloadpermissions(params[], "Reload all permissions from database")
{
	Exec:ReloadPermissions();
	return true;
}

RCMD:reloadpickups(params[], "Reload all pickups from database")
{
	Exec:ReloadPickups();
	return true;
}

RCMD:reloadsavedvehicles(params[], "Reload all saved vehicles from database")
{
	Exec:ReloadSavedVehicles();
	return true;
}

RCMD:reloadvehiclemodels(params[], "Reload all vehicle models from database")
{
	Exec:ReloadVehicleModels();
	return true;
}

RCMD:showmysqlinfo(params[], "Show various information about the MySQL connection (i.e. number of occured warnings)")
{
	printf("Number of warnings: %d", mysql_warning_count());
	return true;
}