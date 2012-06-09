ShowDialog:ChangePassword_Step1(playerID)
{
	CreateDialog(playerID, "ChangePassword_Step1", DIALOG_STYLE_PASSWORD, LanguageString(playerID, 240), LanguageString(playerID, 241), LanguageString(playerID, 177), LanguageString(playerID, 165));
}

DialogResponse:ChangePassword_Step1(playerID, response, listItem, inputText[])
{
	if (response)
	{
		MySQLQuery("SELECT `id` FROM `users` WHERE `id` = '%d' AND `password` = '%s'", PVar:playerID[USERID], MD5(inputText));
		mysql_store_result();
		new rows = mysql_num_rows();
		mysql_free_result();
		if (rows)
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