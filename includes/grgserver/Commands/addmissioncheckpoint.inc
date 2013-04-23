/**
 * <summary>
 *	Add a new mission checkpoint to a mission group.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 *
 * <param name="params">
 *	The name of the mission group
 * </param>
 *
 * <returns>
 *	<item name="COMMAND_ERROR">An error occured while processing the command (e.g. unable to insert record to database)</item>
 *	<item name="COMMAND_OK">The checkpoint has been added successfully</item>
 *	<item name="COMMAND_USAGE">Usage message has been shown to the player</item>
 * </returns>
 */

PCMD:addmissioncheckpoint[MAPPER](playerID, params[], StringID:614(""))
{
	if (!StrNotNull(params))
	{
		CmdUsageMsg(playerID, "addmissioncheckpoint", "MissionGroup");
		return COMMAND_USAGE;
	}
	new missionID;
	MySQLQuery("SELECT `id` FROM `missioncheckpointgroups` WHERE `name` = '%s'", MySQLEscapeString(params));
	mysql_store_result();
	if (mysql_num_rows())
	{
		missionID = strval(GetMySQLField("id"));
	}
	mysql_free_result();
	if (!missionID)
	{
		MySQLQuery("INSERT INTO `missioncheckpointgroups` (`name`) VALUES('%s')", MySQLEscapeString(params));
		missionID = mysql_insert_id();
	}
	if (!missionID)
	{
		return COMMAND_ERROR;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	GetPlayerPos(playerID, posX, posY, posZ);
	MySQLQuery("SELECT MAX(`checkpointId`) AS `maxId` FROM `missioncheckpoints` WHERE `missionId` = '%d'", missionID);
	mysql_store_result();
	new checkpointID = strval(GetMySQLField("maxId")) + 1;
	mysql_free_result();
	MySQLQuery("INSERT INTO `missioncheckpoints` (`missionId`, `checkpointId`, `posX`, `posY`, `posZ`) VALUES('%d', '%d', '%f', '%f', '%f')", missionID, checkpointID, posX, posY, posZ);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:615(""), checkpointID, params);
	return COMMAND_OK;
}