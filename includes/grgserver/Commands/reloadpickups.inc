PCMD:reloadpickups[SERVERADMIN](playerID, params[], StringID:152("Reload all pickups from database"))
{
	ReloadPickups(playerID);
	return COMMAND_OK;
}