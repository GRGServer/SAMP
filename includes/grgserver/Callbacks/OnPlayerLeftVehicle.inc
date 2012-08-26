OnPlayerLeftVehicle(playerID, vehicleID, isPassenger)
{
	#pragma unused isPassenger
	StopRadioStation(playerID);
	if (GetVehicleModel(vehicleID) == 449)
	{
		SetCameraBehindPlayer(playerID);// Fixes not setting camera behind player after leaving a tram
	}
	if (PVar:playerID[CPMISSION_VEHICLEID] == vehicleID)
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		GetVehiclePos(vehicleID, posX, posY, posZ);
		DisablePlayerRaceCheckpoint(playerID);
		SetPlayerCheckpointEx(playerID, CHECKPOINT_VEHICLEMARKER, posX, posY, posZ, 5);
		ShowMessage(playerID, 29, 3000);
	}
}