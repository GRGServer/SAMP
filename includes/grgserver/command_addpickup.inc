PCMD:addpickup[MAPPER](playerid, params[], "Pickup erstellen")
{
	new type[256];
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	if (sscanf(params, "s", type))
	{
		CmdUsageMsg(playerid, "addpickup", "GASSTATION/TRUCKER/VEHICLEDEALER/POLICE/INBANK");
		return COMMAND_USAGE;
	}
	Format:type("%s", strtoupper(type));
	if (!strcmp(type, "GASSTATION", true) || !strcmp(type, "INBANK", true) || !strcmp(type, "POLICE", true) || !strcmp(type, "TRUCKER", true) || !strcmp(type, "VEHICLEDEALER", true))
	{
		GetPlayerPos(playerid, posX, posY, posZ);
		new id = AddPickup(-1, type, posX, posY, posZ, true);
		if (id > 0)
		{
			FormatNew:string[80]("Das Pickup %s wurde unter der ID %d gespeichert", type, id);
			SendClientMessage(playerid, COLOR_INFO, string);
			return COMMAND_OK;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Ungültiger Typ!");
	}
	return COMMAND_ERROR;
}