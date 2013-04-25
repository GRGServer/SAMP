PCMD:giveweapon[ADMIN](playerID, params[], StringID:104("Give weapons to yourself"))
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
		SendClientMessageEx(playerID, COLOR_INFO, StringID:69("Have fun with your new weapon (%s)!"), weapons[weaponID][WEAPON_NAME]);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:68("Invalid WeaponID!"));
		return COMMAND_ERROR;
	}
}