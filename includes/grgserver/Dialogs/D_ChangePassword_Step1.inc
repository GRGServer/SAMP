ShowDialog:ChangePassword_Step1(playerID)
{
	CreateDialog(playerID, "ChangePassword_Step1", DIALOG_STYLE_PASSWORD, LanguageString(playerID, 240), LanguageString(playerID, 241), LanguageString(playerID, 177), LanguageString(playerID, 165));
}

DialogResponse:ChangePassword_Step1(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strcmp(GetUserDBValue(playerID, "Password"), MD5(inputText), true))
		{
			ShowDialog:ChangePassword_Step2(playerID);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 30);
			ShowDialog:ChangePassword_Step1(playerID);
		}
	}
}