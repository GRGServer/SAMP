CMD:about(playerid, params[])
{
	SendClientMessage(playerid, COLOR_INFO, "Created by Aerox_Tobi (aerox@grgserver.de) and Programie (programie@selfcoders.com)");
	return COMMAND_OK;
}

CMD:makeadmin(playerid, params[])
{
	new playerName[MAX_PLAYER_NAME];
	new level;
	if (GetPVarInt(playerid, "AdminLevel") >= ADMINLEVEL_SERVERADMIN)
	{
		if (!sscanf(params, "sd", playerName, level))
		{
			SendClientMessage(playerid, COLOR_USAGE, "Verwendung: /makeadmin [Spielername] [level(1-1337)]");
		}
		new targetPlayerID = getPlayerByName(playerName);
		if (targetPlayerID == INVALID_PLAYERID)
		{
			SendClientMessage(playerid, COLOR_ERROR, "Spieler nicht gefunden!");
		}
		else
		{
			if (level >= 1 && level <= 1337)
			{
				new string[256];
				new adminPlayerName[MAX_PLAYER_NAME];
				new targetPlayerName[MAX_PLAYER_NAME];
				GetPlayerName(playerid, adminPlayerName, sizeof(adminPlayerName));
				GetPlayerName(targetPlayerID, targetPlayerName, sizeof(targetPlayerName));
				SetPVarInt(targetPlayerID, "AdminLevel", level);
				format(string, sizeof(string), "Du hast Admin Level %d von %s bekommen!", level, adminPlayerName);
				SendClientMessage(targetPlayerID, COLOR_INFO, string);
				format(string, sizeof(string), "Du hast Admin Level %d an %s gegeben!", level, targetPlayerName);
				SendClientMessage(playerid, COLOR_INFO, string);
				printf("%s got admin level %d by %s", targetPlayerName, level, adminPlayerName);
			}
			else
			{
				SendClientMessage(playerid, COLOR_ERROR, "Level muss zwischen 1 und 1337 sein!");
			}
		}
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
	return COMMAND_OK;
}