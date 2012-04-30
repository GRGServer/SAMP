IsValidWeapon(weaponID)
{
	if (weaponID >= 0 && weaponID < sizeof(weapons) && weapons[weaponID][WEAPON_AMMO])
	{
		return true;
	}
	return false;
}