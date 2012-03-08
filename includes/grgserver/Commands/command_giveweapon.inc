PCMD:giveweapon[ADMIN](playerid, params[], "Sich selber Waffen Geben")
{
	new weaponid;
	new ammo;
	if (sscanf(params, "dd", weaponid, ammo))
	{
		if (weaponid >= 0 && weaponid <= 46)
		{
			GivePlayerWeapon(playerid, weaponid,ammo);
		}
	}
	else
	{
		CmdUsageMsg(playerid, "giveweapon", "WeaponID");
	}
	return COMMAND_OK;
}