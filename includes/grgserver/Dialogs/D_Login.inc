ShowDialog:Login(playerID)
{
	CreateDialog(playerID, "Login", DIALOG_STYLE_PASSWORD, "Login", LanguageString(playerID, StringID:262("Please enter the password of your account.")), "OK", LanguageString(playerID, StringID:165("Cancel")));
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
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:30("The entered password is wrong!"));
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
						SendClientMessageEx(currentPlayerID, COLOR_JOINLEAVE, StringID:7("%p logged in"), playerID);
					}
				}
				LoadPlayer(playerID);
				ReloadTextDraws(playerID);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:35("You have been logged in successfully"));
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
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:36("You have to enter your password!"));
				ShowDialog:Login(playerID);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:36("You have to enter your password!"));
			ShowDialog:Login(playerID);
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_INFO, StringID:37("You can now quit the game"));
		Kick(playerID);
	}
	return true;
}