CMD:radio(playerID, params[], 115)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (vehicleID)
	{
		if (VehicleProperty:vehicleID[RADIOSTATION])
		{
			StopAudioStreamForPlayer(playerID);
			VehicleProperty:vehicleID[RADIOSTATION] = 0;
		}
		else
		{
			VehicleProperty:vehicleID[RADIOSTATION] = 1;
			PlayRadioStation(playerID, VehicleProperty:vehicleID[RADIOSTATION]);
		}
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
}