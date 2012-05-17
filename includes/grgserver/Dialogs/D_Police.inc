ShowDialog:Police(playerID)
{
	FormatNew:options[10]("Betreten");
	CreateDialog(playerID, "Police", DIALOG_STYLE_LIST, "Polizei", options, "OK", LanguageString(playerID, 165));
}

DialogResponse:Police(playerID, response, listItem, inputText[])
{
	// Nothing to do here
}