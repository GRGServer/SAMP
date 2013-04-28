ShowDialog:Shop(playerID)
{
	FormatNew:title[64](LanguageString(playerID, StringID:17("Shop")), GetMySQLValue("properties", "name", "id", val2str(PVar:playerID[DIALOGPROPERTYID])));
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:268("Enter")));	
	CreateDialog(playerID, "Shop", DIALOG_STYLE_LIST, title, options, "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:Shop(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0: //Enter
			{
				TeleportToProperty(playerID, PVar:playerID[DIALOGPROPERTYID]);
			}
		}
	}
}
