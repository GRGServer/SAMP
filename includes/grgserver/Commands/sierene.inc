CMD:sierene(playerID, params[], )
{
	new PoliceLight = CreatePlayerObject(playerid, 18646, 0, 0, 0, 0, 0, 0);	
	if(VehicleProperty:vehicleID[SIERENLIGHTID] == 1)
	{
		DestroyObject(playerid, PoliceLight);
		VehicleProperty:vehicleID[SIERENLIGHTID] = 0;
	}
	else
	{
		AttachPlayerObjectToVehicle(playerid, PoliceLight, GetPlayerVehicleID(playerid), 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
		VehicleProperty:vehicleid[SIERENLIGHTID] = 1;
	}
}