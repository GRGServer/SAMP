CMD:about(playerid, params[])
{
	SendClientMessage(playerid, COLOR_INFO, "Created by Aerox_Tobi (aerox@grgserver.net) and Programie (programie@selfcoders.com)");
	return COMMAND_OK;
}

CMD:cmds(playerid, params[])
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
			if (!sscanf(string, "cs", type, command))
			{
				new showCommand;
				if (type == 'P')
				{
					showCommand = true;
					format(command, sizeof(command), "{00FF00}%s", command);
				}
				if (type == 'A' && IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
				{
					showCommand = true;
					format(command, sizeof(command), "{A00000}%s", command);
				}
				if (showCommand)
				{
					count++;
					if (count == 1)
					{
						format(line, sizeof(line), "%s", command);
					}
					else
					{
						format(line, sizeof(line), "%s %s", line, command);
					}
					if (count == HELP_COMMANDSPERLINE)
					{
						count = 0;
						SendClientMessage(playerid, COLOR_INFO, line);
					}
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

CMD:exit(playerid, params[])
{
	new query[256];
	new currentBankID = GetPVarInt(playerid, "CurrentBankID");
	new currentHouseID = GetPVarInt(playerid, "CurrentHouseID");
	if (currentBankID || currentHouseID)
	{
		if (currentBankID)
		{
			format(query, sizeof(query), "SELECT * FROM `banks` WHERE `ID` = '%d'", currentBankID);
		}
		if (currentHouseID)
		{
			format(query, sizeof(query), "SELECT * FROM `houses` WHERE `ID` = '%d'", currentHouseID);
		}
		mysql_query(query);
		mysql_store_result();
		SetPlayerPos(playerid, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Du bist in keinem Haus!");
		return COMMAND_ERROR;
	}
}

CMD:help(playerid, params[])
{
	SendClientMessage(playerid, COLOR_INFO, "Verwende /cmds um eine Liste an Befehlen zu sehen.");
	return COMMAND_OK;
}

CMD:me(playerid, params[])
{
	if (strlen(params))
	{
		new string[256];
		format(string, sizeof(string), "*%s %s", GetPlayerNameEx(playerid), params);
		SendClientMessageToAll(COLOR_ME, string);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "me", "Text");
		return COMMAND_USAGE;
	}
}

CMD:motor(playerid, params[])
{
	if (!IsPlayerInAnyVehicle(playerid))
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, COLOR_ERROR, "Du bist nicht der Fahrer dieses Fahrzeugs!");
		return COMMAND_ERROR;
	}
	new vehicleID = GetPlayerVehicleID(playerid);
	if (GetVehicleEngineState(vehicleID))
	{
		SetVehicleEngineState(vehicleID, false);
		SendClientMessage(playerid, COLOR_INFO, "Der Motor deines Fahrzeuges wurde ausgeschalten.");
	}
	else
	{
		new Float:health;
		GetVehicleHealth(vehicleID, health);
		if (health < VEHICLE_MINHEALTH)
		{
			SendClientMessage(playerid, COLOR_ERROR, "Der Motor deines Fahrzeuges konnte nicht gestartet werden (Motorschaden)!");
		}
		else
		{
			SetVehicleEngineState(vehicleID, true);
			SendClientMessage(playerid, COLOR_INFO, "Der Motor deines Fahrzeuges wurde gestartet.");
		}
	}
	return COMMAND_OK;
}

CMD:ordervehicle(playerid, params[])
{
	new JobID = GetPVarInt(playerid, "JobID");
	if (JobID == JOB_VEHICLEDEALER)
	{
		ShowDialog(playerid, DIALOG_ORDERVEHICLE);
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
	return COMMAND_OK;
}

CMD:radio(playerid, params[])
{
	if (IsPlayerInAnyVehicle(playerid))
	{
		ShowDialog(playerid, DIALOG_RADIO);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
}