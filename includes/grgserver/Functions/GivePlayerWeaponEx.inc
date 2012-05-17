GivePlayerWeaponEx(playerID, weaponID, ammo = 0)
{
	if (IsValidWeapon(weaponID) && IsAllowedWeapon(weaponID))
	{
		switch (ammo)
		{
			case -1:
			{
				ammo = 999999;
			}
			case 0:
			{
				ammo = weapons[weaponID][WEAPON_AMMO];
			}
		}
		GivePlayerWeapon(playerID, weaponID, ammo);
		return true;
	}
	return false;
}