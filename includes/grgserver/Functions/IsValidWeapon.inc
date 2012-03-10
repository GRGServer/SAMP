IsValidWeapon(weaponID)
{
	if (weaponID < 0 || weaponID > 46)
	{
		return false;
	}
	if (weaponID == 44 || weaponID == 45)// Do not allow Night Vis Goggles and Thermal Goggles (Bugs in Multiplayer)
	{
		return false;
	}
	return true;
}