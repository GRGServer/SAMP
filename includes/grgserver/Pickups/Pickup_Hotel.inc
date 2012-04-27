PickupEvent:HOTEL(playerID, pickupID)
{
	PVar:playerID[CURRENTBUILDINGID] = strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
	SetPlayerPosEx(playerID, HOTEL_RECEPTION_POSX, HOTEL_RECEPTION_POSY, HOTEL_RECEPTION_POSZ);
	SetPlayerFacingAngle(playerID, HOTEL_RECEPTION_ANGLE);
	SetPlayerInterior(playerID, HOTEL_RECEPTION_INTERIOR);
	SetPlayerVirtualWorld(playerID, PVar:playerID[CURRENTBUILDINGID]);
	MySQLQuery("SELECT * FROM `hotelrooms` WHERE `BuildingID` = '%d' AND `OwnerUserID` = '%d'", PVar:playerID[CURRENTBUILDINGID], PVar:playerID[USERID]);
	mysql_store_result();
	PVar:playerID[HOTEL_ROOMID] = strval(GetMySQLField("RoomID"));
	mysql_free_result();
	if (PVar:playerID[HOTEL_ROOMID])
	{
		ShowDialog(playerID, DIALOG_HOTEL_HASROOM);
	}
	else
	{
		MySQLQuery("SELECT * FROM `hotelrooms` WHERE `BuildingID` = '%d' AND `OwnerUserID` = '0' ORDER BY `RoomID` ASC", PVar:playerID[CURRENTBUILDINGID]);
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
				LeaveBuilding(playerID);
			}
		}
		mysql_free_result();
	}
}

PickupModelID:HOTEL(pickupID)
{
	return 1314;
}