PCMD:markobject[MAPPER](playerID, params[], 426)
{
	new objectID;
	if (sscanf(params, "d", objectID))
	{
		CmdUsageMsg(playerID, "markobject", "ObjectID");
		return COMMAND_USAGE;
	}
	MySQLQuery("SELECT * FROM `objects` WHERE `id` = '%d'", objectID);
	mysql_store_result();
	new rows = mysql_num_rows();
	if (rows)
	{
		SetPlayerMapIcon(playerID, 0, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")), 0, COLOR_MARKER_OBJECT, MAPICON_GLOBAL);
	}
	mysql_free_result();
	if (!rows)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 427);
		return COMMAND_ERROR;
	}
	return COMMAND_OK;
}