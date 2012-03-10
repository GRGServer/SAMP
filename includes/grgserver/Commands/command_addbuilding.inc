PCMD:addbuilding[MAPPER](playerid, params[], "Gebäude erstellen")
{
	new Float:price;
	if (sscanf(params, "f", price))
	{
		CmdUsageMsg(playerid, "addbuilding", "Preis");
		return COMMAND_USAGE;
	}
	PVar:playerid[ADDBUILDING_PRICE] = price;
	ShowDialog(playerid, DIALOG_ADDBUILDING_TYPE);
	return COMMAND_OK;
}