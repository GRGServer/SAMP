OnPlayerEnteredVehicle(playerID, vehicleID, isPassenger)
{
	MySQLQuery("SELECT `ID` FROM `vehicles` WHERE `ID` = '%d' AND `Locked`", VehicleProperty:vehicleID[SAVEID]);
	mysql_store_result();
	new isLocked = mysql_num_rows();
	mysql_free_result();
	if (isLocked)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 482);
	}
	else
	{
		if (IsPlayerNPC(playerID))
		{
			return true;
		}
		new modelID = GetVehicleModel(vehicleID);
		if (modelID == 420)
		{
			new npcPlayerID;
			MySQLQuery("SELECT * FROM `npcs` WHERE `VehicleID` = '%d'", VehicleProperty:vehicleID[SAVEID]);
			mysql_store_result();
			if (mysql_num_rows())
			{
				FormatNew:npcName[MAX_PLAYER_NAME]("NPC_%s", GetMySQLField("Name"));
				sscanf(npcName, "u", npcPlayerID);
			}
			mysql_free_result();
			if (npcPlayerID != INVALID_PLAYER_ID)
			{
				if (isPassenger)
				{
					SendNPCCommand(npcPlayerID, "start");
					return true;
				}
				else
				{
					RemovePlayerFromVehicle(playerID);
					return false;
				}
			}
		}
		if (!isPassenger && !GetVehicleEngineState(vehicleID))
		{
			SendClientMessageEx(playerID, COLOR_INFO, 424);
		}
	}
	return true;
}