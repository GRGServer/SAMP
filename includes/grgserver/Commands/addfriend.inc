/**
 * <summary>
 *	Add the specified player as a friend or accept a friend request from the specified player.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which called the command.
 * </param>
 *
 * <param name="params">
 *	<title>The parameters passed to this command.</title>
 *	<item>ID or name of the player which should be added or accepted</item>
 * </param>
 *
 * <returns>
 *	<item>COMMAND_ERROR</item>
 *	<item>COMMAND_OK</item>
 *	<item>COMMAND_PLAYER_NOT_FOUND</item>
 *	<item>COMMAND_USAGE</item>
 * </returns>
 */

CMD:addfriend(playerID, params[], StringID:439(""))
{
	new targetPlayerID;
	if (sscanf(params, "u", targetPlayerID))
	{
		CmdUsageMsg(playerID, "addfriend", "Playername/ID");
		return COMMAND_USAGE;
	}
	if (targetPlayerID == INVALID_PLAYER_ID || !IsLoggedIn(targetPlayerID))
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	if (playerID == targetPlayerID)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:445(""));
		return COMMAND_ERROR;
	}
	new alreadyInList;
	MySQLQuery("SELECT * FROM `friends` WHERE (`userId1` = '%d' AND `userId2` = '%d') OR (`userId2` = '%d' AND `userId1` = '%d')", PVar:playerID[USERID], PVar:targetPlayerID[USERID], PVar:playerID[USERID], PVar:targetPlayerID[USERID]);
	mysql_store_result();
	alreadyInList = mysql_num_rows();
	mysql_free_result();
	if (alreadyInList)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:440(""), targetPlayerID);
		return COMMAND_ERROR;
	}
	MySQLQuery("INSERT INTO `friends` (`userId1`, `userId2`) VALUES('%d', '%d')", PVar:playerID[USERID], PVar:targetPlayerID[USERID]);
	SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:443(""), playerID, playerID);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:444(""), targetPlayerID);
	return COMMAND_OK;
}