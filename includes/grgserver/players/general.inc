public OnPlayerRequestClass(playerid, classid)
{
	new previousClassID = GetPVarInt(playerid, "PreviousClassID");
	new direction;
	switch (classid)
	{
		case 0:
		{
			switch (previousClassID)
			{
				case 1:
					direction--;
				case 2:
					direction++;
			}
		}
		case 1:
		{
			switch (previousClassID)
			{
				case 2:
					direction--;
				case 0:
					direction++;
			}
		}
		case 2:
		{
			switch (previousClassID)
			{
				case 0:
					direction--;
				case 1:
					direction++;
			}
		}
	}
	SetPVarInt(playerid, "PreviousClassID", classid);
	new skinID = GetPVarInt(playerid, "Skin");
	switch (direction)
	{
		case -1:
		{
			do
			{
				skinID--;
				if (skinID < 0)
				{
					skinID = 298;
				}
			}
			while (!IsValidSkin(skinID));
		}
		case 1:
		{
			do
			{
				skinID++;
				if (skinID > 298)
				{
					skinID = 0;
				}
			}
			while (!IsValidSkin(skinID));
		}
	}
	SetPVarInt(playerid, "Skin", skinID);
	SetPlayerSkin(playerid, skinID);
	new string[256];
	format(string, sizeof(string), "Player/ClassID/Direction/SkinID: %s/%d/%d/%d", GetPlayerNameEx(playerid), classid, direction, skinID);
	SendClientMessage(playerid, COLOR_SYSTEM, string);
	SetPlayerPos(playerid, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ);
	SetPlayerFacingAngle(playerid, SPAWN_ANGLE);
	SetPlayerCameraPos(playerid, SPAWN_CAMERAPOSX, SPAWN_CAMERAPOSY, SPAWN_CAMERAPOSZ);
	SetPlayerCameraLookAt(playerid, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ);
	return true;
}

public OnPlayerSpawn(playerid)
{
	if (GetPVarInt(playerid, "SpawnAfterLogin"))
	{
		DeletePVar(playerid, "SpawnAfterLogin");
		SetPlayerPos(playerid, floatstr(GetUserDBValue(playerid, "PosX")), floatstr(GetUserDBValue(playerid, "PosY")), floatstr(GetUserDBValue(playerid, "PosZ")));
		SetPlayerFacingAngle(playerid, floatstr(GetUserDBValue(playerid, "Angle")));
		SetPlayerInterior(playerid, strval(GetUserDBValue(playerid, "Interior")));
		SetPlayerSkin(playerid, GetPVarInt(playerid, "Skin"));
	}
	return true;
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

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
		StopRadioStation(playerid);
	}
}

public OnPlayerUpdate(playerid)
{
	if (savePlayers[playerid])
	{
		SavePlayer(playerid);
		savePlayers[playerid] = false;
	}
	return true;
}