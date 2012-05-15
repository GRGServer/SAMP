ShowDialog:RESTARTGAMEMODE(playerID)
{
	ShowMsgBox(playerID, "RESTARTGAMEMODE", LanguageString(playerID, 249), LanguageString(playerID, 250), MSGBOXSTYLE_YESNO);
}

DialogResponse:RESTARTGAMEMODE(playerID, response, listItem, inputText[])
{
	if (response)
	{
		PlayerLoop(currentPlayerID)
		{
			SavePlayer(currentPlayerID);
			if (currentPlayerID != playerID)
			{
				SendClientMessageEx(currentPlayerID, COLOR_INFO, 43, playerID);
			}
		}
		SendClientMessageEx(playerID, COLOR_INFO, 42);
		printf("%s has restarted the gamemode", GetPlayerNameEx(playerID));
		SendRconCommand("gmx");
	}
}