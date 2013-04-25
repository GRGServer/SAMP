PCMD:money[ADMIN](playerid, params[], StringID:110("Give money to yourself"))
{
	new Float:money;
	if (!sscanf(params, "f", money))
	{
		GivePlayerMoneyEx(playerid, MONEY_CASH, money);
		SendClientMessageEx(playerid, COLOR_INFO, StringID:81("You gave you %m and have now %m"), money, PVar:playerid[MONEY]);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "money", "$$$");
		return COMMAND_USAGE;
	}
}