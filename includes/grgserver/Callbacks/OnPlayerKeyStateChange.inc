public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
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
			}
		}
	}
	return false;
}