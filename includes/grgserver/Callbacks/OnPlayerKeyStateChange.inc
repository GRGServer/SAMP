public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (IsKeyPressed(KEY_YES))
	{
		Count(pickupID, MAX_PICKUPS)
		{
			if (GetPlayerDistanceFromPoint(playerid, pickups[pickupID][PICKUP_POSX], pickups[pickupID][PICKUP_POSY], pickups[pickupID][PICKUP_POSZ]) <= 1)
			{
				FormatNew:functionName[MAX_FUNCTION_NAME]("PUE_%s", pickups[pickupID][PICKUP_TYPE]);// PUE = PickUpEvent
				if (funcidx(functionName) == -1)
				{
					printf("Unknown pickup type: %s", pickups[pickupID][PICKUP_TYPE]);
				}
				else
				{
					CallLocalFunction(functionName, "dd", playerid, pickupID);
				}
				return true;
			}
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
	return false;
}