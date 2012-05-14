ShowDialog:REGISTER_LOCATION(playerID)
{
	CreateDialog(playerID, "REGISTER_LOCATION", DIALOG_STYLE_INPUT, LanguageString(playerID, 258), LanguageString(playerID, 259), "OK", LanguageString(playerID, 171));
}

DialogResponse:REGISTER_LOCATION(playerID, response, listItem, inputText[])
{
	if (response)
	{
		SetPVarStr:playerID[REGISTERLOCATION][STRINGLENGTH_LOCATION](inputText);
		PVar:playerID[REGISTER_SELECTSKIN] = true;
	}
	else
	{
		ShowDialog:REGISTER_GENDER(playerID);
	}
}