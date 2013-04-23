ShowDialog:PreviewInfo(playerID)
{
	CreateDialog(playerID, "PreviewInfo", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:269("")), LanguageString(playerID, StringID:270("")), "OK", "");
}

DialogResponse:PreviewInfo(playerID, response, listItem, inputText[])
{
	if (PVar:playerID[REGISTERED])
	{
		ShowDialog:Login(playerID);
	}
	else
	{
		ShowDialog:Register_Password1(playerID);
	}
}