public OnPlayerConnect(playerid)
{
	new query[256];
	if (IsPlayerNPC(playerid))
	{
		format(query, sizeof(query), "SELECT * FROM `npcs` WHERE `Name` = '%s'", mySQLEscapeString(getPlayerName(playerid)));
		mysql_query(query);
		mysql_store_result();
		if (strval(getMySQLField("StartOnConnect")))
		{
			new modelID;
			new playbackType;
			new vehicleID;
			modelID = strval(getMySQLField("VehicleModelID"));
			if (modelID)
			{
				playbackType = PLAYER_RECORDING_TYPE_DRIVER;
				vehicleID = CreateVehicle(modelID, 0.0, 0.0, 0.0, 0.0, random(126), random(126), 1);
				PutPlayerInVehicle(playerid, vehicleID, 0);
				SetPVarInt(playerid, "VehicleID", vehicleID);
			}
			else
			{
				playbackType = PLAYER_RECORDING_TYPE_ONFOOT;
			}
			startNPCPlayback(playerid, getMySQLField("Recording"), playbackType, strval(getMySQLField("AutoRepeat")));
		}
		mysql_free_result();
	}
	else
	{
		format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s'", mySQLEscapeString(getPlayerName(playerid)));
		mysql_query(query);
		mysql_store_result();
		if (strval(getMySQLField("UserID")))
		{
			ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Bitte gebe das Passwort von deinen Account ein.", "OK", "Abbrechen");
		}
		else
		{
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Registrieren", "Du bist noch nicht registriert!\nBitte gebe ein neues Passwort für deinen Account ein.", "OK", "Abbrechen");
		}
		mysql_free_result();
		new string[256];
		SendClientMessage(playerid, COLOR_SYSTEM, "Willkommen auf GRG Server!");
		format(string, sizeof(string), "Auf diesem Server läuft aktuell Revision %d unserer Gamemode.", COMPILER_SVN_REVISION);
		SendClientMessage(playerid, COLOR_SYSTEM, string);
		format(string, sizeof(string), "%s hat den Server betreten", getPlayerName(playerid));
		sendClientMessageToAllExcept(playerid, COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		textDrawSpeedo[playerid] = TextDrawCreate(500, 400, "_");
		TextDrawAlignment(textDrawSpeedo[playerid], 1);
		TextDrawLetterSize(textDrawSpeedo[playerid], 0.3, 0.9);
		TextDrawFont(textDrawSpeedo[playerid], 1);
		TextDrawSetShadow(textDrawSpeedo[playerid], 2);
		TextDrawTextSize(textDrawSpeedo[playerid], 635, 475);
		TextDrawBoxColor(textDrawSpeedo[playerid], 0x00000080);
		TextDrawUseBox(textDrawSpeedo[playerid], true);
	}
	return true;
}

public OnPlayerDisconnect(playerid, reason)
{
	if (!IsPlayerNPC(playerid))
	{
		if (GetPVarInt(playerid, "UserID"))
		{
			savePlayer(playerid);
		}
		new string[256];
		format(string, sizeof(string), "%s hat den Server verlassen", getPlayerName(playerid));
		SendClientMessageToAll(COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		TextDrawDestroy(textDrawSpeedo[playerid]);
	}
	return true;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return true;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case DIALOG_BUYVEHICLE:
		{
			if (response)
			{
				new string[256];
				new vehicleID = vehicles[GetPlayerVehicleID(playerid)];
				new price = strval(getMySQLValue("savedvehicles", "Price", "ID", val2str(vehicleID)));
				if (price <= GetPlayerMoney(playerid))
				{
					GivePlayerMoney(playerid, -price);
					setMySQLValue("savedvehicles", "ownerUserID", val2str(GetPVarInt(playerid, "UserID")), "ID", val2str(vehicleID));
					savePlayer(playerid);
				}
				else
				{
					format(string,sizeof(string), "Du benötigst $%d für dieses Fahrzeug! Leider hast du nur $%d.", price, GetPlayerMoney(playerid));
					SendClientMessage(playerid, COLOR_ERROR, string);
					RemovePlayerFromVehicle(playerid);
				}
			}
			else
			{
				RemovePlayerFromVehicle(playerid);
			}
		}
		case DIALOG_LOGIN:
		{
			if (response)
			{
				if (strlen(inputtext))
				{
					new playerName[MAX_PLAYER_NAME];
					new query[256];
					GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
					format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s'", mySQLEscapeString(playerName));
					mysql_query(query);
					mysql_store_result();
					if (!strcmp(md5(inputtext), getMySQLField("Password"), true))
					{
						SetPVarInt(playerid, "UserID", strval(getMySQLField("UserID")));
					}
					else
					{
						ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Das angegebene Passwort ist falsch!\nBtte versuche es erneut.", "OK", "Abbrechen");
					}
					mysql_free_result();
					if (GetPVarInt(playerid, "UserID"))
					{
						loadPlayer(playerid);
						format(query, sizeof(query), "UPDATE `users` SET `LoginTime` = NOW() WHERE `UserID` = '%d'", GetPVarInt(playerid, "UserID"));
						mysql_query(query);
						printf("Player logged in: %s (UserID: %d)", playerName, GetPVarInt(playerid, "UserID"));
						SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich eingeloggt.");
						SpawnPlayer(playerid);
					}
				}
				else
				{
					ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Kein Passwort eingegeben!\nBitte versuche es erneut.", "OK", "Abbrechen");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_INFO, "Du kannst nun das Spiel beenden!");
				Kick(playerid);
			}
			return true;
		}
		case DIALOG_REGISTER:
		{
			if (response)
			{
				if (strlen(inputtext) >= REGISTER_MINPASSWORD && strlen(inputtext) <= REGISTER_MAXPASSWORD)
				{
					new query[256];
					new playerName[MAX_PLAYER_NAME];
					GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
					format(query, sizeof(query), "INSERT INTO `users` (`Username`, `Password`, `RegisterTime`) VALUES ('%s', '%s', NOW())", mySQLEscapeString(playerName), md5(inputtext));
					mysql_query(query);
					SetPVarInt(playerid, "UserID", mysql_insert_id());
					SetPVarInt(playerid, "Level", REGISTER_LEVEL);
					SetPVarInt(playerid, "AdminLevel", REGISTER_ADMINLEVEL);
					savePlayer(playerid);
					printf("Player registered: %s (UserID: %d)", playerName, GetPVarInt(playerid, "UserID"));
					SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich registriert und bist nun eingeloggt.");
					SpawnPlayer(playerid);
				}
				else
				{
					new string[256];
					format(string, sizeof(string), "Bitte verwende ein Passwort mit einer Länge zwischen %d und %d Zeichen!", REGISTER_MINPASSWORD, REGISTER_MAXPASSWORD);
					ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Registrieren", string, "OK", "Abbrechen");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_INFO, "Du kannst nun das Spiel beenden!");
				Kick(playerid);
			}
			return true;
		}
	}

	return false;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	switch (success)
	{
		case COMMAND_ERROR:
			SendClientMessage(playerid, COLOR_ERROR, "Fehler bei der Befehlsausführung!");
		case COMMAND_USAGE:
			return true;// Command usage message displayed -> Nothing to do yet
		case COMMAND_OK:
			return true;// Command executed successfully -> Do nothing
		case COMMAND_TELEPORTED:
			SendClientMessage(playerid, COLOR_INFO, "Du wurdest teleportiert!");
		case COMMAND_NPC_ONLY:
			SendClientMessage(playerid, COLOR_ERROR, "Diese Befehl ist nur für NPCs verfügbar!");
		case COMMAND_NOT_IN_VEHICLE:
			SendClientMessage(playerid, COLOR_ERROR, "Du bist nicht in einem Fahrzeug!");
		case COMMAND_ACCESS_DENIED:
		{
			SendClientMessage(playerid, COLOR_ERROR, "Du hast nicht die nötigen Rechte um diesen Befehl zu verwenden!");
			printf("%s tried to execute %s with admin level %d but has not the required permission!", getPlayerName(playerid), cmdtext, GetPVarInt(playerid, "AdminLevel"));
		}
		case COMMAND_NOT_FOUND:
			return false;
		default:
			printf("Unknown command return code from %s", cmdtext);
	}
	return true;
}

public OnPlayerText(playerid, text[])
{
	new string[256];
	format(string, sizeof(string), "[%s] %s", getPlayerName(playerid), text);
	IRC_Say(ircBot, IRC_CHANNEL, string);
	sendClientMessageToAllExcept(playerid, COLOR_CHAT, string);
	SendClientMessage(playerid, COLOR_CHATOWN, string);
	writeChatToDatabase(playerid, text);
	return false;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (!ispassenger && !IsPlayerNPC(playerid))
	{
		setVehicleEngineState(vehicleid, false);
	}
	if (!ispassenger)
	{
		if (vehicles[vehicleid])
		{
			new string[256];
			new ownerUserID = strval(getMySQLValue("savedvehicles", "OwnerUserID", "ID", val2str(vehicles[vehicleid])));
			if (ownerUserID == GetPVarInt(playerid, "UserID"))
			{
				return true;
			}
			if (ownerUserID)
			{
				SendClientMessage(playerid, COLOR_ERROR, "Dieses Fahrzeug besitzt bereits ein anderer Spieler");
				RemovePlayerFromVehicle(playerid);
			}
			else
			{
				format(string,sizeof(string), "Möchtest du dieses Fahrzeug Kaufen?\nDies kostet $%s", getMySQLValue("savedvehicles", "Price", "ID", val2str(vehicles[vehicleid])));
				ShowPlayerDialog(playerid, DIALOG_BUYVEHICLE,DIALOG_STYLE_MSGBOX, "Fahrzeug Kaufen", string, "Ja", "Nein");
			}
		}
	}
	return true;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsPlayerNPC(playerid))
	{
		setVehicleEngineState(vehicleid, false);
	}
	if (vehicles[vehicleid])
	{
		new query[256];
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		GetVehiclePos(vehicleid, posX, posY, posZ);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Interior` = '%d' WHERE `ID` = '%d'", posX, posY, posZ, GetPlayerInterior(playerid), vehicles[vehicleid]);
		mysql_query(query);
	}
	return true;
}