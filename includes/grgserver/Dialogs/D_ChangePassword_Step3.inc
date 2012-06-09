ShowDialog:ChangePassword_Step3(playerID)
{
	CreateDialog(playerID, "ChangePassword_Step3", DIALOG_STYLE_PASSWORD, LanguageString(playerID, 240), LanguageString(playerID, 243), "OK", LanguageString(playerID, 171));
}

DialogResponse:ChangePassword_Step3(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strcmp(PVar:playerID[CHANGEPASSWORD], inputText))
		{
			MySQLQuery("UPDATE `users` SET `password` = '%s' WHERE `id` = '%d'", MD5(inputText), PVar:playerID[USERID]);
			SendClientMessageEx(playerID, COLOR_INFO, 20);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 32);
			ShowDialog:ChangePassword_Step3(playerID);
		}
	}
	else
	{
		ShowDialog:ChangePassword_Step2(playerID);
	}
}