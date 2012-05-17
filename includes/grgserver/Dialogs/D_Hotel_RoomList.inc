ShowDialog:Hotel_RoomList(playerID)
{
	MySQLQuery("SELECT * FROM `hotelrooms` WHERE `PropertyID` = '%d' AND `OwnerUserID` = '0' ORDER BY `RoomID` ASC", PVar:playerID[CURRENTPROPERTYID]);
	mysql_store_result();
	new roomsCount = mysql_num_rows();
	if (roomsCount)
	{
		new rooms[2048];
		while (FetchMySQLRow())
		{
			if (strlen(rooms))
			{
				strcat(rooms, "\n");
			}
			Format:rooms("%s%s: $%s", rooms, GetMySQLField("RoomID"), FormatMoney(floatstr(GetMySQLField("Price"))));
		}
		CreateDialog(playerID, "Hotel_RoomList", DIALOG_STYLE_LIST, LanguageString(playerID, 315), rooms, "OK", LanguageString(playerID, 165));
	}
	mysql_free_result();
	return roomsCount;
}

DialogResponse:Hotel_RoomList(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new string[256];
		sscanf(inputText, "p:ds", PVar:playerID[HOTEL_ROOMID], string);
		MySQLQuery("UPDATE `hotelrooms` SET `OwnerUserID` = '%d' WHERE `PropertyID` = '%d' AND `RoomID` = '%d'", PVar:playerID[USERID], PVar:playerID[CURRENTPROPERTYID], PVar:playerID[HOTEL_ROOMID]);
		TeleportToInterior(playerID, HOTEL_ROOM_INTERIOR);
		SetPlayerVirtualWorld(playerID, playerID);
	}
	else
	{
		LeaveProperty(playerID);
	}
}