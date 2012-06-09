ShowDialog:FriendRequests(playerID)
{
	MySQLQuery("SELECT `users`.`Username` FROM `friends` LEFT JOIN `users` ON `users`.`ID` = `friends`.`UserID1` WHERE `UserID2` = '%d' AND `Accepted` = '0'", PVar:playerID[USERID]);
	mysql_store_result();
	new rows = mysql_num_rows();
	new list[2048];
	if (rows)
	{
		while (FetchMySQLRow())
		{
			AddLine(list, GetMySQLField("Username"));
		}
		FormatNew:title[64](LanguageString(playerID, 480), rows);
		CreateDialog(playerID, "FriendRequests", DIALOG_STYLE_LIST, title, list, LanguageString(playerID, 496), LanguageString(playerID, 165));
	}
	mysql_free_result();
	return rows;
}

DialogResponse:FriendRequests(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new friendUserID = strval(GetMySQLValue("users", "ID", "Username", inputText));
		if (friendUserID)
		{
			ShowDialog:FriendRequests_Options(playerID, friendUserID);
		}
	}
}