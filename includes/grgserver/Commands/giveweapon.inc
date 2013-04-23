PCMD:giveweapon[ADMIN](playerID, params[], StringID:104(""))
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
		SendClientMessageEx(playerID, COLOR_INFO, StringID:69(""), weapons[weaponID][WEAPON_NAME]);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:68(""));
		return COMMAND_ERROR;
	}
}