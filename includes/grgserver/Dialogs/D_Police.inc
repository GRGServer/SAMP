ShowDialog:POLICE(playerID)
{
	FormatNew:options[10]("Betreten");
	CreateDialog(playerID, "POLICE", DIALOG_STYLE_LIST, "Polizei", options, "OK", LanguageString(playerID, 165));
}