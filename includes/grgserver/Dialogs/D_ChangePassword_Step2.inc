ShowDialog:ChangePassword_Step2(playerID)
{
	CreateDialog(playerID, "ChangePassword_Step2", DIALOG_STYLE_PASSWORD, LanguageString(playerID, StringID:240("Change account password")), LanguageString(playerID, StringID:242("Enter your new password.")), LanguageString(playerID, StringID:177("Next")), LanguageString(playerID, StringID:171("Back")));
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
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:31("Please use a password with a length between %d and %d!"), REGISTER_PASSWORD_MIN, REGISTER_PASSWORD_MAX);
			ShowDialog:ChangePassword_Step2(playerID);
		}
	}
	else
	{
		ShowDialog:ChangePassword_Step1(playerID);
	}
}