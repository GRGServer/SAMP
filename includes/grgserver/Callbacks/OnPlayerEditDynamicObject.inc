public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	MoveDynamicObject(objectid, x, y, z, 10.0, rx, ry, rz);
	switch (response)
	{
		case EDIT_RESPONSE_CANCEL:
		{
			MoveDynamicObject(objectid, PVar:playerid[OBJEDITOR_LASTPOSX], PVar:playerid[OBJEDITOR_LASTPOSY], PVar:playerid[OBJEDITOR_LASTPOSZ], 10.0, PVar:playerid[OBJEDITOR_LASTROTX], PVar:playerid[OBJEDITOR_LASTROTY], PVar:playerid[OBJEDITOR_LASTROTZ]);
			PVar:playerid[OBJEDITOR_CURRENTOBJECTID] = 0;
			SelectObject(playerid);
		}
		case EDIT_RESPONSE_FINAL:
		{
			if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID) == OBJECTTYPE_NORMAL)
			{
				GetDynamicObjectPos(objectid, dynamicObjects[objectid - 1][OBJECT_POS][0], dynamicObjects[objectid - 1][OBJECT_POS][1], dynamicObjects[objectid - 1][OBJECT_POS][2]);
				GetDynamicObjectRot(objectid, dynamicObjects[objectid - 1][OBJECT_ROT][0], dynamicObjects[objectid - 1][OBJECT_ROT][1], dynamicObjects[objectid - 1][OBJECT_ROT][2]);
				SaveObjects(dynamicObjects[objectid - 1][OBJECT_FILENAME]);
				SendClientMessageEx(playerid, COLOR_INFO, StringID:199("The changes have been saved"));
			}
			else
			{
				SendClientMessageEx(playerid, COLOR_ERROR, StringID:200("The object is not a streamed object or is already used in another way!"));
			}

			PVar:playerid[OBJEDITOR_CURRENTOBJECTID] = 0;
			PlaySound(playerid, SOUND_OBJECTPLACED);
			SelectObject(playerid);
		}
	}
}