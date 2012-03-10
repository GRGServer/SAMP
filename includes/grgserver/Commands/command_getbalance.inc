CMD:getbalance(playerid, params[], "Kontostand anzeigen")
{
	new string[256];
	Format:string("Aktueller Kontostand: $%s", FormatMoney(PVar:playerid[MONEY]));
	SendClientMessage(playerid, COLOR_INFO, string);
	return COMMAND_OK;
}