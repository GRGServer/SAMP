ShowDialog:FriendRequests(playerID)
{
	MySQLQuery("SELECT `users`.`username` FROM `friends` LEFT JOIN `users` ON `users`.`id` = `friends`.`userId1` WHERE `userId2` = '%d' AND `accepted` = '0'", PVar:playerID[USERID]);
	mysql_store_result();
	new rows = mysql_num_rows();
	new list[2048];
	if (rows)
	{
		while (FetchMySQLRow())
		{
			AddLine(list, GetMySQLField("username"));
		}
		FormatNew:title[64](LanguageString(playerID, StringID:480("Your friend requests (%d)")), rows);
		CreateDialog(playerID, "FriendRequests", DIALOG_STYLE_LIST, title, list, LanguageString(playerID, StringID:496("Options")), LanguageString(playerID, StringID:165("Cancel")));
	}
	mysql_free_result();
	return rows;
}

DialogResponse:FriendRequests(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new friendUserID = strval(GetMySQLValue("users", "id", "username", inputText));
		if (friendUserID)
		{
			ShowDialog:FriendRequests_Options(playerID, friendUserID);
		}
	}
}