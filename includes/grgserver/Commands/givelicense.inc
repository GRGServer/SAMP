CMD:givelicense(playerID, params[], StringID:511(""))
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
					SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:513(""), GetLicenseLanguageStringID(license));
					SendClientMessageEx(playerID, COLOR_INFO, StringID:535(""), GetLicenseLanguageStringID(license), targetPlayerID);
				}
				else
				{
					SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:537(""), GetLicenseLanguageStringID(license));
					SendClientMessageEx(playerID, COLOR_INFO, StringID:536(""), GetLicenseLanguageStringID(license), targetPlayerID);
				}
			}
			else
			{
				if (newState)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:512(""), targetPlayerID, GetLicenseLanguageStringID(license));
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:538(""), targetPlayerID, GetLicenseLanguageStringID(license));
				}
			}
		}
	}
	return COMMAND_OK;
}