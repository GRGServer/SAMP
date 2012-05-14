ShowDialog:CHANGEPASSWORD_STEP1(playerID)
{
	CreateDialog(playerID, "CHANGEPASSWORD_STEP1", DIALOG_STYLE_PASSWORD, LanguageString(playerID, 240), LanguageString(playerID, 241), LanguageString(playerID, 177), LanguageString(playerID, 165));
}

DialogResponse:CHANGEPASSWORD_STEP1(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strcmp(GetUserDBValue(playerID, "Password"), MD5(inputText), true))
		{
			ShowDialog:CHANGEPASSWORD_STEP2(playerID);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 30);
			ShowDialog:CHANGEPASSWORD_STEP1(playerID);
		}
	}
}