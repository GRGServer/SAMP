ShowDialog:Register_Language(playerID)
{
	new list[1024];
	AddLine(list, "en\tEnglish");
	AddLine(list, "de\tDeutsch");
	CreateDialog(playerID, "Register_Language", DIALOG_STYLE_LIST, "Select language / Sprache wählen", list, "OK", "Quit / Beenden");
}

DialogResponse:Register_Language(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new languageName[STRINGLENGTH_LANGUAGE];
		sscanf(inputText, "p\tss", languageName);
		PVar:playerID[LANGUAGE] = languageName;
		ShowDialog:PreviewInfo(playerID);
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_INFO, "37");
		Kick(playerID);
	}
}