PickupEvent:HOTEL(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			PVar:playerID[CURRENTPROPERTYID] = strval(GetMySQLValue("properties", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
			SetPlayerPosEx(playerID, HOTEL_RECEPTION_POSX, HOTEL_RECEPTION_POSY, HOTEL_RECEPTION_POSZ);
			SetPlayerFacingAngle(playerID, HOTEL_RECEPTION_ANGLE);
			SetPlayerInterior(playerID, HOTEL_RECEPTION_INTERIOR);
			SetPlayerVirtualWorld(playerID, PVar:playerID[CURRENTPROPERTYID]);
			MySQLQuery("SELECT * FROM `hotelrooms` WHERE `PropertyID` = '%d' AND `OwnerUserID` = '%d'", PVar:playerID[CURRENTPROPERTYID], PVar:playerID[USERID]);
			mysql_store_result();
			PVar:playerID[HOTEL_ROOMID] = strval(GetMySQLField("RoomID"));
			mysql_free_result();
			if (PVar:playerID[HOTEL_ROOMID])
			{
				ShowDialog(playerID, DIALOG_HOTEL_HASROOM);
			}
			else
			{
				MySQLQuery("SELECT * FROM `hotelrooms` WHERE `PropertyID` = '%d' AND `OwnerUserID` = '0' ORDER BY `RoomID` ASC", PVar:playerID[CURRENTPROPERTYID]);
				mysql_store_result();
				if (mysql_num_rows())
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
					ShowDialog(playerID, DIALOG_HOTEL_ROOMLIST, rooms);
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_INFO, 314);
					if (permissions[playerID][PERMISSION_MAPPER])
					{
						SendClientMessageEx(playerID, COLOR_INFO, 322);
					}
					else
					{
						LeaveProperty(playerID);
					}
				}
				mysql_free_result();
			}
			return true;
		}
		case PICKUPEVENT_PICKUP:
		{
			if (permissions[playerID][PERMISSION_MAPPER])
			{
				SendClientMessageEx(playerID, COLOR_INFO, 338);
			}
			return false;
		}
	}
	return false;
}

PickupModelID:HOTEL(pickupID)
{
	return 1314;
}