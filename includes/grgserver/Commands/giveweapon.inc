PCMD:giveweapon[ADMIN](playerID, params[], 104)
{
	new weaponID;
	if (sscanf(params, "d", weaponID))
	{
		ShowDialog:GIVEWEAPON(playerID);
		return COMMAND_OK;
	}
	if (GivePlayerWeaponEx(playerID, weaponID))
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