CMD:givelicense(playerID, params[], 511)
{
	new targetPlayerID;
	new licenseString[256];
	if (sscanf(params, "us", targetPlayerID, licenseString))
	{
		CmdUsageMsg(playerID, "givelicense", "PlayerID/Name", "Car|Bike|Truck|Sailing|Fly");
		return COMMAND_USAGE;
	}
	new licenseArray[30][30];
	new license[30];
	explode(licenseString, licenseArray, ',', sizeof(licenseArray));
	for (new licenseIndex = 0; licenseIndex < sizeof(licenseArray); licenseIndex++)
	{
		license = licenseArray[licenseIndex];
		if(PVar:playerID[JOBID] == JOB_SCHOOLDRIVER)
		{
			if(PVar:playerID[LICENSECAR] == license[3])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 512);
			}
			else
			{
				MySQLQuery("UPDATE `users` SET `CarLicense` = '1' WHERE `id` = '%d'",PVar:targetPlayerID[USERID]);
				SendClientMessageEx(playerID, COLOR_INFO, 513);
			}
			if(PVar:playerID[LICENSEBIKE] == license[4])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 512);
			}
			else
			{
				MySQLQuery("UPDATE `users` SET `BikeLicense` = '1' WHERE `id` = '%d'", PVar:targetPlayerID[USERID]);
				SendClientMessageEx(playerID, COLOR_INFO, 530);
			}
			if(PVar:playerID[LICENSETRUCK] == license[5])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 512);
			}
			else
			{
				MySQLQuery("UPDATE `users` SET `TruckLicense` = '1' WHERE `id` = '%d'", PVar:targetPlayerID[USERID]);
				SendClientMessageEx(playerID, COLOR_INFO, 531);
			}
			if(PVar:playerID[LICENSESAILING] == license[7])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 512);
			}
			else
			{
				MySQLQuery("UPDATE `users` SET `SailingLicense` = '1' WHERE `id` = '%d'", PVar:targetPlayerID[USERID]);
				SendClientMessageEx(playerID, COLOR_INFO, 532);
			}
			if(PVar:playerID[LICENSEFLY] == license[3])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 512);
			}
			else
			{
				MySQLQuery("UPDATE `users` SET `FlyLicense` = '1' WHERE `id` = '%d'", PVar:targetPlayerID[USERID]);
				SendClientMessageEx(playerID, COLOR_INFO, 533);
			}
		}
	}
	return COMMAND_OK;
}