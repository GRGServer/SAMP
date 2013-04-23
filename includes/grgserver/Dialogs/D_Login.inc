ShowDialog:Login(playerID)
{
	CreateDialog(playerID, "Login", DIALOG_STYLE_PASSWORD, "Login", LanguageString(playerID, StringID:262("")), "OK", LanguageString(playerID, StringID:165("")));
}

DialogResponse:Login(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (strlen(inputText))
		{
			MySQLQuery("SELECT `id` FROM `users` WHERE `username` = '%s' AND `password` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerID)), MD5(inputText));
			mysql_store_result();
			if (mysql_num_rows())
			{
				PVar:playerID[USERID] = strval(GetMySQLField("id"));
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:30(""));
				ShowDialog:Login(playerID);
			}
			mysql_free_result();
			if (PVar:playerID[USERID])
			{
				MySQLQuery("UPDATE `users` SET `loginTime` = NOW(), `clientVersion` = '%s' WHERE `id` = '%d'", GetPlayerVersionEx(playerID), PVar:playerID[USERID]);
				printf("Player logged in: %s (UserID: %d)", GetPlayerNameEx(playerID), PVar:playerID[USERID]);
				PlayerLoop(currentPlayerID)
				{
					if (currentPlayerID != playerID)
					{
						SendClientMessageEx(currentPlayerID, COLOR_JOINLEAVE, StringID:7(""), playerID);
					}
				}
				LoadPlayer(playerID);
				ReloadTextDraws(playerID);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:35(""));
				PVar:playerID[PLAYRANDOMCAMERACUTS] = false;
				if (PVar:playerID[INTUTORIAL])// The player is still in the tutorial (e.g. Quit game while in tutorial)
				{
					StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_TUTORIAL_START, 0);
				}
				else
				{
					StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_LOGIN, 0);
				}
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:36(""));
				ShowDialog:Login(playerID);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:36(""));
			ShowDialog:Login(playerID);
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_INFO, StringID:37(""));
		Kick(playerID);
	}
	return true;
}