ShowDialog:HOTEL_HASROOM(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, 317));// Item 0
	AddLine(options, LanguageString(playerID, 318));// Item 1
	AddLine(options, LanguageString(playerID, 319));// Item 2
	CreateDialog(playerID, "HOTEL_HASROOM", DIALOG_STYLE_LIST, LanguageString(playerID, 316), options, "OK", LanguageString(playerID, 165));
}

DialogResponse:HOTEL_HASROOM(playerID, response, listItem, inputText[])
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
				MySQLQuery("UPDATE `hotelrooms` SET `OwnerUserID` = '0' WHERE `PropertyID` = '%d' AND `RoomID` = '%d'", PVar:playerID[CURRENTPROPERTYID], PVar:playerID[HOTEL_ROOMID]);
				SendClientMessageEx(playerID, COLOR_INFO, 321);
				LeaveProperty(playerID);
			}
			case 2:// Room information
			{
				MySQLQuery("SELECT * FROM `hotelrooms` WHERE `PropertyID` = '%d' AND `RoomID` = '%d'", PVar:playerID[CURRENTPROPERTYID], PVar:playerID[HOTEL_ROOMID]);
				mysql_store_result();
				new Float:price = floatstr(GetMySQLField("Price"));
				mysql_free_result();
				SendClientMessageEx(playerID, COLOR_INFO, 320, price);
				ShowDialog:HOTEL_HASROOM(playerID);
			}
		}
	}
	else
	{
		LeaveProperty(playerID);
	}
}