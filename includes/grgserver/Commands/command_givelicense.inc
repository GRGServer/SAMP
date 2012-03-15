CMD:givelicense(playerid, params[], "Um einen Spieler einen Führerschein zu geben")
{
	if (PVar:playerid[JOBID] == JOB_DRIVINGSCOOL)
	{
		new targetPlayerID;
		new licenseString[256];
		if (sscanf(params, "us", targetPlayerID, licenseString))
		{
			CmdUsageMsg(playerid, "givelicense", "Spielername", "Scheine(Car|Bike|Sailing|Fishing|Truck|Flying|Weapon)");
			return COMMAND_USAGE;
		}
		if (IsPlayerConnected(targetPlayerID))
		{
			new licenseArray[30][30];
			new license[50];
			explode(licenseString, licenseArray, ',', sizeof(licenseArray));
			for (new licenseIndex = 0; licenseIndex < sizeof(licenseArray); licenseIndex++)
			{
				Format:license(licenseArray[licenseIndex]);
				if (strcmp(license, "UserID", true))
				{
					new newState = true;
					if (license[0] == '-')
					{
						strdel(license, 0, 1);
						newState = false;
					}
					new string[256];
					// new licenseID = GetLicenseByName(license);
					// TODO: Muss überprüft werden error kommt ich checks nicht 
					/* if (license[targetPlayerID][enum_license:licenseID] == newState)
					{
						if (newState)
						{
							Format:string("%s hat bereits den %s Schein", GetPlayerNameEx(targetPlayerID), license);
						}
						else
						{
							Format:string("%s hatte den %s Schein noch nicht und kann daher nicht entfernt werden", GetPlayerNameEx(targetPlayerID), license);
						}
						SendClientMessage(playerid, COLOR_ERROR, string);
						return COMMAND_ERROR;
					}*/
					MySQLQuery("SELECT `UserID` FROM `license` WHERE `UserID` = '%d'", PVar:targetPlayerID[USERID]);
					mysql_store_result();
					new rows = mysql_num_rows();
					mysql_free_result();
					if (rows)
					{
						MySQLQuery("UPDATE `license` SET `%s` = '%d' WHERE `UserID` = '%d'", MySQLEscapeString(license), newState, PVar:targetPlayerID[USERID]);
					}
					else
					{
						MySQLQuery("INSERT INTO `license` (`UserID`, `%s`) VALUES('%d', '%d')", MySQLEscapeString(license), PVar:targetPlayerID[USERID], newState);
					}
					// TODO: Muss überprüft werden.
					// license[targetPlayerID][enum_license:licenseID] = newState;
					if (newState)
					{
						Format:string("Du hast das Recht %s von %s bekommen!", license, GetPlayerNameEx(playerid));
						SendClientMessage(targetPlayerID, COLOR_INFO, string);
						Format:string("Du hast das Recht %s an %s gegeben!", license, GetPlayerNameEx(targetPlayerID));
						SendClientMessage(playerid, COLOR_INFO, string);
						printf("%s got license %s by %s", GetPlayerNameEx(targetPlayerID), license, GetPlayerNameEx(playerid));
					}
					else
					{
						Format:string("%s hat dir den %s Schein weggenommen!", GetPlayerNameEx(playerid), license);
						SendClientMessage(targetPlayerID, COLOR_INFO, string);
						Format:string("Du hast den %s Schein von %s weggenommen!", license, GetPlayerNameEx(targetPlayerID));
						SendClientMessage(playerid, COLOR_INFO, string);
						printf("%s has revoked the license %s of %s", GetPlayerNameEx(playerid), license, GetPlayerNameEx(targetPlayerID));
					}
				}
			}
			return COMMAND_OK;
		}
		else
		{
			return COMMAND_PLAYER_NOT_FOUND;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Du bist kein Fahrlehrer!");
		return true;
	}
}