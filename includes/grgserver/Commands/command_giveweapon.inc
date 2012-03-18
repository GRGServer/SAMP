PCMD:giveweapon[ADMIN](playerid, params[], 104)
{
	new weaponID;
	new ammo;
	if (sscanf(params, "dd", weaponID, ammo))
	{
		CmdUsageMsg(playerid, "giveweapon", "WeaponID", "Munition");
		return COMMAND_USAGE;
	}
	if (!IsValidWeapon(weaponID))
	{
		SendClientMessageEx(playerid, COLOR_ERROR, 68);
		return COMMAND_ERROR;
	}
	GivePlayerWeapon(playerid, weaponID, ammo);
	SendClientMessageEx(playerid, COLOR_INFO, 69, GetWeaponNameEx(weaponID));
	return COMMAND_OK;
}