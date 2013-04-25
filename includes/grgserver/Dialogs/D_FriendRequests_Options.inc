ShowDialog:FriendRequests_Options(playerID, friendUserID)
{
	new list[2048];
	AddLine(list, LanguageString(playerID, StringID:164("Accept")));// Accept
	AddLine(list, LanguageString(playerID, StringID:499("Decline")));// Decline
	PVar:playerID[FRIENDUSERID] = friendUserID;
	CreateDialog(playerID, "FriendRequests_Options", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:496("Options")), list, "OK", LanguageString(playerID, StringID:171("Back")));
}

DialogResponse:FriendRequests_Options(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (IsStr(inputText, LanguageString(playerID, StringID:164("Accept"))))// Accept
		{
			MySQLQuery("UPDATE `friends` SET `accepted` = '1' WHERE `userId1` = '%d' AND `userId2` = '%d'", PVar:playerID[FRIENDUSERID], PVar:playerID[USERID]);
			new friendPlayerID = GetPlayerByUserID(PVar:playerID[FRIENDUSERID]);
			if (friendPlayerID != INVALID_PLAYER_ID)
			{
				SendClientMessageEx(friendPlayerID, COLOR_INFO, StringID:441("%p has confirmed your friend request"), playerID);
			}
			SendClientMessageEx(playerID, COLOR_INFO, StringID:442("%s has been added to your friend list"), GetMySQLValue("users", "username", "id", val2str(PVar:playerID[FRIENDUSERID])));
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:499("Decline"))))// Decline
		{
			MySQLQuery("DELETE FROM `friends` WHERE `userId1` = '%d' AND `userId2` = '%d'", PVar:playerID[FRIENDUSERID], PVar:playerID[USERID]);
			new friendPlayerID = GetPlayerByUserID(PVar:playerID[FRIENDUSERID]);
			if (friendPlayerID != INVALID_PLAYER_ID)
			{
				SendClientMessageEx(friendPlayerID, COLOR_INFO, StringID:500("%p has declined your friend request!"), playerID);
			}
			SendClientMessageEx(playerID, COLOR_INFO, StringID:501("You have declined the friend request of %s!"), GetMySQLValue("users", "username", "id", val2str(PVar:playerID[FRIENDUSERID])));
		}
	}
	else
	{
		ShowDialog:FriendRequests(playerID);
	}
}