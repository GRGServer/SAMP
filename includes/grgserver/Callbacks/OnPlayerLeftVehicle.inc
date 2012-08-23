OnPlayerLeftVehicle(playerID, vehicleID, isPassenger)
{
	#pragma unused vehicleID
	#pragma unused isPassenger
	StopRadioStation(playerID);
	if (GetVehicleModel(vehicleID) == 449)
	{
		SetCameraBehindPlayer(playerID);// Fixes not setting camera behind player after leaving a tram
	}
	if (PVar:playerID[DRIVINGSCHOOL_INMISSION])
	{
		ShowMessage(playerID, 29, 3000);
	}
}