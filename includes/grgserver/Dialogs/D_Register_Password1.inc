ShowDialog:Register_Password1(playerID)
{
	CreateDialog(playerID, "Register_Password1", DIALOG_STYLE_PASSWORD, LanguageString(playerID, StringID:260("Register")), LanguageString(playerID, StringID:261("You are not registered yet!\n\nPlease enter a new password for your account.")), LanguageString(playerID, StringID:177("Next")), LanguageString(playerID, StringID:171("Back")));
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
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:31("Please use a password with a length between %d and %d!"), REGISTER_PASSWORD_MIN, REGISTER_PASSWORD_MAX);
			ShowDialog:Register_Password1(playerID);
		}
	}
	else
	{
		ShowDialog:Register_Language(playerID);
	}
}