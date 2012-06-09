public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (IsKeyPressed(KEY_ANALOG_DOWN))
	{
		new vehicleID = GetPlayerVehicleID(playerid);
		if (vehicleID)
		{
			new id = VehicleProperty:vehicleID[RADIOSTATION];
			if (id <= 1)
			{
				MySQLQuery("SELECT COUNT(*) AS `count` FROM `radiostations`");
				mysql_store_result();
				id = strval(GetMySQLField("count"));
				mysql_free_result();
			}
			else
			{
				id--;
			}
			PlayRadioStation(playerid, id);
			return true;
		}
	}
	if (IsKeyPressed(KEY_ANALOG_UP))
	{
		new vehicleID = GetPlayerVehicleID(playerid);
		if (vehicleID)
		{
			MySQLQuery("SELECT COUNT(*) AS `count` FROM `radiostations`");
			mysql_store_result();
			new count = strval(GetMySQLField("count"));
			mysql_free_result();
			new id = VehicleProperty:vehicleID[RADIOSTATION];
			if (id >= count)
			{
				id = 1;
			}
			else
			{
				id++;
			}
			PlayRadioStation(playerid, id);
			return true;
		}
	}
	if (IsKeyPressed(KEY_NO))
	{
		if (PVar:playerid[OBJEDITOR_CURRENTOBJECTID])
		{
			MySQLQuery("DELETE FROM `objects` WHERE `id` = '%d'", Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerid[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_EXTRA_ID));
			new extraID = Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerid[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_EXTRA_ID);
			new modelID = Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerid[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_MODEL_ID);
			DestroyDynamicObject(PVar:playerid[OBJEDITOR_CURRENTOBJECTID]);
			PVar:playerid[OBJEDITOR_CURRENTOBJECTID] = 0;
			UpdateObjectsForAllPlayers();
			CancelEdit(playerid);
			SelectObject(playerid);
			SendClientMessageEx(playerid, COLOR_INFO, 203, extraID, GetMySQLValue("objectmodels", "name", "id", val2str(modelID)));
			return true;
		}
	}
	if (IsKeyPressed(KEY_WALK))
	{
		if (PVar:playerid[OBJEDITOR_CURRENTOBJECTID])
		{
			AddObject(playerid, Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerid[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_MODEL_ID), true);
			return true;
		}
		if (permissions[playerid][PERMISSION_MAPPER])
		{
			new pickupID = IsPlayerInPickup(playerid);
			if (pickupID != -1)
			{
				MySQLQuery("SELECT * FROM `properties` WHERE `pickupId` = '%d'", pickups[pickupID][PICKUP_ID]);
				mysql_store_result();
				if (mysql_num_rows())
				{
					PVar:playerid[SELECTEDPROPERTYID] = strval(GetMySQLField("id"));
					SendClientMessageEx(playerid, COLOR_INFO, 142, GetMySQLField("name"));
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_INFO, 337);
				}
				mysql_free_result();
				return true;
			}
		}
	}
	if (IsKeyPressed(KEY_YES))
	{
		new pickupID = IsPlayerInPickup(playerid);
		if (pickupID != -1)
		{
			PickupEvent(playerid, pickupID, PICKUPEVENT_KEYPRESS);
			return true;
		}
	}
	return false;
}