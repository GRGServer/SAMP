CMD:about(playerid, params[], "Informationen über dieses Script")
{
	SendClientMessage(playerid, COLOR_INFO, "Erstellt von Aerox_Tobi (aerox@grgserver.net) und Programie (programie@selfcoders.com)");
	return COMMAND_OK;
}
CMD:accept(playerid, params[], "Annehmen eines Auftrages")
{
	switch (GetPVar:playerid[JOBID])
	{
		case JOB_ADAC, JOB_AMBULANCE, JOB_POLICE, JOB_TRUCKER:
			ShowDialog(playerid, DIALOG_ACCEPT);
		default:
			return COMMAND_PERMISSION_DENIED;
	}
	return COMMAND_OK;
}

CMD:changepw(playerid, params[], "Accountpasswort ändern")
{
	ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP1);
	return COMMAND_OK;
}

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

CMD:exit(playerid, params[], "Gebäude verlassen")
{
	if (GetPVar:playerid[SHOWINTERIOR_OLDINTERIOR] == -1)
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
		SetPlayerPos(playerid, GetPVar:playerid[SHOWINTERIOR_OLDPOSX], GetPVar:playerid[SHOWINTERIOR_OLDPOSY], GetPVar:playerid[SHOWINTERIOR_OLDPOSZ]);
		SetPlayerInterior(playerid, GetPVar:playerid[SHOWINTERIOR_OLDINTERIOR]);
		SetPVar:playerid[SHOWINTERIOR_OLDINTERIOR](-1);
		return COMMAND_OK;
	}
}

CMD:getbalance(playerid, params[], "Kontostand anzeigen")
{
	new string[256];
	Format:string("Aktueller Kontostand: $%s", FormatMoney(GetPVar:playerid[MONEY]));
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
	if (!CheckVehiclePermission(playerid, vehicleID))
	{
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
	if (GetPVar:playerid[JOBID] == JOB_VEHICLEDEALER)
	{
		ShowDialog(playerid, DIALOG_ORDERVEHICLE);
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
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

CMD:teststart(playerid, params[], "Startsequenz nach dem Registrieren testen")
{
	TeleportTo(playerid, 1.7414, 31.6997, 1199.6012, 177.4850, 1, playerid);
	SetPlayerCheckpointEx(playerid, CHECKPOINT_WALKTOSEAT);
	return COMMAND_OK;
}

CMD:testunfreeze(playerid, params[], "Steuerungsbehinderung aufheben")
{
	TogglePlayerControllable(playerid, true);
	return COMMAND_OK;
}