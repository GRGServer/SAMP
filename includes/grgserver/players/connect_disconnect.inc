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
		textDrawRadioStation[playerid] = TextDrawCreate(635, 435, "_");
		TextDrawAlignment(textDrawRadioStation[playerid], 3);
		TextDrawLetterSize(textDrawRadioStation[playerid], 0.3, 0.9);
		TextDrawFont(textDrawRadioStation[playerid], 1);
		TextDrawSetShadow(textDrawRadioStation[playerid], 2);
		TextDrawShowForPlayer(playerid, textDrawClock);
	}
	return true;
}

public OnPlayerDisconnect(playerid, reason)
{
	if (!IsPlayerNPC(playerid))
	{
		SavePlayer(playerid);
		new string[256];
		format(string, sizeof(string), "%s hat den Server verlassen", GetPlayerNameEx(playerid));
		SendClientMessageToAll(COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		TextDrawHideForPlayer(playerid, textDrawSpeedoColumn1);
		TextDrawHideForPlayer(playerid, textDrawClock);
		TextDrawDestroy(textDrawSpeedoColumn2[playerid]);
		TextDrawDestroy(textDrawRadioStation[playerid]);
	}
	return true;
}