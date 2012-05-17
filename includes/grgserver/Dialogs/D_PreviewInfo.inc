ShowDialog:PreviewInfo(playerID)
{
	ShowMsgBox(playerID, "PreviewInfo", LanguageString(playerID, 269), LanguageString(playerID, 270));
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