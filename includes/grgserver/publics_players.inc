public OnPlayerConnect(playerid)
{
	new query[256];
	if (IsPlayerNPC(playerid))
	{
		format(query, sizeof(query), "SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_query(query);
		mysql_store_result();
		if (strval(GetMySQLField("StartOnConnect")))
		{
			new modelID;
			new playbackType;
			new vehicleID;
			modelID = strval(GetMySQLField("VehicleModelID"));
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
			StartNPCPlayback(playerid, GetMySQLField("Recording"), playbackType, strval(GetMySQLField("AutoRepeat")));
		}
		mysql_free_result();
	}
	else
	{
		format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_query(query);
		mysql_store_result();
		if (strval(GetMySQLField("UserID")))
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
		format(string, sizeof(string), "%s hat den Server betreten", GetPlayerNameEx(playerid));
		SendClientMessageToAllExcept(playerid, COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		textDrawSpeedoColumn2[playerid] = TextDrawCreate(580, 400, "_");
		TextDrawAlignment(textDrawSpeedoColumn2[playerid], 1);
		TextDrawLetterSize(textDrawSpeedoColumn2[playerid], 0.3, 0.9);
		TextDrawFont(textDrawSpeedoColumn2[playerid], 1);
		TextDrawSetShadow(textDrawSpeedoColumn2[playerid], 2);
		TextDrawTextSize(textDrawSpeedoColumn2[playerid], 635, 475);
		TextDrawShowForPlayer(playerid, textDrawClock);
		TextDrawShowForPlayer(playerid, textDrawBottomBanner);
	}
	return true;
}

public OnPlayerPickUpPickup(playerid,pickupid)
{
	switch (pickups[pickupid][pickups_type])
	{
		case PICKUPTYPE_BANK:
		{
			SendClientMessage(playerid, COLOR_INFO, "Du stehst in einem Bank Pickup");
		}
		case PICKUPTYPE_GASSTATION:
		{
			new vehicleID = GetPlayerVehicleID(playerid);
			new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][vehicleModels_maxFuel], vehicles[vehicleID][vehicles_currentFuel]);
			if (maximum > 0)
			{
				new string[256];
				format(string, sizeof(string), "Wie viel möchtest du tanken (0 - %s)?", FormatNumber(maximum, 2, 0, '.'));
				ShowPlayerDialog(playerid, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Tanken", string, "Tanken", "Abbrechen");
			}
			else
			{
				SendClientMessage(playerid, COLOR_ERROR, "Der Tank ist bereits voll!");
			}
		}
	}
	return true;
}

public OnPlayerDisconnect(playerid, reason)
{
	if (!IsPlayerNPC(playerid))
	{
		if (GetPVarInt(playerid, "UserID"))
		{
			SavePlayer(playerid);
		}
		new string[256];
		format(string, sizeof(string), "%s hat den Server verlassen", GetPlayerNameEx(playerid));
		SendClientMessageToAll(COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		TextDrawHideForPlayer(playerid, textDrawSpeedoColumn1);
		TextDrawHideForPlayer(playerid, textDrawClock);
		TextDrawHideForPlayer(playerid, textDrawBottomBanner);
		TextDrawDestroy(textDrawSpeedoColumn2[playerid]);
	}
	return true;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ);
	SetPlayerCameraPos(playerid, SPAWN_CAMERAPOSX, SPAWN_CAMERAPOSY, SPAWN_CAMERAPOSZ);
	SetPlayerCameraLookAt(playerid, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ);
	return true;
}

public OnPlayerSpawn(playerid)
{
	if (!GetPVarInt(playerid, "WasSpawned"))
	{
		LoadPlayer(playerid);
		SetPVarInt(playerid, "WasSpawned", true);
	}
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
				new saveID = vehicles[GetPlayerVehicleID(playerid)][vehicles_saveID];
				new Float:price = floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(saveID)));
				if (price <= GetPVarFloat(playerid, "Money"))
				{
					SetPlayerMoney(playerid, floatsub(GetPVarFloat(playerid, "Money"), price));
					SetMySQLValue("savedvehicles", "ownerUserID", val2str(GetPVarInt(playerid, "UserID")), "ID", val2str(saveID));
					SavePlayer(playerid);
				}
				else
				{
					format(string,sizeof(string), "Du benötigst $%f für dieses Fahrzeug! Leider hast du nur $%f.", price, GetPVarFloat(playerid, "Money"));
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
					format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(playerName));
					mysql_query(query);
					mysql_store_result();
					if (!strcmp(MD5(inputtext), GetMySQLField("Password"), true))
					{
						SetPVarInt(playerid, "UserID", strval(GetMySQLField("UserID")));
					}
					else
					{
						ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Das angegebene Passwort ist falsch!\nBtte versuche es erneut.", "OK", "Abbrechen");
					}
					mysql_free_result();
					if (GetPVarInt(playerid, "UserID"))
					{
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
		case DIALOG_REFUEL:
		{
			if (response && strlen(inputtext))
			{
				new Float:amount = floatstr(inputtext);
				new vehicleID = GetPlayerVehicleID(playerid);
				new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][vehicleModels_maxFuel], vehicles[vehicleID][vehicles_currentFuel]);
				if (amount > maximum)
				{
					amount = maximum;
				}
				TogglePlayerControllable(playerid, false);
				SetVehicleEngineState(vehicleID, false);
				GameTextForPlayer(playerid, "Dein Fahrzeug wird getankt. Bitte warten...", 3000, 4);
				timer_refuelVehicle(playerid, amount);
			}
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
					format(query, sizeof(query), "INSERT INTO `users` (`Username`, `Password`, `RegisterTime`) VALUES ('%s', '%s', NOW())", MySQLEscapeString(playerName), MD5(inputtext));
					mysql_query(query);
					SetPVarInt(playerid, "UserID", mysql_insert_id());
					SetPVarInt(playerid, "Level", REGISTER_LEVEL);
					SetPVarInt(playerid, "AdminLevel", REGISTER_ADMINLEVEL);
					SavePlayer(playerid);
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
			printf("%s tried to execute %s with admin level %d but has not the required permission!", GetPlayerNameEx(playerid), cmdtext, GetPVarInt(playerid, "AdminLevel"));
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
	format(string, sizeof(string), "[%s] %s", GetPlayerNameEx(playerid), text);
	IRC_Say(ircBot, IRC_CHANNEL, string);
	SendClientMessageToAllExcept(playerid, COLOR_CHAT, string);
	SendClientMessage(playerid, COLOR_CHATOWN, string);
	WriteChatToDatabase(playerid, text);
	return false;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (!ispassenger && !IsPlayerNPC(playerid))
	{
		SetVehicleEngineState(vehicleid, false);
	}
	if (!ispassenger)
	{
		if (vehicles[vehicleid][vehicles_saveID])
		{
			new string[256];
			new ownerUserID = strval(GetMySQLValue("savedvehicles", "OwnerUserID", "ID", val2str(vehicles[vehicleid][vehicles_saveID])));
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
				format(string,sizeof(string), "Möchtest du dieses Fahrzeug Kaufen?\nDies kostet $%s", GetMySQLValue("savedvehicles", "Price", "ID", val2str(vehicles[vehicleid][vehicles_saveID])));
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
		SetVehicleEngineState(vehicleid, false);
	}
	if (vehicles[vehicleid][vehicles_saveID])
	{
		new query[256];
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		GetVehiclePos(vehicleid, posX, posY, posZ);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Interior` = '%d', `CurrentFuel` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, GetPlayerInterior(playerid), vehicles[vehicleid][vehicles_currentFuel], vehicles[vehicleid][vehicles_saveID]);
		mysql_query(query);
	}
	return true;
}