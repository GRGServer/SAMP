PCMD:reloadvehicles[SERVERADMIN](playerID, params[], StringID:153(""))
{
	ReloadVehicles(false, playerID);
	return COMMAND_OK;
}