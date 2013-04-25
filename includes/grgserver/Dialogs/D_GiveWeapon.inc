ShowDialog:GiveWeapon(playerID)
{
	new weaponList[1024];
	Count(weaponID, sizeof(weapons))
	{
		if (weapons[weaponID][WEAPON_AMMO] && IsAllowedWeapon(weaponID))
		{
			if (strlen(weaponList))
			{
				Format:weaponList("%s\n", weaponList);
			}
			Format:weaponList("%s%d: %s", weaponList, weaponID, weapons[weaponID][WEAPON_NAME]);
		}
	}
	CreateDialog(playerID, "GiveWeapon", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:361("Select a weapon")), weaponList, "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:GiveWeapon(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new weaponID;
		new name[STRINGLENGTH_WEAPONNAME];
		sscanf(inputText, "p<:>ds[" #STRINGLENGTH_WEAPONNAME "]", weaponID, name);
		if (GivePlayerWeaponEx(playerID, weaponID))
		{
			SendClientMessageEx(playerID, COLOR_INFO, StringID:69("Have fun with your new weapon (%s)!"), weapons[weaponID][WEAPON_NAME]);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:68("Invalid WeaponID!"));
		}
	}
}