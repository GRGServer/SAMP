ShowDialog:REGISTER_PASSWORD2(playerID)
{
	CreateDialog(playerID, "REGISTER_PASSWORD1", DIALOG_STYLE_PASSWORD, LanguageString(playerID, 251), LanguageString(playerID, 243), LanguageString(playerID, 177), LanguageString(playerID, 171));
}

DialogResponse:REGISTER_PASSWORD2(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strcmp(inputText, PVar:playerID[REGISTERPASSWORD]))
		{
			ShowDialog:REGISTER_GENDER(playerID);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 32);
			ShowDialog:REGISTER_PASSWORD1(playerID);
		}
	}
	else
	{
		ShowDialog:REGISTER_PASSWORD1(playerID);
	}
	return true;
}