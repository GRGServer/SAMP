ShowMsgBox(playerID, name[], caption[], info[], style = MSGBOXSTYLE_OK)
{
	new button1[32];
	new button2[32];
	switch (style)
	{
		case MSGBOXSTYLE_OKCANCEL:
		{
			button1 = "OK";
			strcat(button2, LanguageString(playerID, 165));
		}
		case MSGBOXSTYLE_YESNO:
		{
			strcat(button1, LanguageString(playerID, 166));
			strcat(button2, LanguageString(playerID, 167));
		}
		default:
		{
			button1 = "OK";
		}
	}
	CreateDialog(playerID, name, DIALOG_STYLE_MSGBOX, caption, info, button1, button2);
}