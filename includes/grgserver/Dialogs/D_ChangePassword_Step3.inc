ShowDialog:CHANGEPASSWORD_STEP3(playerID)
{
	CreateDialog(playerID, "CHANGEPASSWORD_STEP3", DIALOG_STYLE_PASSWORD, LanguageString(playerID, 240), LanguageString(playerID, 243), "OK", LanguageString(playerID, 171));
}

DialogResponse:CHANGEPASSWORD_STEP3(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strcmp(PVar:playerID[CHANGEPASSWORD], inputText))
		{
			SetUserDBValue(playerID, "Password", MD5(inputText));
			SendClientMessageEx(playerID, COLOR_INFO, 20);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 32);
			ShowDialog:CHANGEPASSWORD_STEP3(playerID);
		}
	}
	else
	{
		ShowDialog:CHANGEPASSWORD_STEP2(playerID);
	}
}