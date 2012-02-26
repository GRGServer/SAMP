PCMD:kick[MODERATOR](playerid, params[], "Spieler vom Server kicken")
{
	new targetPlayerID;
	new reason[256];
	new string[256];
	if (sscanf(params, "us", targetPlayerID, reason))
	{
		CmdUsageMsg(playerid, "kick", "Spielername/ID", "Grund");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		Kick(targetPlayerID);
		Format:string("%s wurde von %s gekickt, Grund: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerid), reason);
		SendClientMessageToAll(COLOR_ERROR, string);
		printf("%s has been kicked by %s, Reason: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerid), reason);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}