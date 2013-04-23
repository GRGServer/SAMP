PCMD:money[ADMIN](playerid, params[], StringID:110(""))
{
	new Float:money;
	if (!sscanf(params, "f", money))
	{
		GivePlayerMoneyEx(playerid, MONEY_CASH, money);
		SendClientMessageEx(playerid, COLOR_INFO, StringID:81(""), money, PVar:playerid[MONEY]);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "money", "$$$");
		return COMMAND_USAGE;
	}
}