public OnPlayerConnect(playerid)
{
	ResetPlayerVariables(playerid);
	if (IsPlayerNPC(playerid))
	{
		new npcName[MAX_PLAYER_NAME];
		GetPlayerName(playerid, npcName, sizeof(npcName));
		strdel(npcName, 0, 4);
		MySQLQuery("SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(npcName));
		mysql_store_result();
		SetPlayerSkin(playerid, strval(GetMySQLField("Skin")));
		if (strval(GetMySQLField("StartOnConnect")))
		{
			new color1;
			new color2;
			new modelID;
			new playbackType;
			new vehicleID;
			modelID = strval(GetMySQLField("VehicleModelID"));
			if (modelID)
			{
				playbackType = PLAYER_RECORDING_TYPE_DRIVER;
				color1 = random(127);
				color2 = random(127);
				vehicleID = CreateVehicleEx(modelID, 0.0, 0.0, 0.0, 0.0, color1, color2, 0);
				PutPlayerInVehicle(playerid, vehicleID, 0);
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
		printf("%s connected from %s", GetPlayerNameEx(playerid), GetPlayerCountryName(playerid));
		MySQLQuery("SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_store_result();
		if (strval(GetMySQLField("ID")))
		{
			PVar:playerid[LANGUAGE] = strval(GetMySQLField("Language"));
			TogglePlayerSpectating(playerid, true);
			ShowDialog(playerid, DIALOG_LOGIN);
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
			ShowDialog(playerid, DIALOG_REGISTER_PASSWORD1);
		}
		mysql_free_result();
		SendDeathMessage(INVALID_PLAYER_ID, playerid, 200);
		SendClientMessageEx(playerid, COLOR_SYSTEM, 138);
		SendClientMessageEx(playerid, COLOR_SYSTEM, 5, COMPILER_SVN_REVISION);
		PlayerLoop(playerID)
		{
			if (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID) && playerID != playerid)
			{
				SendClientMessageEx(playerid, COLOR_JOINLEAVE, 3, playerid);
			}
		}
		FormatNew:string[MAX_PLAYER_NAME + 30]("%s has joined the server", GetPlayerNameEx(playerid));
		IRC_Say(ircBot, IRC_CHANNEL, string);
		ReloadTextDraws(playerid);
		TextDrawShowForPlayer(playerid, textDrawClock);
	}
	return true;
}