PickupEvent:HOTEL(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			PVar:playerID[CURRENTPROPERTYID] = strval(GetMySQLValue("properties", "id", "pickupId", val2str(pickups[pickupID][PICKUP_ID])));
			SetPlayerPosEx(playerID, HOTEL_RECEPTION_POSX, HOTEL_RECEPTION_POSY, HOTEL_RECEPTION_POSZ);
			SetPlayerFacingAngle(playerID, HOTEL_RECEPTION_ANGLE);
			SetPlayerInterior(playerID, HOTEL_RECEPTION_INTERIOR);
			SetPlayerVirtualWorld(playerID, PVar:playerID[CURRENTPROPERTYID]);
			MySQLQuery("SELECT * FROM `hotelrooms` WHERE `propertyId` = '%d' AND `ownerUserId` = '%d'", PVar:playerID[CURRENTPROPERTYID], PVar:playerID[USERID]);
			mysql_store_result();
			PVar:playerID[HOTEL_ROOMID] = strval(GetMySQLField("roomId"));
			mysql_free_result();
			if (PVar:playerID[HOTEL_ROOMID])
			{
				ShowDialog:Hotel_HasRoom(playerID);
			}
			else
			{
				if (!ShowDialog:Hotel_RoomList(playerID))
				{
					SendClientMessageEx(playerID, COLOR_INFO, StringID:314(""));
					if (permissions[playerID][PERMISSION_MAPPER])
					{
						SendClientMessageEx(playerID, COLOR_INFO, StringID:322(""));
					}
					else
					{
						LeaveProperty(playerID);
					}
				}
			}
			return true;
		}
		case PICKUPEVENT_PICKUP:
		{
			if (permissions[playerID][PERMISSION_MAPPER])
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:338(""));
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