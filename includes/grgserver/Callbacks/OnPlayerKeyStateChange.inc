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
				MySQLQuery("SELECT COUNT(*) AS `Count` FROM `radiostations`");
				mysql_store_result();
				id = strval(GetMySQLField("Count"));
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
			MySQLQuery("SELECT COUNT(*) AS `Count` FROM `radiostations`");
			mysql_store_result();
			new count = strval(GetMySQLField("Count"));
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
			MySQLQuery("DELETE FROM `objects` WHERE `ID` = '%d'", Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerid[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_EXTRA_ID));
			new modelID = Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerid[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_MODEL_ID);
			DestroyDynamicObject(PVar:playerid[OBJEDITOR_CURRENTOBJECTID]);
			PVar:playerid[OBJEDITOR_CURRENTOBJECTID] = 0;
			CancelEdit(playerid);
			SelectObject(playerid);
			SendClientMessageEx(playerid, COLOR_INFO, 203, GetMySQLValue("objectmodels", "Name", "ID", val2str(modelID)));
			return true;
		}
	}
	if (IsKeyPressed(KEY_WALK))
	{
		if (PVar:playerid[OBJEDITOR_CURRENTOBJECTID])
		{
			new Float:rotX;
			new Float:rotY;
			new Float:rotZ;
			GetDynamicObjectRot(PVar:playerid[OBJEDITOR_CURRENTOBJECTID], rotX, rotY, rotZ);
			AddObject(playerid, Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerid[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_MODEL_ID), rotX, rotY, rotZ);
			return true;
		}
		if (permissions[playerid][PERMISSION_MAPPER])
		{
			new pickupID = IsPlayerInPickup(playerid);
			if (pickupID)
			{
				MySQLQuery("SELECT * FROM `properties` WHERE `PickupID` = '%d'", pickups[pickupID][PICKUP_ID]);
				mysql_store_result();
				if (mysql_num_rows())
				{
					PVar:playerid[SELECTEDPROPERTYID] = strval(GetMySQLField("ID"));
					SendClientMessageEx(playerid, COLOR_INFO, 142, GetMySQLField("Name"));
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
		if (pickupID)
		{
			FormatNew:functionName[MAX_FUNCTION_NAME]("PUE_%s", pickups[pickupID][PICKUP_TYPE]);// PUE = PickUpEvent
			if (funcidx(functionName) == -1)
			{
				printf("Unknown pickup type: %s", pickups[pickupID][PICKUP_TYPE]);
			}
			else
			{
				PlaySound(playerid, SOUND_PICKUPKEYPRESSED);
				CallLocalFunction(functionName, "dd", playerid, pickupID);
			}
			return true;
		}
	}
	return false;
}