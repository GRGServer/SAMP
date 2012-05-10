AddObject(playerID, modelID, copyFromCurrent = false)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:rotX;
	new Float:rotY;
	new Float:rotZ;
	new interior = GetPlayerInterior(playerID);
	if (copyFromCurrent)
	{
		GetDynamicObjectPos(PVar:playerID[OBJEDITOR_CURRENTOBJECTID], posX, posY, posZ);
		GetDynamicObjectRot(PVar:playerID[OBJEDITOR_CURRENTOBJECTID], rotX, rotY, rotZ);
	}
	else
	{
		GetPlayerPos(playerID, posX, posY, posZ);
	}
	MySQLQuery("INSERT INTO `objects` (`ModelID`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Interior`, `Source`) VALUES('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', 'INGAME:%d')", modelID, posX, posY, posZ, rotX, rotY, rotZ, interior, PVar:playerID[USERID]);
	new extraID = mysql_insert_id();
	new objectID = CreateDynamicObject(modelID, posX, posY, posZ, rotX, rotY, rotZ, -1, interior, -1, STREAMER_OBJECTDISTANCE);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, extraID);
	Streamer_Update(playerID);
	PlaySound(playerID, SOUND_OBJECTPLACED);
	SendClientMessageEx(playerID, COLOR_INFO, 396, extraID, GetMySQLValue("objectmodels", "Name", "ID", val2str(modelID)));
	OnPlayerSelectDynamicObject(playerID, objectID, modelID, posX, posY, posZ);
}