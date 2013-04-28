OnPlayerLeftVehicle(playerID, vehicleID, isPassenger)
{
	#pragma unused isPassenger
	StopRadioStation(playerID);
	if (GetVehicleModel(vehicleID) == 449)
	{
		SetCameraBehindPlayer(playerID);// Fixes not setting camera behind player after leaving a tram
	}
	if (PVar:playerID[CPMISSION_VEHICLEID] && PVar:playerID[CPMISSION_VEHICLEID] == vehicleID)
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		GetVehiclePos(vehicleID, posX, posY, posZ);
		DisablePlayerRaceCheckpoint(playerID);
		SetVehicleParamsForPlayer(vehicleID, playerID, true, false);
		ShowSubtitle(playerID, LanguageString(playerID, StringID:607("Go back to your vehicle!")));
	}
}