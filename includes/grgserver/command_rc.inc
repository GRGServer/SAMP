PCMD:rc[SERVERADMIN](playerid, params[], "RCON Befehl ausführen")
{
	if (strlen(params))
	{
		printf("%s sent a RCON command: %s", GetPlayerNameEx(playerid), params);
		SendRconCommand(params);
		SendClientMessage(playerid, COLOR_INFO, "Der Befehl wurde ausgeführt");
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "rc", "Befehl(exit,gmx,...)", "Parameter", "...");
		return COMMAND_USAGE;
	}
}