ShowDialog:Register_Password1(playerID)
{
	CreateDialog(playerID, "Register_Password1", DIALOG_STYLE_PASSWORD, LanguageString(playerID, 260), LanguageString(playerID, 261), LanguageString(playerID, 177), LanguageString(playerID, 165));
}

DialogResponse:Register_Password1(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (strlen(inputText) >= REGISTER_PASSWORD_MIN && strlen(inputText) <= REGISTER_PASSWORD_MAX)
		{
			SetPVarStr:playerID[REGISTERPASSWORD][REGISTER_PASSWORD_MAX](inputText);
			ShowDialog:Register_Password2(playerID);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 31, REGISTER_PASSWORD_MIN, REGISTER_PASSWORD_MAX);
			ShowDialog:Register_Password1(playerID);
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_INFO, 37);
		Kick(playerID);
	}
}