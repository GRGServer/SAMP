public OnPlayerConnect(playerid)
{
	ResetPlayerVariables(playerid);
	if (IsPlayerNPC(playerid))
	{
		new ip[16];
		GetPlayerIp(playerid, ip, sizeof(ip));
		if (strcmp(ip, "127.0.0.1", true))
		{
			printf("External NPC connection from %s -> Banned", ip);
			BanEx(playerid, "External NPC connection");
			return false;
		}
		new npcName[MAX_PLAYER_NAME];
		GetPlayerName(playerid, npcName, sizeof(npcName));
		strdel(npcName, 0, 4);
		MySQLQuery("SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(npcName));
		mysql_store_result();
		SetPlayerSkin(playerid, strval(GetMySQLField("Skin")));
		new playbackType;
		new vehicleID = GetVehicleBySaveID(strval(GetMySQLField("VehicleID")));
		if (vehicleID)
		{
			playbackType = PLAYER_RECORDING_TYPE_DRIVER;
			PutPlayerInVehicle(playerid, vehicleID, 0);
		}
		else
		{
			playbackType = PLAYER_RECORDING_TYPE_ONFOOT;
		}
		if (strval(GetMySQLField("StartOnConnect")))
		{
			StartNPCPlayback(playerid, GetMySQLField("Recording"), playbackType, strval(GetMySQLField("AutoRepeat")));
		}
		else
		{
			FormatNew:command[40]("setrec %s %d %d", GetMySQLField("Recording"), playbackType, strval(GetMySQLField("AutoRepeat")));
			SendNPCCommand(playerid, command);
		}
		mysql_free_result();
	}
	else
	{
		printf("%s connected from %s", GetPlayerNameEx(playerid), GetPlayerCountryName(playerid));
		PlaySound(playerid, musicSoundIDs[random(sizeof(musicSoundIDs))]);
		MySQLQuery("SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_store_result();
		if (strval(GetMySQLField("ID")))
		{
			PVar:playerid[LANGUAGE] = strval(GetMySQLField("Language"));
			TogglePlayerSpectating(playerid, true);
			PVar:playerid[REGISTERED] = true;
		}
		else
		{
			new countryCode[2];
			strcat(countryCode, GetPlayerCountryCode(playerid));
			if (strlen(countryCode) && (!strcmp(countryCode, "AT", true) || !strcmp(countryCode, "CH", true) || !strcmp(countryCode, "DE", true)))
			{
				PVar:playerid[LANGUAGE] = LANGUAGE_GERMAN;
			}
			else
			{
				PVar:playerid[LANGUAGE] = LANGUAGE_ENGLISH;
			}
			PVar:playerid[REGISTERED] = false;
		}
		mysql_free_result();
		ShowDialog(playerid, DIALOG_PREVIEWINFO);
		SendDeathMessage(INVALID_PLAYER_ID, playerid, 200);
		SendClientMessageEx(playerid, COLOR_SYSTEM, 138);
		SendClientMessageEx(playerid, COLOR_SYSTEM, 5, COMPILER_SVN_REVISION);
		PlayerLoop(playerID)
		{
			if (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID) && playerID != playerid)
			{
				SendClientMessageEx(playerID, COLOR_JOINLEAVE, 3, playerid);
			}
		}
		FormatNew:string[MAX_PLAYER_NAME + 30]("%s has joined the server", GetPlayerNameEx(playerid));
		IRC_Say(ircBot, IRC_CHANNEL, string);
		ReloadTextDraws(playerid);
		TextDrawShowForPlayer(playerid, textDrawClock);
	}
	return true;
}