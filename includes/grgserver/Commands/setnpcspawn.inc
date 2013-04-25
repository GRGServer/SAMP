PCMD:setnpcspawn[NPCADMIN](playerID, params[], StringID:282("Set the spawn position of a NPC"))
{
	new npcName[MAX_PLAYER_NAME];
	if (sscanf(params, "s[" #MAX_PLAYER_NAME "]", npcName))
	{
		CmdUsageMsg(playerID, "setnpcspawn", "Name");
		return COMMAND_USAGE;
	}
	MySQLQuery("SELECT * FROM `npcs` WHERE `name` = '%s'", MySQLEscapeString(npcName));
	mysql_store_result();
	new id = strval(GetMySQLField("id"));
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
		MySQLQuery("UPDATE `npcs` SET `spawnPosX` = '%f', `spawnPosY` = '%f', `spawnPosZ` = '%f', `spawnAngle` = '%f' WHERE `id` = '%d'", posX, posY, posZ, angle, id);
	}
	mysql_free_result();
	if (id)
	{
		SendClientMessageEx(playerID, COLOR_INFO, StringID:283("The spawn position of the NPC has been changed"));
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:284("NPC not found!"));
		return COMMAND_ERROR;
	}
}