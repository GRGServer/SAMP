public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (IsKeyPressed(KEY_JUMP) && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED)
	{
		ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.1, 0, 1, 1, 0, 0);// Prevent player from jumping while cuffed
		return true;
	}

	if (IsKeyPressed(KEY_ANALOG_DOWN))
	{
		new vehicleID = GetPlayerVehicleID(playerid);
		if (vehicleID)
		{
			if (VehicleProperty:vehicleID[RADIOSTATIONID] <= 1)
			{
				VehicleProperty:vehicleID[RADIOSTATIONID] = sizeof(radioStations) - 1;
			}
			else
			{
				VehicleProperty:vehicleID[RADIOSTATIONID]--;
			}
			PlayRadioStation(playerid, VehicleProperty:vehicleID[RADIOSTATIONID]);
			return true;
		}
	}

	if (IsKeyPressed(KEY_ANALOG_UP))
	{
		new vehicleID = GetPlayerVehicleID(playerid);
		if (vehicleID)
		{
			if (VehicleProperty:vehicleID[RADIOSTATIONID] >= sizeof(radioStations) - 1)
			{
				VehicleProperty:vehicleID[RADIOSTATIONID] = 1;
			}
			else
			{
				VehicleProperty:vehicleID[RADIOSTATIONID]++;
			}
			PlayRadioStation(playerid, VehicleProperty:vehicleID[RADIOSTATIONID]);
			return true;
		}
	}

	if (IsKeyPressed(KEY_ACTION))
	{
		if (IsPlayerInAnyVehicle(playerid))
		{
			TogglePlayerVehicleEngine(playerid);
			return true;
		}
	}

	if (IsKeyPressed(KEY_NO))
	{
		if (PVar:playerid[OBJEDITOR_CURRENTOBJECTID])
		{
			CancelEdit(playerid);

			new arrayIndex = PVar:playerid[OBJEDITOR_CURRENTOBJECTID] - 1;

			new modelID = Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerid[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_MODEL_ID);
			DestroyDynamicObject(PVar:playerid[OBJEDITOR_CURRENTOBJECTID]);

			new fileName[STRINGLENGTH_OBJECTFILENAME];
			new objectID = dynamicObjects[arrayIndex][OBJECT_ID];
			strcat(fileName, dynamicObjects[arrayIndex][OBJECT_FILENAME]);

			// Unset all enum variables in the object element
			Count(enumField, sizeof(dynamicObjects[]))
			{
				dynamicObjects[PVar:playerid[OBJEDITOR_CURRENTOBJECTID] - 1][enum_object:enumField] = 0;
			}

			SaveObjects(fileName);

			UpdateObjectsForAllPlayers();
			SelectObject(playerid);

			SendClientMessageEx(playerid, COLOR_INFO, "203", objectID, objectModels[modelID]);

			PVar:playerid[OBJEDITOR_CURRENTOBJECTID] = 0;

			return true;
		}
	}

	if (IsKeyPressed(KEY_WALK))
	{
		if (PVar:playerid[OBJEDITOR_CURRENTOBJECTID])
		{
			AddObject(playerid, Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerid[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_MODEL_ID), dynamicObjects[PVar:playerid[OBJEDITOR_CURRENTOBJECTID] - 1][OBJECT_FILENAME], true);
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
					SendClientMessageEx(playerid, COLOR_INFO, "142", GetMySQLField("name"));
				}
				else
				{
					SendClientMessageEx(playerid, COLOR_INFO, "337");
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