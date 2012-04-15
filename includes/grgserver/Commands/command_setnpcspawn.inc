PCMD:setnpcspawn[NPCADMIN](playerID, params[], 282)
{
	new npcName[MAX_PLAYER_NAME];
	if (sscanf(params, "s", npcName))
	{
		CmdUsageMsg(playerID, "setnpcspawn", "Name");
		return COMMAND_USAGE;
	}
	MySQLQuery("SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(npcName));
	mysql_store_result();
	new id = strval(GetMySQLField("ID"));
	if (id)
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerPos(playerID, posX, posY, posZ);
		if (IsPlayerInAnyVehicle(playerID))
		{
			GetVehicleZAngle(GetPlayerVehicleID(playerID), angle);
		}
		else
		{
			GetPlayerFacingAngle(playerID, angle);
		}
		MySQLQuery("UPDATE `npcs` SET `SpawnPosX` = '%f', `SpawnPosY` = '%f', `SpawnPosZ` = '%f', `SpawnAngle` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, angle, id);
	}
	mysql_free_result();
	if (id)
	{
		SendClientMessageEx(playerID, COLOR_INFO, 283);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 284);
		return COMMAND_ERROR;
	}
}