public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (IsPlayerNPC(playerid))
	{
		return true;
	}
	if (!ispassenger)
	{
		SetVehicleEngineState(vehicleid, false);
		if (!CheckVehiclePermission(playerid, vehicleid))
		{
			return false;
		}
	}
	return true;
}