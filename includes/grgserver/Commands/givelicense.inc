CMD:givelicense(playerID, params[], StringID:511("Give license to a player"))
{
	new targetPlayerID;
	new licenseString[256];
	if (sscanf(params, "us[256]", targetPlayerID, licenseString))
	{
		CmdUsageMsg(playerID, "givelicense", "PlayerID/Name", "Bike|Boat|Car|Plane|Truck");
		return COMMAND_USAGE;
	}
	new licenseArray[30][30];
	new license[30];
	explode(licenseString, licenseArray, ',', sizeof(licenseArray));
	for (new licenseIndex = 0; licenseIndex < sizeof(licenseArray); licenseIndex++)
	{
		license = licenseArray[licenseIndex];
		new newState = true;
		if (license[0] == '-')
		{
			strdel(license, 0, 1);
			newState = false;
		}
		if (strlen(license))
		{
			if (GiveLicense(playerID, targetPlayerID, license, newState))
			{
				if (newState)
				{
					SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:513("You got a %l!"), GetLicenseLanguageStringID(license));
					SendClientMessageEx(playerID, COLOR_INFO, StringID:535("You gave a %l to %p"), GetLicenseLanguageStringID(license), targetPlayerID);
				}
				else
				{
					SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:537("Your %l has been revoked!"), GetLicenseLanguageStringID(license));
					SendClientMessageEx(playerID, COLOR_INFO, StringID:536("You revoked the %l from %p!"), GetLicenseLanguageStringID(license), targetPlayerID);
				}
			}
			else
			{
				if (newState)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:512("%p already owns that license (%l)!"), targetPlayerID, GetLicenseLanguageStringID(license));
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:538("%p does not own a %l!"), targetPlayerID, GetLicenseLanguageStringID(license));
				}
			}
		}
	}
	return COMMAND_OK;
}