CMD:getbalance(playerid, params[], "Kontostand anzeigen")
{
	new string[256];
	Format:string("Aktueller Kontostand: $%s", FormatMoney(GetPVar:playerid[MONEY]));
	SendClientMessage(playerid, COLOR_INFO, string);
	return COMMAND_OK;
}