ShowDialog:Register_Location(playerID)
{
	CreateDialog(playerID, "Register_Location", DIALOG_STYLE_INPUT, LanguageString(playerID, 258), LanguageString(playerID, 259), "OK", LanguageString(playerID, 171));
}

DialogResponse:Register_Location(playerID, response, listItem, inputText[])
{
	if (response)
	{
		SetPVarStr:playerID[REGISTERLOCATION][STRINGLENGTH_LOCATION](inputText);
		PVar:playerID[REGISTER_SELECTSKIN] = true;
	}
	else
	{
		ShowDialog:Register_Gender(playerID);
	}
}