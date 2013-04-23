ShowDialog:Hotel_HasRoom(playerID)
{
	FormatNew:title[64](LanguageString(playerID, StringID:316("")), GetMySQLValue("properties", "name", "id", val2str(PVar:playerID[CURRENTPROPERTYID])));
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:317("")));// Item 0
	AddLine(options, LanguageString(playerID, StringID:318("")));// Item 1
	AddLine(options, LanguageString(playerID, StringID:319("")));// Item 2
	CreateDialog(playerID, "Hotel_HasRoom", DIALOG_STYLE_LIST, title, options, "OK", LanguageString(playerID, StringID:165("")));
}

DialogResponse:Hotel_HasRoom(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:// Enter hotel room
			{
				TeleportToInterior(playerID, HOTEL_ROOM_INTERIOR);
				SetPlayerVirtualWorld(playerID, playerID);
			}
			case 1:// Cancel hotel room
			{
				MySQLQuery("UPDATE `hotelrooms` SET `ownerUserId` = '0' WHERE `propertyId` = '%d' AND `roomId` = '%d'", PVar:playerID[CURRENTPROPERTYID], PVar:playerID[HOTEL_ROOMID]);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:321(""));
				LeaveProperty(playerID);
			}
			case 2:// Room information
			{
				MySQLQuery("SELECT * FROM `hotelrooms` WHERE `propertyId` = '%d' AND `roomId` = '%d'", PVar:playerID[CURRENTPROPERTYID], PVar:playerID[HOTEL_ROOMID]);
				mysql_store_result();
				new Float:price = floatstr(GetMySQLField("price"));
				mysql_free_result();
				SendClientMessageEx(playerID, COLOR_INFO, StringID:320(""), price);
				ShowDialog:Hotel_HasRoom(playerID);
			}
		}
	}
	else
	{
		LeaveProperty(playerID);
	}
}