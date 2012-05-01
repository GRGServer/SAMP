PCMD:nocamproperty[MAPPER](playerID, params[], 350)
{
	MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`PickupID` = `pickups`.`ID` WHERE `CameraPosX` = '0' AND `CameraPosY` = '0' AND `CameraPosZ` = '0'");
	mysql_store_result();
	new rows = mysql_num_rows();
	if (rows)
	{
		SetPlayerPos(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
		SendClientMessageEx(playerID, COLOR_INFO, 351, GetMySQLField("Name"), rows);
	}
	mysql_free_result();
	if (rows)
	{
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 352);
		return COMMAND_ERROR;
	}
}