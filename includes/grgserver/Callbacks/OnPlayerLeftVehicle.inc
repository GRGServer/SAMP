OnPlayerLeftVehicle(playerID, vehicleID, isPassenger)
{
	StopRadioStation(playerID);
	SetCameraBehindPlayer(playerID);// Fixed not setting camera behind player after leaving a tram
}