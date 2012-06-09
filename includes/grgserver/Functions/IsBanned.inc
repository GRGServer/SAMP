IsBanned(playerID, showMessage)
{
	new ip[16];
	GetPlayerIp(playerID, ip, sizeof(ip));
	new userID;
	MySQLQuery("SELECT * FROM `users` WHERE `username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerID)));
	mysql_store_result();
	userID = strval(GetMySQLField("id"));
	mysql_free_result();
	if (!userID)
	{
		userID = -1;
	}
	MySQLQuery("SELECT * FROM `bans` WHERE `ip` = '%s' OR `userId` = '%d'", ip, userID);
	mysql_store_result();
	new rows = mysql_num_rows();
	if (rows)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 473);
			SendClientMessageEx(playerID, COLOR_INFO, 474, GetMySQLField("reason"));
			SendClientMessageEx(playerID, COLOR_INFO, 475);
		}
	}
	mysql_free_result();
	return rows;
}