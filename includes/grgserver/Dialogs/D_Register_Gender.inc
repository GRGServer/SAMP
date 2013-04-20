ShowDialog:Register_Gender(playerID)
{
	FormatNew:options[50]("%s\n%s", LanguageString(playerID, "256"), LanguageString(playerID, "257"));
	CreateDialog(playerID, "Register_Gender", DIALOG_STYLE_LIST, LanguageString(playerID, "255"), options, LanguageString(playerID, "NEXT"), LanguageString(playerID, "BACK"));
}

DialogResponse:Register_Gender(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (listItem)
		{
			PVar:playerID[GENDER] = 'F';// Female
			PVar:playerID[SKIN] = femaleSkins[random(sizeof(femaleSkins))];
		}
		else
		{
			PVar:playerID[GENDER] = 'M';// Male
			PVar:playerID[SKIN] = maleSkins[random(sizeof(maleSkins))];
		}
		SetPlayerSkin(playerID, PVar:playerID[SKIN]);
		ShowDialog:Register_Birthdate(playerID);
	}
	else
	{
		ShowDialog:Register_Password2(playerID);
	}
}