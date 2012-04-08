AddObject(playerID, modelID)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new interior = GetPlayerInterior(playerID);
	GetPlayerPos(playerID, posX, posY, posZ);
	MySQLQuery("INSERT INTO `objects` (`ModelID`, `PosX`, `PosY`, `PosZ`, `Interior`, `Source`) VALUES('%d', '%f', '%f', '%f', '%d', 'Ingame')", modelID, posX, posY, posZ, interior);
	new objectID = CreateDynamicObject(modelID, posX, posY, posZ, 0.0, 0.0, 0.0, -1, interior, -1, 100.0);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, mysql_insert_id());
}