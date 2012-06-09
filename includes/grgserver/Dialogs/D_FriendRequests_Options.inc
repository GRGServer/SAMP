ShowDialog:FriendRequests_Options(playerID, friendUserID)
{
	new list[2048];
	AddLine(list, LanguageString(playerID, 164));// Accept
	AddLine(list, LanguageString(playerID, 499));// Decline
	PVar:playerID[FRIENDUSERID] = friendUserID;
	CreateDialog(playerID, "FriendRequests_Options", DIALOG_STYLE_LIST, LanguageString(playerID, 496), list, "OK", LanguageString(playerID, 171));
}

DialogResponse:FriendRequests_Options(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (IsStr(inputText, LanguageString(playerID, 164)))// Accept
		{
			MySQLQuery("UPDATE `friends` SET `accepted` = '1' WHERE `userId1` = '%d' AND `userId2` = '%d'", PVar:playerID[FRIENDUSERID], PVar:playerID[USERID]);
			new friendPlayerID = GetPlayerByUserID(PVar:playerID[FRIENDUSERID]);
			if (friendPlayerID != INVALID_PLAYER_ID)
			{
				SendClientMessageEx(friendPlayerID, COLOR_INFO, 441, playerID);
			}
			SendClientMessageEx(playerID, COLOR_INFO, 442, GetMySQLValue("users", "username", "id", val2str(PVar:playerID[FRIENDUSERID])));
		}
		if (IsStr(inputText, LanguageString(playerID, 499)))// Decline
		{
			MySQLQuery("DELETE FROM `friends` WHERE `userId1` = '%d' AND `userId2` = '%d'", PVar:playerID[FRIENDUSERID], PVar:playerID[USERID]);
			new friendPlayerID = GetPlayerByUserID(PVar:playerID[FRIENDUSERID]);
			if (friendPlayerID != INVALID_PLAYER_ID)
			{
				SendClientMessageEx(friendPlayerID, COLOR_INFO, 500, playerID);
			}
			SendClientMessageEx(playerID, COLOR_INFO, 501, GetMySQLValue("users", "username", "id", val2str(PVar:playerID[FRIENDUSERID])));
		}
	}
	else
	{
		ShowDialog:FriendRequests(playerID);
	}
}