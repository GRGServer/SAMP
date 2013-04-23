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
		new languageName[3];
		new languageTitle[100];
		sscanf(inputText, "p<\t>s[3]s[100]", languageName, languageTitle);
		PVar:playerID[LANGUAGE] = GetLanguageID(languageName);
		ShowDialog:PreviewInfo(playerID);
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_INFO, StringID:37(""));
		Kick(playerID);
	}
}