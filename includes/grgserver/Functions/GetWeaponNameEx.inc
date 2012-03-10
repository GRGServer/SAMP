GetWeaponNameEx(weaponID)
{
	new string[32];
	GetWeaponName(weaponID, string, sizeof(string));
	return string;
}