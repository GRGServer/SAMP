ShowDialog:Login(playerID)
{
	CreateDialog(playerID, "Login", DIALOG_STYLE_PASSWORD, "Login", LanguageString(playerID, 262), "OK", LanguageString(playerID, 165));
}

DialogResponse:Login(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (strlen(inputText))
		{
			MySQLQuery("SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerID)));
			mysql_store_result();
			if (!strcmp(MD5(inputText), GetMySQLField("Password"), true))
			{
				PVar:playerID[USERID] = strval(GetMySQLField("ID"));
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 30);
				ShowDialog:Login(playerID);
			}
			mysql_free_result();
			if (PVar:playerID[USERID])
			{
				MySQLQuery("UPDATE `users` SET `LoginTime` = NOW(), `ClientVersion` = '%s' WHERE `ID` = '%d'", GetPlayerVersionEx(playerID), PVar:playerID[USERID]);
				printf("Player logged in: %s (UserID: %d)", GetPlayerNameEx(playerID), PVar:playerID[USERID]);
				PlayerLoop(currentPlayerID)
				{
					if (currentPlayerID != playerID)
					{
						SendClientMessageEx(currentPlayerID, COLOR_JOINLEAVE, 7, playerID);
					}
				}
				TogglePlayerSpectating(playerID, false);
				LoadPlayer(playerID);
				ReloadTextDraws(playerID);
				PVar:playerID[SPAWNAFTERLOGIN] = true;
				SendClientMessageEx(playerID, COLOR_INFO, 35);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 36);
			ShowDialog:Login(playerID);
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_INFO, 37);
		Kick(playerID);
	}
	return true;
}