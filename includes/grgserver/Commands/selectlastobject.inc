PCMD:selectlastobject[MAPPER](playerID, params[], 398)
{
	new id;
	new modelID;
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	MySQLQuery("SELECT * FROM `objects` WHERE `Source` = 'INGAME:%d' ORDER BY `ID` DESC LIMIT 1", PVar:playerID[USERID]);
	mysql_store_result();
	if (mysql_num_rows())
	{
		id = strval(GetMySQLField("ID"));
		modelID = strval(GetMySQLField("ModelID"));
		posX = floatstr(GetMySQLField("PosX"));
		posY = floatstr(GetMySQLField("PosY"));
		posZ = floatstr(GetMySQLField("PosZ"));
	}
	mysql_free_result();
	if (!id)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 399);
		return COMMAND_ERROR;
	}
	new objectID = GetObjectByID(id);
	if (objectID)
	{
		OnPlayerSelectDynamicObject(playerID, objectID, modelID, posX, posY, posZ);
		return COMMAND_OK;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, 425);
	return COMMAND_ERROR;
}