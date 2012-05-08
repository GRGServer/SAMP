OnPlayerLeftVehicle(playerID, vehicleID, isPassenger)
{
	#pragma unused vehicleID
	#pragma unused isPassenger
	StopRadioStation(playerID);
	SetCameraBehindPlayer(playerID);// Fixed not setting camera behind player after leaving a tram
}