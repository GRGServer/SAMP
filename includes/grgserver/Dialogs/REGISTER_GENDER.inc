ShowDialog:REGISTER_GENDER(playerID)
{
	FormatNew:options[50]("%s\n%s", LanguageString(playerID, 256), LanguageString(playerID, 257));
	CreateDialog(playerID, "REGISTER_GENDER", DIALOG_STYLE_LIST, LanguageString(playerID, 255), options, LanguageString(playerID, 177), LanguageString(playerID, 171));
}

DialogResponse:REGISTER_GENDER(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (listItem)
		{
			PVar:playerID[GENDER] = 'F';// Female
			PVar:playerID[SKIN] = REGISTER_SKIN_FEMALE;
		}
		else
		{
			PVar:playerID[GENDER] = 'M';// Male
			PVar:playerID[SKIN] = REGISTER_SKIN_MALE;
		}
		SetPlayerSkin(playerID, PVar:playerID[SKIN]);
		ShowDialog:REGISTER_BIRTHDATE(playerID);
	}
	else
	{
		ShowDialog:REGISTER_PASSWORD2(playerID);
	}
}