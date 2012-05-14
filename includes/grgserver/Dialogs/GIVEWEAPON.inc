ShowDialog:GIVEWEAPON(playerID)
{
	new weaponList[1024];
	Count(weaponID, sizeof(weapons))
	{
		if (weapons[weaponID][WEAPON_AMMO])
		{
			if (strlen(weaponList))
			{
				Format:weaponList("%s\n", weaponList);
			}
			Format:weaponList("%s%d: %s", weaponList, weaponID, weapons[weaponID][WEAPON_NAME]);
		}
	}
	CreateDialog(playerID, "GIVEWEAPON", DIALOG_STYLE_LIST, LanguageString(playerID, 361), weaponList, "OK", LanguageString(playerID, 165));
}

DialogResponse:GIVEWEAPON(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new weaponID;
		new name[STRINGLENGTH_WEAPONNAME];
		sscanf(inputText, "p:ds", weaponID, name);
		if (GivePlayerWeaponEx(playerID, weaponID))
		{
			SendClientMessageEx(playerID, COLOR_INFO, 69, weapons[weaponID][WEAPON_NAME]);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 68);
		}
	}
}