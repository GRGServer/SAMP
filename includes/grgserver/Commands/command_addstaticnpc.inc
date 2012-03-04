PCMD:addstaticnpc[NPCADMIN](playerid, params[], "NPC ohne Aufnahme an die aktuelle Position stellen")
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
	MySQLQuery("INSERT INTO `npcs` (`Name`, `SpawnPosX`, `SpawnPosY`, `SpawnPosZ`, `SpawnAngle`, `AutoConnect`) VALUES('%s', '%f', '%f', '%f', '%f', '1')", MySQLEscapeString(playerName), posX, posY, posZ, angle);
	new id = mysql_insert_id();
	if (id > 0)
	{
		Format:playerName("NPC_%s", playerName);
		ConnectNPC(playerName, NPC_SCRIPTNAME);
		FormatNew:string[70]("Der NPC wurde erfolgreich unter der ID %d gespeichert", id);
		SendClientMessage(playerid, COLOR_INFO, string);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Während dem Speichern ist ein Fehler aufgetreten!");
	}
	return COMMAND_ERROR;
}