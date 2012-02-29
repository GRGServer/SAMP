public OnPlayerConnect(playerid)
{
	if (IsPlayerNPC(playerid))
	{
		new npcName[MAX_PLAYER_NAME];
		GetPlayerName(playerid, npcName, sizeof(npcName));
		strdel(npcName, 4, strlen(npcName));
		MySQLQuery("SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(npcName));
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
				vehicleID = CreateVehicle(modelID, 0.0, 0.0, 0.0, 0.0, random(127), random(127), 1);
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
		MySQLQuery("SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_store_result();
		if (strval(GetMySQLField("UserID")))
		{
			ShowDialog(playerid, DIALOG_LOGIN);
		}
		else
		{
			ShowDialog(playerid, DIALOG_REGISTER_STEP1);
		}
		mysql_free_result();
		SendClientMessage(playerid, COLOR_SYSTEM, "Willkommen auf GRG Server!");
		FormatNew:string[70]("Auf diesem Server läuft aktuell Revision %d unserer Gamemode.", COMPILER_SVN_REVISION);
		SendClientMessage(playerid, COLOR_SYSTEM, string);
		Format:string("%s hat den Server betreten", GetPlayerNameEx(playerid));
		SendClientMessageToAllExcept(playerid, COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		textDrawSpeedoName[playerid] = TextDrawCreate(480, 400, "_");
		TextDrawAlignment(textDrawSpeedoName[playerid], 1);
		TextDrawLetterSize(textDrawSpeedoName[playerid], 0.3, 0.9);
		TextDrawFont(textDrawSpeedoName[playerid], 1);
		TextDrawSetShadow(textDrawSpeedoName[playerid], 2);
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
		FormatNew:string[MAX_PLAYER_NAME + 30]("%s hat den Server verlassen", GetPlayerNameEx(playerid));
		SendClientMessageToAll(COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		TextDrawHideForPlayer(playerid, textDrawSpeedoColumn1);
		TextDrawHideForPlayer(playerid, textDrawClock);
		TextDrawDestroy(textDrawSpeedoName[playerid]);
		TextDrawDestroy(textDrawSpeedoColumn2[playerid]);
		TextDrawDestroy(textDrawRadioStation[playerid]);
	}
	return true;
}