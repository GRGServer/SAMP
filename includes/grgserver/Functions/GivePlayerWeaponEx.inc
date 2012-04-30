GivePlayerWeaponEx(playerID, weaponID)
{
	if (IsValidWeapon(weaponID))
	{
		GivePlayerWeapon(playerID, weaponID, weapons[weaponID][WEAPON_AMMO]);
		return true;
	}
	return false;
}