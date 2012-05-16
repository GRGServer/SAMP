public OnPlayerExitVehicle(playerid, vehicleid)
{
	SaveVehicle(vehicleid, GetPlayerInterior(playerid));
	StopRadioStation(playerid);
	PVar:playerid[OLDVEHICLEID] = vehicleid;
	return true;
}