IsBanned(playerID, showMessage)
{
	new ip[16];
	GetPlayerIp(playerID, ip, sizeof(ip));
	new userID;
	MySQLQuery("SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerID)));
	mysql_store_result();
	userID = strval(GetMySQLField("ID"));
	mysql_free_result();
	if (!userID)
	{
		userID = -1;
	}
	MySQLQuery("SELECT * FROM `bans` WHERE `IP` = '%s' OR `UserID` = '%d'", ip, userID);
	mysql_store_result();
	new rows = mysql_num_rows();
	if (rows)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 473);
			SendClientMessageEx(playerID, COLOR_INFO, 474, GetMySQLField("Reason"));
			SendClientMessageEx(playerID, COLOR_INFO, 475);
		}
	}
	mysql_free_result();
	return rows;
}