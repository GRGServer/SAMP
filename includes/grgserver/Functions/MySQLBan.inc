MySQLBan(playerID, targetPlayerID, reason[], kick)
{
	new executorUserID;
	new ip[16];
	GetPlayerIp(targetPlayerID, ip, sizeof(ip));
	if (playerID != INVALID_PLAYER_ID)
	{
		executorUserID = PVar:playerID[USERID];
	}
	MySQLQuery("REPLACE INTO `bans` (`UserID`, `IP`, `ExecutorUserID`, `Time`, `Reason`) VALUES('%d', '%s', '%d', NOW(), '%s')", PVar:targetPlayerID[USERID], ip, executorUserID, MySQLEscapeString(reason));
	if (playerID == INVALID_PLAYER_ID)
	{
		printf("%s has been banned, Reason: %s", GetPlayerNameEx(targetPlayerID), reason);
	}
	else
	{
		printf("%s has been banned by %s, Reason: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerID), reason);
	}
	if (kick)
	{
		Kick(targetPlayerID);
	}
}