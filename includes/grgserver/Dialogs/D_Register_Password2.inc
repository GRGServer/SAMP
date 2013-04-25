ShowDialog:Register_Password2(playerID)
{
	CreateDialog(playerID, "Register_Password2", DIALOG_STYLE_PASSWORD, LanguageString(playerID, StringID:251("Repeat password")), LanguageString(playerID, StringID:243("Please repeat your new password to verfify.")), LanguageString(playerID, StringID:177("Next")), LanguageString(playerID, StringID:171("Back")));
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
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:32("The entered passwords do not match! Please try again."));
			ShowDialog:Register_Password1(playerID);
		}
	}
	else
	{
		ShowDialog:Register_Password1(playerID);
	}
	return true;
}