AddObject(playerID, modelID, Float:rotX = 0.0, Float:rotY = 0.0, Float:rotZ = 0.0)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new interior = GetPlayerInterior(playerID);
	GetPlayerPos(playerID, posX, posY, posZ);
	MySQLQuery("INSERT INTO `objects` (`ModelID`, `PosX`, `PosY`, `PosZ`, `RotX`, `RotY`, `RotZ`, `Interior`, `Source`) VALUES('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', 'INGAME:%d')", modelID, posX, posY, posZ, rotX, rotY, rotZ, interior, PVar:playerID[USERID]);
	new objectID = CreateDynamicObject(modelID, posX, posY, posZ, rotX, rotY, rotZ, -1, interior, -1, 100.0);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, mysql_insert_id());
	Streamer_Update(playerID);
	OnPlayerSelectDynamicObject(playerID, objectID, modelID, posX, posY, posZ);
	PlaySound(playerID, SOUND_OBJECTPLACED);
	SendClientMessageEx(playerID, COLOR_INFO, 396);
}