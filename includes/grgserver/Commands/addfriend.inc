CMD:addfriend(playerID, params[], 439)
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
		SendClientMessageEx(playerID, COLOR_ERROR, 445);
		return COMMAND_ERROR;
	}
	new alreadyInList;
	MySQLQuery("SELECT * FROM `friends` WHERE `UserID` = '%d' AND `FriendUserID` = '%d'", PVar:playerID[USERID], PVar:targetPlayerID[USERID]);
	mysql_store_result();
	alreadyInList = mysql_num_rows();
	mysql_free_result();
	if (alreadyInList)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 440, targetPlayerID);
		return COMMAND_ERROR;
	}
	MySQLQuery("INSERT INTO `friends` (`UserID`, `FriendUserID`) VALUES('%d', '%d')", PVar:playerID[USERID], PVar:targetPlayerID[USERID]);
	MySQLQuery("SELECT * FROM `friends` WHERE `UserID` = '%d' AND `FriendUserID` = '%d'", PVar:targetPlayerID[USERID], PVar:playerID[USERID]);
	mysql_store_result();
	alreadyInList = mysql_num_rows();
	mysql_free_result();
	if (alreadyInList)
	{
		SendClientMessageEx(targetPlayerID, COLOR_INFO, 441, playerID);
		SendClientMessageEx(playerID, COLOR_INFO, 442, targetPlayerID);
	}
	else
	{
		SendClientMessageEx(targetPlayerID, COLOR_INFO, 443, playerID, playerID);
		SendClientMessageEx(playerID, COLOR_INFO, 444, targetPlayerID);
	}
	return COMMAND_OK;
}