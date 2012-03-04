CMD:motor(playerid, params[], "Starten oder stoppen des Motors deines Fahrzeugs")
{
	if (!IsPlayerInAnyVehicle(playerid))
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, COLOR_ERROR, "Du bist nicht der Fahrer dieses Fahrzeugs!");
		return COMMAND_ERROR;
	}
	new vehicleID = GetPlayerVehicleID(playerid);
	if (!CheckVehiclePermission(playerid, vehicleID))
	{
		return COMMAND_ERROR;
	}
	if (GetVehicleEngineState(vehicleID))
	{
		SetVehicleEngineState(vehicleID, false);
		SendClientMessage(playerid, COLOR_INFO, "Der Motor deines Fahrzeuges wurde ausgeschalten.");
		return COMMAND_OK;
	}
	new Float:health;
	GetVehicleHealth(vehicleID, health);
	if (health >= VEHICLE_MINHEALTH)
	{
		SetVehicleEngineState(vehicleID, true);
		SendClientMessage(playerid, COLOR_INFO, "Der Motor deines Fahrzeuges wurde gestartet.");
		return COMMAND_OK;
	}
	SendClientMessage(playerid, COLOR_ERROR, "Der Motor deines Fahrzeuges konnte nicht gestartet werden (Motorschaden)!");
	return COMMAND_ERROR;
}