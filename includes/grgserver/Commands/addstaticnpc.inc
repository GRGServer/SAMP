PCMD:addstaticnpc[NPCADMIN](playerid, params[], 97)
{
	new playerName[MAX_PLAYER_NAME];
	if (sscanf(params, "s", playerName))
	{
		CmdUsageMsg(playerid, "addstaticnpc", "Playername");
		return COMMAND_USAGE;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	GetPlayerPos(playerid, posX, posY, posZ);
	GetPlayerFacingAngle(playerid, angle);
	MySQLQuery("INSERT INTO `npcs` (`name`, `spawnPosX`, `spawnPosY`, `spawnPosZ`, `spawnAngle`, `autoConnect`) VALUES('%s', '%f', '%f', '%f', '%f', '1')", MySQLEscapeString(playerName), posX, posY, posZ, angle);
	new id = mysql_insert_id();
	if (id > 0)
	{
		ConnectNPC(playerName, NPC_SCRIPTNAME);
		SendClientMessageEx(playerid, COLOR_INFO, 83, id);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_ERROR, 84);
	}
	return COMMAND_ERROR;
}