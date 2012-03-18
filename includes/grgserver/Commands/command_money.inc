PCMD:money[ADMIN](playerid, params[], 110)
{
	new Float:money;
	if (!sscanf(params, "f", money))
	{
		GivePlayerMoneyEx(playerid, money);
		SendClientMessageEx(playerid, COLOR_INFO, 81, money, PVar:playerid[MONEY]);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "money", "Wert");
		return COMMAND_USAGE;
	}
}