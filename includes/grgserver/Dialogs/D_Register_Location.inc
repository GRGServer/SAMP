ShowDialog:Register_Location(playerID)
{
	CreateDialog(playerID, "Register_Location", DIALOG_STYLE_INPUT, LanguageString(playerID, 258), LanguageString(playerID, 259), "OK", LanguageString(playerID, 171));
}

DialogResponse:Register_Location(playerID, response, listItem, inputText[])
{
	if (response)
	{
		MySQLQuery("INSERT INTO `users` (`username`, `password`, `gender`, `birthDate`, `location`) VALUES('%s', '%s', '%c', '%s', '%s')", MySQLEscapeString(GetPlayerNameEx(playerID)), MD5(PVar:playerID[REGISTERPASSWORD]), PVar:playerID[GENDER], PVar:playerID[BIRTHDATE], MySQLEscapeString(inputText));
		PVar:playerID[USERID] = mysql_insert_id();
		SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE]("INRANGE");
		PVar:playerID[INTUTORIAL] = true;
		PVar:playerID[SHOWCLOCK] = true;
		MySQLQuery("UPDATE `users` SET `registerTime` = NOW(), `loginTime` = NOW(), `clientVersion` = '%s' WHERE `id` = '%d'", MySQLEscapeString(GetPlayerVersionEx(playerID)), PVar:playerID[USERID]);
		SavePlayer(playerID);
		LoadPlayer(playerID);
		ReloadTextDraws(playerID);
		printf("Player registered: %s (UserID: %d)", GetPlayerNameEx(playerID), PVar:playerID[USERID]);
		PlayerLoop(currentPlayerID)
		{
			if (currentPlayerID != playerID)
			{
				SendClientMessageEx(currentPlayerID, COLOR_JOINLEAVE, 7, playerID);
			}
		}
		PVar:playerID[SPAWNAFTERTUTORIALSTART] = false;
		PlayerPlaySound(playerID, 1063, 0.0, 0.0, 0.0);
		PVar:playerID[PLAYRANDOMCAMERACUTS] = false;
		StartScreenFader(playerID, 0, 0, 0, 10, 0, FADE_TUTORIAL_START, 0);
		SendClientMessageEx(playerID, COLOR_INFO, 139);
	}
	else
	{
		ShowDialog:Register_Gender(playerID);
	}
}