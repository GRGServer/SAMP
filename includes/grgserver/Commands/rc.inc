PCMD:rc[SERVERADMIN](playerID, params[], StringID:51("Execute RCON command"))
{
	if (!StrNotNull(params))
	{
		CmdUsageMsg(playerID, "rc", "Command(exit,gmx,...)", "Parameter", "...");
		return COMMAND_USAGE;
	}
	printf("%s sent a RCON command: %s", GetPlayerNameEx(playerID), params);
	PlayerLoop(targetPlayerID)
	{
		if (playerID != targetPlayerID && permissions[targetPlayerID][PERMISSION_SERVERADMIN])
		{
			SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:462("%p executed '%s' via RCON"), playerID, params);
		}
	}
	SendClientMessageEx(playerID, COLOR_INFO, StringID:50("'%s' has been executed via RCON"), params);
	SendRconCommand(params);
	return COMMAND_OK;
}