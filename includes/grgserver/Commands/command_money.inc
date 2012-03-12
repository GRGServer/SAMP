PCMD:money[ADMIN](playerid, params[], "Gebe dir Geld")
{
	new Float:money;
	if (!sscanf(params, "f", money))
	{
		GivePlayerMoneyEx(playerid, money);
		FormatNew:string[80]("Du hast dir $%s gegeben und hast daher nun $%s", FormatMoney(money), FormatMoney(PVar:playerid[MONEY]));
		SendClientMessage(playerid, COLOR_INFO, string);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "money", "Wert");
		return COMMAND_USAGE;
	}
}