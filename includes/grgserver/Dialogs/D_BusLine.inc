ShowDialog:BusLine(playerID)
{
	new options[1024];
	Count1(line, 5)
	{
		AddLine:options(LanguageString(playerID, "562"), line);
	}
	CreateDialog(playerID, "BusLine", DIALOG_STYLE_LIST, LanguageString(playerID, "561"), options, "OK", LanguageString(playerID, "165"));
}

DialogResponse:BusLine(playerID, response, listItem, inputText[])
{
	if (response)
	{
		SendClientMessage(playerID, COLOR_INFO, "Coming soon");
	}
}