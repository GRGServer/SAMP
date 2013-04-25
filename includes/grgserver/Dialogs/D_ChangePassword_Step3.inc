ShowDialog:ChangePassword_Step3(playerID)
{
	CreateDialog(playerID, "ChangePassword_Step3", DIALOG_STYLE_PASSWORD, LanguageString(playerID, StringID:240("Change account password")), LanguageString(playerID, StringID:243("Please repeat your new password to verfify.")), "OK", LanguageString(playerID, StringID:171("Back")));
}

DialogResponse:ChangePassword_Step3(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strcmp(PVar:playerID[CHANGEPASSWORD], inputText))
		{
			MySQLQuery("UPDATE `users` SET `password` = '%s' WHERE `id` = '%d'", MD5(inputText), PVar:playerID[USERID]);
			SendClientMessageEx(playerID, COLOR_INFO, StringID:20("Your password has been changed"));
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:32("The entered passwords do not match! Please try again."));
			ShowDialog:ChangePassword_Step3(playerID);
		}
	}
	else
	{
		ShowDialog:ChangePassword_Step2(playerID);
	}
}