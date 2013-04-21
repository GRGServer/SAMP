CMD:givelicense(playerID, params[], 511)
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
					SendClientMessageEx(targetPlayerID, COLOR_INFO, "513", LicenseLanguageStringName(license));
					SendClientMessageEx(playerID, COLOR_INFO, "535", LicenseLanguageStringName(license), targetPlayerID);
				}
				else
				{
					SendClientMessageEx(targetPlayerID, COLOR_INFO, "537", LicenseLanguageStringName(license));
					SendClientMessageEx(playerID, COLOR_INFO, "536", LicenseLanguageStringName(license), targetPlayerID);
				}
			}
			else
			{
				if (newState)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, "512", targetPlayerID, LicenseLanguageStringName(license));
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, "538", targetPlayerID, LicenseLanguageStringName(license));
				}
			}
		}
	}
	return COMMAND_OK;
}