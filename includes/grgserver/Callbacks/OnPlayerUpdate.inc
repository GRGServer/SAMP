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
	new Float:money = floatdiv(GetPlayerMoney(playerid), 100);
	if (money < PVar:playerid[MONEY])
	{
		PVar:playerid[MONEY] = money;
	}
	if (!IsAllowedWeapon(GetPlayerWeapon(playerid)))
	{
		MySQLBan(INVALID_PLAYER_ID, playerid, "Use not allowed weapon", true);
	}
	return true;
}