ShowDialog:BusLine(playerID)
{
	new options[1024];
	Count1(line, 5)
	{
		AddLine:options(LanguageString(playerID, StringID:562("Line %d")), line);
	}
	CreateDialog(playerID, "BusLine", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:561("Change bus line")), options, "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:BusLine(playerID, response, listItem, inputText[])
{
	if (response)
	{
		SendClientMessage(playerID, COLOR_INFO, "Coming soon");
	}
}