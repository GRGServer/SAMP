PCMD:rc[SERVERADMIN](playerID, params[], 51)
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
			SendClientMessageEx(targetPlayerID, COLOR_INFO, "462", playerID, params);
		}
	}
	SendClientMessageEx(playerID, COLOR_INFO, "50", params);
	SendRconCommand(params);
	return COMMAND_OK;
}