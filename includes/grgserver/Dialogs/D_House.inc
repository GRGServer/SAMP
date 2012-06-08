ShowDialog:House(playerID)
{
	FormatNew:title[64](LanguageString(playerID, 329), GetMySQLValue("properties", "Name", "ID", val2str(PVar:playerID[DIALOGPROPERTYID])));
	new options[1024];
	AddLine(options, LanguageString(playerID, 268));// Item 0
	AddLine(options, LanguageString(playerID, 328));// Item 1
	AddLine(options, LanguageString(playerID, 476));// Item 2
	AddLine(options, LanguageString(playerID, 480));// Item 3
	CreateDialog(playerID, "House", DIALOG_STYLE_LIST, title, options, "OK", LanguageString(playerID, 165));
}

DialogResponse:House(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:// Enter
			{
				MySQLQuery("SELECT `Locked` FROM `properties` WHERE `ID` = '%d' AND `Locked`", PVar:playerID[DIALOGPROPERTYID]);
				mysql_store_result();
				new isLocked = mysql_num_rows();
				mysql_free_result();
				if (isLocked)
				{
					SendClientMessage(playerID, COLOR_ERROR, LanguageString(playerID, 481));
				}
				else
				{
					TeleportToProperty(playerID, PVar:playerID[DIALOGPROPERTYID]);
				}
			}
			case 1:// Sell
			{
				MySQLQuery("UPDATE `properties` SET `OwnerUserID` = '0' WHERE `ID` = '%d'", PVar:playerID[DIALOGPROPERTYID]);
				GivePlayerMoneyEx(playerID, MONEY_BANK, floatstr(GetMySQLValue("properties", "Price", "ID", val2str(PVar:playerID[DIALOGPROPERTYID]))));
				ReloadPickup(strval(GetMySQLValue("properties", "PickupID", "ID", val2str(PVar:playerID[DIALOGPROPERTYID]))));
				SendClientMessageEx(playerID, COLOR_INFO, 330);
			}
			case 2:// Lock
			{
				MySQLQuery("SELECT `Locked` FROM `properties` WHERE `ID` = '%d' AND `Locked`", PVar:playerID[DIALOGPROPERTYID]);
				mysql_store_result();
				new isLocked = mysql_num_rows();
				mysql_free_result();
				if (isLocked)
				{
					SendClientMessage(playerID, COLOR_INFO, LanguageString(playerID, 477));
					MySQLQuery("UPDATE `properties` SET `Locked`= '0' WHERE `ID` = '%d'", PVar:playerID[DIALOGPROPERTYID]);
				}
				else
				{
					MySQLQuery("UPDATE `properties` SET `Locked` = '1' WHERE `ID`= '%d'", PVar:playerID[DIALOGPROPERTYID]);
					SendClientMessage(playerID, COLOR_INFO, LanguageString(playerID, 478));
				}
			}
			case 3:// Info
			{
				SendClientMessage(playerID, COLOR_INFO, LanguageString(playerID, 479));
			}
		}
	}
}