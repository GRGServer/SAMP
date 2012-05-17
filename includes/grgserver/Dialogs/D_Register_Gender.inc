ShowDialog:Register_Gender(playerID)
{
	FormatNew:options[50]("%s\n%s", LanguageString(playerID, 256), LanguageString(playerID, 257));
	CreateDialog(playerID, "Register_Gender", DIALOG_STYLE_LIST, LanguageString(playerID, 255), options, LanguageString(playerID, 177), LanguageString(playerID, 171));
}

DialogResponse:Register_Gender(playerID, response, listItem, inputText[])
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
		ShowDialog:Register_Birthdate(playerID);
	}
	else
	{
		ShowDialog:Register_Password2(playerID);
	}
}