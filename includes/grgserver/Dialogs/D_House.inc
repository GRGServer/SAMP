ShowDialog:House(playerID)
{
	FormatNew:title[64](LanguageString(playerID, StringID:329("Your house - %s")), GetMySQLValue("properties", "name", "id", val2str(PVar:playerID[DIALOGPROPERTYID])));
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:268("Enter")));// Item 0
	AddLine(options, LanguageString(playerID, StringID:328("Sell")));// Item 1
	AddLine(options, LanguageString(playerID, StringID:476("Lock/Unlock")));// Item 2
	CreateDialog(playerID, "House", DIALOG_STYLE_LIST, title, options, "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:House(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:// Enter
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
			case 1:// Sell
			{
				MySQLQuery("UPDATE `properties` SET `ownerUserId` = '0' WHERE `id` = '%d'", PVar:playerID[DIALOGPROPERTYID]);
				MySQLQuery("SELECT * FROM `properties` WHERE `id` = '%d'", PVar:playerID[DIALOGPROPERTYID]);
				mysql_store_result();
				new Float:price = floatstr(GetMySQLField("price"));
				new pickupID = strval(GetMySQLField("pickupId"));
				mysql_free_result();
				GivePlayerMoneyEx(playerID, MONEY_BANK, price);
				ReloadPickup(pickupID);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:330("Your house has been sold!"));
			}
			case 2:// Lock
			{
				MySQLQuery("SELECT `locked` FROM `properties` WHERE `id` = '%d' AND `locked`", PVar:playerID[DIALOGPROPERTYID]);
				mysql_store_result();
				new isLocked = mysql_num_rows();
				mysql_free_result();
				if (isLocked)
				{
					SendClientMessage(playerID, COLOR_INFO, LanguageString(playerID, StringID:477("You have unlocked your house")));
					MySQLQuery("UPDATE `properties` SET `locked`= '0' WHERE `id` = '%d'", PVar:playerID[DIALOGPROPERTYID]);
				}
				else
				{
					MySQLQuery("UPDATE `properties` SET `locked` = '1' WHERE `id`= '%d'", PVar:playerID[DIALOGPROPERTYID]);
					SendClientMessage(playerID, COLOR_INFO, LanguageString(playerID, StringID:478("You have locked your house")));
				}
			}
		}
	}
}