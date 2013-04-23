ShowDialog:Police_Options(playerID)
{
	FormatNew:title[20](LanguageString(playerID, StringID:553("")));
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:268("")));// Item 1
	AddLine(options, LanguageString(playerID, StringID:328("")));// Item 2
	AddLine(options, LanguageString(playerID, StringID:476("")));// Item 3
	AddLine(options, LanguageString(playerID, StringID:549("")));// Item 4
	CreateDialog(playerID, "Police Options", DIALOG_STYLE_LIST, title, options, LanguageString(playerID, StringID:164("")), LanguageString(playerID, StringID:165("")));
}

DialogResponse:Police_Options(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				MySQLQuery("SELECT `locked` FROM `properties` WHERE `id` = '%d' AND `locked`", PVar:playerID[DIALOGPROPERTYID]);
				mysql_store_result();
				new isLocked = mysql_num_rows();
				mysql_free_result();
				if (isLocked)
				{
					SendClientMessage(playerID, COLOR_ERROR, LanguageString(playerID, StringID:481("")));
				}
				else
				{
					TeleportToProperty(playerID, PVar:playerID[DIALOGPROPERTYID]);
				}
			}
			case 1:
			{
				MySQLQuery("UPDATE `properties` SET `ownerUserId` = '0' WHERE `id` = '%d'", PVar:playerID[DIALOGPROPERTYID]);
				MySQLQuery("SELECT * FROM `properties` WHERE `id` = '%d'", PVar:playerID[DIALOGPROPERTYID]);
				mysql_store_result();
				new Float:price = floatstr(GetMySQLField("price"));
				new pickupID = strval(GetMySQLField("pickupId"));
				mysql_free_result();
				GivePlayerMoneyEx(playerID, MONEY_BANK, price);
				ReloadPickup(pickupID);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:330(""));
			}
			case 2:
			{
				MySQLQuery("SELECT `locked` FROM `properties` WHERE `id` = '%d' AND `locked`", PVar:playerID[DIALOGPROPERTYID]);
				mysql_store_result();
				new isLocked = mysql_num_rows();
				mysql_free_result();
				if (isLocked)
				{
					SendClientMessage(playerID, COLOR_INFO, LanguageString(playerID, StringID:477("")));
					MySQLQuery("UPDATE `properties` SET `locked`= '0' WHERE `id` = '%d'", PVar:playerID[DIALOGPROPERTYID]);
				}
				else
				{
					MySQLQuery("UPDATE `properties` SET `locked` = '1' WHERE `id`= '%d'", PVar:playerID[DIALOGPROPERTYID]);
					SendClientMessage(playerID, COLOR_INFO, LanguageString(playerID, StringID:478("")));
				}
			}
			case 3: 
			{
				SendClientMessage(playerID, COLOR_INFO, "Comming soon....");
			}
		}
	}
}