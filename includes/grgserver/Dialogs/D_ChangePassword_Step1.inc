ShowDialog:ChangePassword_Step1(playerID)
{
	CreateDialog(playerID, "ChangePassword_Step1", DIALOG_STYLE_PASSWORD, LanguageString(playerID, StringID:98("Change account password")), LanguageString(playerID, StringID:241("Enter your current password.")), LanguageString(playerID, StringID:177("Next")), LanguageString(playerID, StringID:165("Cancel")));
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
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:30("The entered password is wrong!"));
			ShowDialog:ChangePassword_Step1(playerID);
		}
	}
}