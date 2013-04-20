ShowDialog:Register_Password2(playerID)
{
	CreateDialog(playerID, "Register_Password2", DIALOG_STYLE_PASSWORD, LanguageString(playerID, "251"), LanguageString(playerID, "243"), LanguageString(playerID, "177"), LanguageString(playerID, "171"));
}

DialogResponse:Register_Password2(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strcmp(inputText, PVar:playerID[REGISTERPASSWORD]))
		{
			ShowDialog:Register_Gender(playerID);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, "32");
			ShowDialog:Register_Password1(playerID);
		}
	}
	else
	{
		ShowDialog:Register_Password1(playerID);
	}
	return true;
}