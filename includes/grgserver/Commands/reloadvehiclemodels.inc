PCMD:reloadvehiclemodels[SERVERADMIN](playerID, params[], StringID:154("Reload all vehicle models from database"))
{
	ReloadVehicleModels(playerID);
	return COMMAND_OK;
}