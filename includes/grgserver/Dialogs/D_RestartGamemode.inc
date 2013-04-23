ShowDialog:RestartGamemode(playerID)
{
	CreateDialog(playerID, "RestartGamemode", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:249("")), LanguageString(playerID, StringID:250("")), "OK", LanguageString(playerID, StringID:165("")));
}

DialogResponse:RestartGamemode(playerID, response, listItem, inputText[])
{
	if (!response)
	{
		return false;
	}
	if (!StrNotNull(inputText))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:410(""));
		return false;
	}
	RestartGameMode(playerID, inputText);
	return true;
}