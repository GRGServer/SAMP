ShowDialog:RestartGamemode(playerID)
{
	CreateDialog(playerID, "RestartGamemode", DIALOG_STYLE_INPUT, LanguageString(playerID, "249"), LanguageString(playerID, "250"), "OK", LanguageString(playerID, "165"));
}

DialogResponse:RestartGamemode(playerID, response, listItem, inputText[])
{
	if (!response)
	{
		return false;
	}
	if (!StrNotNull(inputText))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, "410");
		return false;
	}
	RestartGameMode(playerID, inputText);
	return true;
}