PCMD:markobjects[MAPPER](playerID, params[], 482)
{
	new modelID;
	if (sscanf(params, "d", modelID))
	{
		CmdUsageMsg(playerID, "markobjects", "ModelID");
		return COMMAND_USAGE;
	}
	MySQLQuery("SELECT * FROM `objects` WHERE `ModelID` = '%d'", modelID);
	mysql_store_result();
	new rows = mysql_num_rows();
	if (rows)
	{
		if (rows > 100)
		{
			rows = 100;
		}
		Count(iconID, 100)
		{
			RemovePlayerMapIcon(playerID, iconID);
		}
		Count(iconID, rows)
		{
			FetchMySQLRow();
			SetPlayerMapIcon(playerID, iconID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), 0, COLOR_MARKER_OBJECT, MAPICON_GLOBAL);
		}
	}
	mysql_free_result();
	if (!rows)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 425);
		return COMMAND_ERROR;
	}
	return COMMAND_OK;
}