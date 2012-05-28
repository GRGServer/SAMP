PCMD:giveweapon[ADMIN](playerID, params[], 104)
{
	new weaponID;
	new ammo;
	if (sscanf(params, "dd", weaponID, ammo))
	{
		if (sscanf(params, "d", weaponID))
		{
			ShowDialog:GiveWeapon(playerID);
			return COMMAND_OK;
		}
	}
	if (GivePlayerWeaponEx(playerID, weaponID, ammo))
	{
		SendClientMessageEx(playerID, COLOR_INFO, 69, weapons[weaponID][WEAPON_NAME]);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 68);
		return COMMAND_ERROR;
	}
}