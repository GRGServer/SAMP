SpawnVehicle(playerID, modelID, color1, color2, showMessage)
{
	if (!modelID)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 64);
		}
		return false;
	}
	if (modelID < 400 || modelID > 611)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 65);
		}
		return false;
	}
	if (color1 < 0 || color1 > 127 || color2 < 0 || color2 > 127)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 63);
		}
		return false;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	GetPlayerPos(playerID, posX, posY, posZ);
	GetPlayerFacingAngle(playerID, angle);
	new vehicleID = CreateVehicleEx(modelID, posX, posY, posZ, angle, color1, color2, -1, false);
	if (!vehicleID)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 461);
		}
		return false;
	}
	VehicleProperty:vehicleID[HASNAVI] = true;
	LinkVehicleToInterior(vehicleID, GetPlayerInterior(playerID));
	SetVehicleVirtualWorld(vehicleID, GetPlayerVirtualWorld(playerID));
	PutPlayerInVehicle(playerID, vehicleID, 0);
	if (showMessage)
	{
		SendClientMessageEx(playerID, COLOR_INFO, 62);
	}
	return true;
}