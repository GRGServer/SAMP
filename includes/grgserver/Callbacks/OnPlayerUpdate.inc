public OnPlayerUpdate(playerid)
{
	if (PVar:playerid[GODMODE])
	{
		SetPlayerHealth(playerid, 100);
		new vehicleID = GetPlayerVehicleID(playerid);
		if (vehicleID)
		{
			SetVehicleHealth(vehicleID, 1000);
		}
	}
	if (!IsAllowedWeapon(GetPlayerWeapon(playerid)))
	{
		BanEx(playerid, "Use not allowed weapon");
	}
	return true;
}