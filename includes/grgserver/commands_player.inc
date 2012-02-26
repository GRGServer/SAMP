CMD:about(playerid, params[], "Informationen über dieses Script")
{
	SendClientMessage(playerid, COLOR_INFO, "Erstellt von Aerox_Tobi (aerox@grgserver.net) und Programie (programie@selfcoders.com)");
	return COMMAND_OK;
}

CMD:cmds(playerid, params[] , "Liste mit Befehlen anzeigen")
{
	if (fexist("commands.txt"))
	{
		new string[256];
		new File:commands = fopen("commands.txt", io_read);
		while (fread(commands, string))
		{
			new type;
			new command[256];
			new infoText[256];
			new permission[256];
			RemoveNewLine(string);
			if (sscanf(string, "css", type, command, permission))
			{
				sscanf(string, "cs", type, command);
			}
			if (type)
			{
				new showCommand;
				fread(commands, infoText);
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

CMD:exit(playerid, params[], "Gebäude verlassen")
{
	if (GetPVarType(playerid, "ShowInterior_OldInterior") == PLAYER_VARTYPE_NONE)
	{
		if (LeaveBuilding(playerid))
		{
			return COMMAND_OK;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Du bist in keinem Haus!");
			return COMMAND_ERROR;
		}
	}
	else
	{
		SetPlayerPos(playerid, GetPVarFloat(playerid, "ShowInterior_OldPosX"), GetPVarFloat(playerid, "ShowInterior_OldPosY"), GetPVarFloat(playerid, "ShowInterior_OldPosZ"));
		SetPlayerInterior(playerid, GetPVarInt(playerid, "ShowInterior_OldInterior"));
		DeletePVar(playerid, "ShowInterior_OldPosX");
		DeletePVar(playerid, "ShowInterior_OldPosY");
		DeletePVar(playerid, "ShowInterior_OldPosZ");
		DeletePVar(playerid, "ShowInterior_OldInterior");
		return COMMAND_OK;
	}
}

CMD:getbalance(playerid, params[], "Kontostand anzeigen")
{
	new string[256];
	Format:string("Aktueller Kontostand: $%s", FormatMoney(GetPlayerMoneyEx(playerid)));
	SendClientMessage(playerid, COLOR_INFO, string);
	return COMMAND_OK;
}

CMD:help(playerid, params[], "Hilfe anzeigen")
{
	SendClientMessage(playerid, COLOR_INFO, "Verwende /cmds um eine Liste an Befehlen zu sehen.");
	return COMMAND_OK;
}

CMD:me(playerid, params[], "Sagen, was du machst (z.B. '/me rennt Admin hinterher' sehen alle Spieler als '*<Dein Name> rennt Admin hinterher')")
{
	if (strlen(params))
	{
		new string[256];
		Format:string("*%s %s", GetPlayerNameEx(playerid), params);
		SendClientMessageToAll(COLOR_ME, string);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "me", "Text");
		return COMMAND_USAGE;
	}
}

CMD:motor(playerid, params[], "Starten oder stoppen des Motors deines Fahrzeugs")
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
	if (!vehicles[vehicleID][VEHICLE_SAVEID] && !permissions[playerid][PERMISSION_MAPPER])
	{
		SendClientMessage(playerid, COLOR_ERROR, "Dieses Fahrzeug kann nur von der Gruppe 'Mapper' verwendet werden!");
		RemovePlayerFromVehicle(playerid);
		return COMMAND_ERROR;
	}
	new ownerUserID = strval(GetMySQLValue("savedvehicles", "OwnerUserID", "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID])));
	if (!ownerUserID)
	{
		ShowDialog(playerid, DIALOG_BUYVEHICLE, FormatMoney(floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID])))));
		return COMMAND_OK;
	}
	if (ownerUserID != GetUserID(playerid))
	{
		SendClientMessage(playerid, COLOR_ERROR, "Dieses Fahrzeug besitzt bereits ein anderer Spieler");
		RemovePlayerFromVehicle(playerid);
		return COMMAND_ERROR;
	}
	if (GetVehicleEngineState(vehicleID))
	{
		SetVehicleEngineState(vehicleID, false);
		SendClientMessage(playerid, COLOR_INFO, "Der Motor deines Fahrzeuges wurde ausgeschalten.");
		return COMMAND_OK;
	}
	new Float:health;
	GetVehicleHealth(vehicleID, health);
	if (health >= VEHICLE_MINHEALTH)
	{
		SetVehicleEngineState(vehicleID, true);
		SendClientMessage(playerid, COLOR_INFO, "Der Motor deines Fahrzeuges wurde gestartet.");
		return COMMAND_OK;
	}
	SendClientMessage(playerid, COLOR_ERROR, "Der Motor deines Fahrzeuges konnte nicht gestartet werden (Motorschaden)!");
	return COMMAND_ERROR;
}

CMD:ordervehicle(playerid, params[], "Fahrzeug bestellen")
{
	new JobID = GetPVarInt(playerid, "JobID");
	if (JobID == JOB_VEHICLEDEALER)
	{
		ShowDialog(playerid, DIALOG_ORDERVEHICLE);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PERMISSION_DENIED;
	}
}

CMD:radio(playerid, params[], "Webradio aktivieren")
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

CMD:stats(playerid, params[], "Informationen über deinen Spieler anzeigen")
{
	ShowDialog(playerid, DIALOG_STATS);
	return COMMAND_OK;
}