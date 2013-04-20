ShowDialog:Hotel_RoomList(playerID)
{
	FormatNew:title[64](LanguageString(playerID, "315"), GetMySQLValue("properties", "name", "id", val2str(PVar:playerID[CURRENTPROPERTYID])));
	MySQLQuery("SELECT * FROM `hotelrooms` WHERE `propertyId` = '%d' AND `ownerUserId` = '0' ORDER BY `roomId` ASC", PVar:playerID[CURRENTPROPERTYID]);
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
			Format:rooms("%s%s: $%s", rooms, GetMySQLField("roomId"), FormatMoney(floatstr(GetMySQLField("price"))));
		}
		CreateDialog(playerID, "Hotel_RoomList", DIALOG_STYLE_LIST, title, rooms, "OK", LanguageString(playerID, "165"));
	}
	mysql_free_result();
	return roomsCount;
}

DialogResponse:Hotel_RoomList(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new string[256];
		sscanf(inputText, "p<:>ds[256]", PVar:playerID[HOTEL_ROOMID], string);
		MySQLQuery("UPDATE `hotelrooms` SET `ownerUserId` = '%d' WHERE `propertyId` = '%d' AND `roomId` = '%d'", PVar:playerID[USERID], PVar:playerID[CURRENTPROPERTYID], PVar:playerID[HOTEL_ROOMID]);
		TeleportToInterior(playerID, HOTEL_ROOM_INTERIOR);
		SetPlayerVirtualWorld(playerID, playerID);
	}
	else
	{
		LeaveProperty(playerID);
	}
}