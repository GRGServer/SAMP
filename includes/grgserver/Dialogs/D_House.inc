ShowDialog:House(playerID)
{
	FormatNew:title[64](LanguageString(playerID, 329), GetMySQLValue("properties", "Name", "ID", val2str(PVar:playerID[DIALOGPROPERTYID])));
	new options[1024];
	AddLine(options, LanguageString(playerID, 268));// Item 0
	AddLine(options, LanguageString(playerID, 328));// Item 1
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
				TeleportToProperty(playerID, PVar:playerID[DIALOGPROPERTYID]);
			}
			case 1:// Sell
			{
				MySQLQuery("UPDATE `properties` SET `OwnerUserID` = '0' WHERE `ID` = '%d'", PVar:playerID[DIALOGPROPERTYID]);
				GivePlayerMoneyEx(playerID, MONEY_BANK, floatstr(GetMySQLValue("properties", "Price", "ID", val2str(PVar:playerID[DIALOGPROPERTYID]))));
				ReloadPickup(strval(GetMySQLValue("properties", "PickupID", "ID", val2str(PVar:playerID[DIALOGPROPERTYID]))));
				SendClientMessageEx(playerID, COLOR_INFO, 330);
			}
		}
	}
}