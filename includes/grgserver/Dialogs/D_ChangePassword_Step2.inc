ShowDialog:ChangePassword_Step2(playerID)
{
	CreateDialog(playerID, "ChangePassword_Step2", DIALOG_STYLE_PASSWORD, LanguageString(playerID, 240), LanguageString(playerID, 242), LanguageString(playerID, 177), LanguageString(playerID, 171));
}

DialogResponse:ChangePassword_Step2(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (strlen(inputText) >= REGISTER_PASSWORD_MIN && strlen(inputText) <= REGISTER_PASSWORD_MAX)
		{
			SetPVarStr:playerID[CHANGEPASSWORD][REGISTER_PASSWORD_MAX](inputText);
			ShowDialog:ChangePassword_Step3(playerID);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 31, REGISTER_PASSWORD_MIN, REGISTER_PASSWORD_MAX);
			ShowDialog:ChangePassword_Step2(playerID);
		}
	}
	else
	{
		ShowDialog:ChangePassword_Step1(playerID);
	}
}