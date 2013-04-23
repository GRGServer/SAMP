CMD:sierene(playerID, params[], )
{
	new PoliceLight = CreatePlayerObject(playerid, 18646, 0, 0, 0, 0, 0, 0);	
	if(VehicleProperty:vehicleID[SIERENLIGHTSID] == 1)
	{
		DestroyObject(playerid, PoliceLight);
		VehicleProperty:vehicleID[SIERENLIGHTSID] = 0;
	}
	else
	{
		AttachPlayerObjectToVehicle(playerid, PoliceLight, GetPlayerVehicleID(playerid), 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
		VehicleProperty:vehicleid[SIERENLIGHTSID] = 1;
	}
}