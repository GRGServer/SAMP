ShowDialog:RestartGamemode(playerID)
{
	CreateDialog(playerID, "RestartGamemode", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:249("Restart gamemode")), LanguageString(playerID, StringID:250("Please give a reason why you want to restart the gamemode.")), "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:RestartGamemode(playerID, response, listItem, inputText[])
{
	if (!response)
	{
		return false;
	}
	if (!StrNotNull(inputText))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:410("You have to give a reason to restart the gamemode!"));
		return false;
	}
	RestartGameMode(playerID, inputText);
	return true;
}