PCMD:reloadvehicles[SERVERADMIN](playerID, params[], StringID:153("Reload all saved vehicles from database"))
{
	ReloadVehicles(false, playerID);
	return COMMAND_OK;
}