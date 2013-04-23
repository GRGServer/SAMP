CMD:removefriend(playerID, params[], StringID:446(""))
{
	new targetPlayerID;
	if (sscanf(params, "u", targetPlayerID))
	{
		CmdUsageMsg(playerID, "removefriend", "Playername/ID");
		return COMMAND_USAGE;
	}
	if (targetPlayerID == INVALID_PLAYER_ID || !IsLoggedIn(targetPlayerID))
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	MySQLQuery("SELECT * FROM `friends` WHERE (`userId1` = '%d' AND `userId2` = '%d') OR (`userId2` = '%d' AND `userId1` = '%d')", PVar:playerID[USERID], PVar:targetPlayerID[USERID], PVar:playerID[USERID], PVar:targetPlayerID[USERID]);
	mysql_store_result();
	new isInList = mysql_num_rows();
	mysql_free_result();
	if (!isInList)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:447(""), targetPlayerID);
		return COMMAND_ERROR;
	}
	MySQLQuery("DELETE FROM `friends` WHERE (`userId1` = '%d' AND `userId2` = '%d') OR (`userId2` = '%d' AND `userId1` = '%d')", PVar:playerID[USERID], PVar:targetPlayerID[USERID], PVar:playerID[USERID], PVar:targetPlayerID[USERID]);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:448(""), targetPlayerID);
	SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:449(""), playerID);
	return COMMAND_OK;
}