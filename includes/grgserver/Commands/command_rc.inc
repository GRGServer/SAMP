PCMD:rc[SERVERADMIN](playerid, params[], 51)
{
	if (strlen(params))
	{
		printf("%s sent a RCON command: %s", GetPlayerNameEx(playerid), params);
		SendRconCommand(params);
		SendClientMessageEx(playerid, COLOR_INFO, 50);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "rc", "Befehl(exit,gmx,...)", "Parameter", "...");
		return COMMAND_USAGE;
	}
}