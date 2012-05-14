ShowDialog:PREVIEWINFO(playerID)
{
	ShowMsgBox(playerID, "PREVIEWINFO", LanguageString(playerID, 269), LanguageString(playerID, 270));
}

DialogResponse:PREVIEWINFO(playerID, response, listItem, inputText[])
{
	if (PVar:playerID[REGISTERED])
	{
		ShowDialog:LOGIN(playerID);
	}
	else
	{
		ShowDialog:REGISTER_PASSWORD1(playerID);
	}
}