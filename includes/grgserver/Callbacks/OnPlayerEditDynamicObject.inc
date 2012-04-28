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
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new Float:rotX;
			new Float:rotY;
			new Float:rotZ;
			GetDynamicObjectPos(objectid, posX, posY, posZ);
			GetDynamicObjectRot(objectid, rotX, rotY, rotZ);
			new id = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID);
			if (id)
			{
				MySQLQuery("UPDATE `objects` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, rotX, rotY, rotZ, id);
				SendClientMessageEx(playerid, COLOR_INFO, 199);
			}
			else
			{
				SendClientMessageEx(playerid, COLOR_ERROR, 200);
			}
			PVar:playerid[OBJEDITOR_CURRENTOBJECTID] = 0;
			PlaySound(playerid, SOUND_OBJECTPLACED);
			SelectObject(playerid);
		}
	}
}