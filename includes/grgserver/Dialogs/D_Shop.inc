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
				MySQLQuery("SELECT `locked` FROM `properties` WHERE `id` = '%d' AND `locked`", PVar:playerID[DIALOGPROPERTYID]);
				mysql_store_result();
				new isLocked = mysql_num_rows();
				mysql_free_result();
				if (isLocked)
				{
					SendClientMessage(playerID, COLOR_ERROR, LanguageString(playerID, StringID:481("This house is locked!")));
				}
				else
				{
					TeleportToProperty(playerID, PVar:playerID[DIALOGPROPERTYID]);
				}
			}
		}
	}
}
