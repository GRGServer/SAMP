ShowDialog:GiveWanted(playerID)
{
	CreateDialog(playerID, "GiveWanted", DIALOG_STYLE_INPUT, LanguageString(playerID, 558), LanguageString(playerID, 559), "OK", LanguageString(playerID, 165));
}

DialogResponse:GiveWanted(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 560);
			ShowDialog:GiveWanted(playerID);
		}
		else
		{
			new wanted = strval(inputText);
			new targetPlayerID;
			SetPlayerWantedLevel(targetPlayerID, wanted);
			SendClientMessageEx(playerID, COLOR_INFO, 561, wanted);
			MySQLQuery("UPDATE `users` SET `wantedLevel` = '%d' WHERE `id` = '%d'", wanted, PVar:playerID[USERID]);
		}
	}
	else
	{
		ShowDialog:Bank_HasAccount(playerID);
	}
}