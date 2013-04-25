ShowDialog:Register_Location(playerID)
{
	CreateDialog(playerID, "Register_Location", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:258("Enter home location")), LanguageString(playerID, StringID:259("Enter your home location.\n\nNote: This can also be a location in San Andreas.")), "OK", LanguageString(playerID, StringID:171("Back")));
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
		PVar:playerID[ONLINESINCE] = gettime();
		MySQLQuery("UPDATE `users` SET `registerTime` = NOW(), `loginTime` = NOW(), `clientVersion` = '%s' WHERE `id` = '%d'", MySQLEscapeString(GetPlayerVersionEx(playerID)), PVar:playerID[USERID]);
		SavePlayer(playerID);
		LoadPlayer(playerID);
		ReloadTextDraws(playerID);
		printf("Player registered: %s (UserID: %d)", GetPlayerNameEx(playerID), PVar:playerID[USERID]);
		PlayerLoop(currentPlayerID)
		{
			if (currentPlayerID != playerID)
			{
				SendClientMessageEx(currentPlayerID, COLOR_JOINLEAVE, StringID:7("%p logged in"), playerID);
			}
		}
		PVar:playerID[SPAWNAFTERTUTORIALSTART] = false;
		PlayerPlaySound(playerID, 1063, 0.0, 0.0, 0.0);
		PVar:playerID[PLAYRANDOMCAMERACUTS] = false;
		StartScreenFader(playerID, 0, 0, 0, 10, 0, FADE_TUTORIAL_START, 0);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:139("You were registered successfully and are now logged in."));
	}
	else
	{
		ShowDialog:Register_Gender(playerID);
	}
}