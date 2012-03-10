PCMD:giveweapon[ADMIN](playerid, params[], "Sich selber Waffen geben")
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
		SendClientMessage(playerid, COLOR_ERROR, "Ungültige WeaponID!");
		return COMMAND_ERROR;
	}
	GivePlayerWeapon(playerid, weaponID, ammo);
	FormatNew:string[70]("Viel Spaß mit deiner neuen Waffe '%s'!", GetWeaponNameEx(weaponID));
	SendClientMessage(playerid, COLOR_INFO, string);
	return COMMAND_OK;
}