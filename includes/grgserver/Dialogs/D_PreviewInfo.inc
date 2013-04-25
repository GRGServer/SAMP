ShowDialog:PreviewInfo(playerID)
{
	CreateDialog(playerID, "PreviewInfo", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:269("Preview")), LanguageString(playerID, StringID:270("This is just a preview of our SA-MP Server!\nSome features may not work or are not free of bugs.\n\nIf you found a bug or have a suggestion, please report it on http://issues.grgserver.net.")), "OK", "");
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