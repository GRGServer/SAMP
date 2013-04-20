ShowDialog:ChatMode_FriendList(playerID)
{
	new list[2048];
	MySQLQuery("SELECT `users`.`username` FROM `friends` LEFT JOIN `users` ON (`users`.`id` = `friends`.`userId1` OR `users`.`id` = `friends`.`userId2`) WHERE (`friends`.`userId1` = '%d' OR `friends`.`userId2` = '%d') AND `friends`.`accepted` AND `users`.`id` != '%d'", PVar:playerID[USERID], PVar:playerID[USERID], PVar:playerID[USERID]);
	mysql_store_result();
	new rows = mysql_num_rows();
	if (rows)
	{
		while (FetchMySQLRow())
		{
			AddLine(list, GetMySQLField("username"));
		}
		CreateDialog(playerID, "ChatMode_FriendList", DIALOG_STYLE_LIST, LanguageString(playerID, "502"), list, "OK", LanguageString(playerID, "171"));
	}
	mysql_free_result();
	if (!rows)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, "503");
		ShowDialog:ChatMode(playerID);
	}
}

DialogResponse:ChatMode_FriendList(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new friendUserID = strval(GetMySQLValue("users", "id", "username", inputText));
		if (friendUserID)
		{
			SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE]("PLAYER");
			PVar:playerID[CHATMODE_USERID] = friendUserID;
			SendClientMessageEx(playerID, COLOR_INFO, "313", GetChatModeName(playerID, PVar:playerID[CHATMODE]));
		}
	}
	else
	{
		ShowDialog:ChatMode(playerID);
	}
}