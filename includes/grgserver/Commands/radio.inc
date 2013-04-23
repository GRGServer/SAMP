CMD:radio(playerID, params[], StringID:115(""))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (vehicleID)
	{
		if (VehicleProperty:vehicleID[RADIOSTATIONID])
		{
			StopAudioStreamForPlayer(playerID);
			VehicleProperty:vehicleID[RADIOSTATIONID] = 0;
		}
		else
		{
			VehicleProperty:vehicleID[RADIOSTATIONID] = 1;
			PlayRadioStation(playerID, VehicleProperty:vehicleID[RADIOSTATIONID]);
		}
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
}