ShowDialog:Register_Language(playerID)
{
	new list[1024];
	AddLine(list, "English");
	AddLine(list, "Deutsch");
	CreateDialog(playerID, "Register_Language", DIALOG_STYLE_LIST, "Select language / Sprache wählen", list, "OK", "Quit / Beenden");
}

DialogResponse:Register_Language(playerID, response, listItem, inputText[])
{
	if (response)
	{
		PVar:playerID[LANGUAGE] = listItem;
		ShowDialog:PreviewInfo(playerID);
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_INFO, 37);
		Kick(playerID);
	}
}